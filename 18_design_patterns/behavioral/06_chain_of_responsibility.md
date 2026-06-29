# Chain of Responsibility Pattern

**Category:** Behavioral

---

## What Is It?

The **Chain of Responsibility** pattern passes a request along a chain of handlers. Each handler decides whether to process it or pass it to the next handler.

> 🔁 **Analogy:** A customer complaint at a company. First the customer service rep handles it. If they can't, it goes to the supervisor. If not, the manager. If not, the CEO. Each person in the chain either handles it or passes it up.

---

## When to Use It?

- More than one object may handle a request, and the handler isn't known a priori
- You want to issue a request to one of several objects without specifying the receiver explicitly
- The set of objects that can handle a request should be specified dynamically

---

## Structure

```
Client
  │
  └──► Handler1 ──► Handler2 ──► Handler3 ──► nullptr (end of chain)
       │            │            │
    handles?     handles?     handles?
    YES→process  YES→process  YES→process
    NO →next     NO →next     NO →unhandled
```

---

## C++ Implementation: Support Ticket System

```cpp
#include <iostream>
#include <string>
using namespace std;

// ============ Request ============
struct SupportTicket {
    int    level;     // 1=simple, 2=medium, 3=complex
    string issue;
};

// ============ Handler Interface ============
class SupportHandler {
protected:
    SupportHandler* next = nullptr;

public:
    SupportHandler* setNext(SupportHandler* handler) {
        next = handler;
        return handler;   // return handler to enable chaining: a->setNext(b)->setNext(c)
    }

    virtual void handle(const SupportTicket& ticket) {
        if (next) next->handle(ticket);
        else cout << "[Unhandled] Ticket level " << ticket.level
                  << ": " << ticket.issue << endl;
    }

    virtual ~SupportHandler() {}
};

// ============ Concrete Handlers ============
class Level1Support : public SupportHandler {
public:
    void handle(const SupportTicket& ticket) override {
        if (ticket.level == 1) {
            cout << "[Level 1 Support] Resolved: " << ticket.issue << endl;
        } else {
            cout << "[Level 1 Support] Escalating to Level 2..." << endl;
            SupportHandler::handle(ticket);
        }
    }
};

class Level2Support : public SupportHandler {
public:
    void handle(const SupportTicket& ticket) override {
        if (ticket.level == 2) {
            cout << "[Level 2 Support] Resolved: " << ticket.issue << endl;
        } else {
            cout << "[Level 2 Support] Escalating to Manager..." << endl;
            SupportHandler::handle(ticket);
        }
    }
};

class ManagerSupport : public SupportHandler {
public:
    void handle(const SupportTicket& ticket) override {
        if (ticket.level == 3) {
            cout << "[Manager] Resolved: " << ticket.issue << endl;
        } else {
            cout << "[Manager] Cannot handle level " << ticket.level << endl;
            SupportHandler::handle(ticket);
        }
    }
};

int main() {
    // Build the chain
    Level1Support  l1;
    Level2Support  l2;
    ManagerSupport mgr;

    l1.setNext(&l2)->setNext(&mgr);   // chain: l1 → l2 → mgr

    // Send various tickets
    vector<SupportTicket> tickets = {
        {1, "Password reset"},
        {2, "Software installation issue"},
        {3, "Critical data breach"},
        {1, "Email not working"},
        {4, "Unknown issue (no handler)"}
    };

    for (const auto& ticket : tickets) {
        cout << "\nTicket [Level " << ticket.level << "]: " << ticket.issue << endl;
        l1.handle(ticket);
    }

    return 0;
}
```

Output:

```
Ticket [Level 1]: Password reset
[Level 1 Support] Resolved: Password reset

Ticket [Level 2]: Software installation issue
[Level 1 Support] Escalating to Level 2...
[Level 2 Support] Resolved: Software installation issue

Ticket [Level 3]: Critical data breach
[Level 1 Support] Escalating to Level 2...
[Level 2 Support] Escalating to Manager...
[Manager] Resolved: Critical data breach

Ticket [Level 1]: Email not working
[Level 1 Support] Resolved: Email not working

Ticket [Level 4]: Unknown issue (no handler)
[Level 1 Support] Escalating to Level 2...
[Level 2 Support] Escalating to Manager...
[Manager] Cannot handle level 4
[Unhandled] Ticket level 4: Unknown issue (no handler)
```

---

## Real-World Example: Middleware / Request Pipeline

```cpp
#include <iostream>
#include <functional>
#include <string>
using namespace std;

// Like Express.js / ASP.NET middleware

struct HttpRequest {
    string method;
    string path;
    string token;
};

class Middleware {
protected:
    Middleware* next = nullptr;
public:
    void setNext(Middleware* m) { next = m; }
    virtual void process(HttpRequest& req) {
        if (next) next->process(req);
    }
    virtual ~Middleware() {}
};

class LoggingMiddleware : public Middleware {
public:
    void process(HttpRequest& req) override {
        cout << "[Log] " << req.method << " " << req.path << endl;
        Middleware::process(req);
    }
};

class AuthMiddleware : public Middleware {
public:
    void process(HttpRequest& req) override {
        if (req.token.empty()) {
            cout << "[Auth] DENIED: No token provided" << endl;
            return;   // stop the chain here
        }
        cout << "[Auth] Token valid: " << req.token << endl;
        Middleware::process(req);
    }
};

class RouteHandler : public Middleware {
public:
    void process(HttpRequest& req) override {
        cout << "[Route] Handling: " << req.path << endl;
    }
};

int main() {
    LoggingMiddleware logger;
    AuthMiddleware    auth;
    RouteHandler      handler;

    logger.setNext(&auth);
    auth.setNext(&handler);

    HttpRequest r1{"GET", "/dashboard", "bearer abc123"};
    HttpRequest r2{"POST", "/data", ""};  // no token

    cout << "=== Request 1 ===" << endl;
    logger.process(r1);

    cout << "\n=== Request 2 (no token) ===" << endl;
    logger.process(r2);
}
```

---

## Chain Flow Diagram

```
Request
  │
  ▼
Handler1.handle(req)
  │ Can handle?
  ├── YES → handle it, done
  └── NO  → pass to next
              │
              ▼
           Handler2.handle(req)
              │ Can handle?
              ├── YES → handle it, done
              └── NO  → pass to next
                          │
                          ▼
                       Handler3.handle(req)
                          │ Can handle?
                          ├── YES → handle it, done
                          └── NO  → end of chain → unhandled
```

---

## Pros and Cons

| ✅ Pros                                   | ❌ Cons                                               |
| ----------------------------------------- | ----------------------------------------------------- |
| Decouples sender from receiver            | No guarantee a request will be handled                |
| Add/remove handlers without changing code | Debugging can be tricky (hard to trace through chain) |
| Handlers are focused and single-purpose   | Performance overhead for long chains                  |
| Dynamic chain configuration at runtime    |                                                       |

---

> 💡 **Used in:** HTTP middleware pipelines (Express, Django), event bubbling in HTML DOM, logging levels (DEBUG → INFO → WARN → ERROR), ATM cash dispensing (try $50s, then $20s, then $10s).
