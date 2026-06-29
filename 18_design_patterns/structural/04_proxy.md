# Proxy Pattern

**Category:** Structural

---

## What Is It?

The **Proxy** pattern provides a **substitute or placeholder** for another object. It controls access to the real object, allowing you to do something before/after the request reaches it.

> 🔁 **Analogy:** A receptionist at a company. When you want to meet the CEO, you don't walk straight to their office. The receptionist (proxy) checks if you have an appointment, logs your visit, and then lets you in — or doesn't. The CEO (real object) only deals with approved visitors.

---

## When to Use It?

| Proxy Type           | Use Case                                                 |
| -------------------- | -------------------------------------------------------- |
| **Virtual Proxy**    | Delay creation of expensive objects (lazy loading)       |
| **Protection Proxy** | Control access / permissions                             |
| **Remote Proxy**     | Represent object in another address space (RPC, network) |
| **Caching Proxy**    | Cache results of expensive operations                    |
| **Logging Proxy**    | Log all calls to the real object                         |

---

## Structure

```
Client ──────► Subject (interface)
                    △
            ┌───────┴───────┐
            │               │
         Proxy          RealSubject
         │ -realSubject*    │ +request()
         │ +request()       │  (does the actual work)
         │   │
         │   ├── pre-processing (check access, log, etc.)
         │   ├── realSubject->request()
         │   └── post-processing
         └──────────────────┘
```

---

## Virtual Proxy: Lazy Loading

```cpp
#include <iostream>
#include <string>
using namespace std;

// ============ Subject Interface ============
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() {}
};

// ============ Real Subject (expensive to load) ============
class RealImage : public Image {
    string filename;

    void loadFromDisk() {
        cout << "[RealImage] Loading from disk: " << filename << endl;
        // simulate expensive operation
    }

public:
    RealImage(const string& file) : filename(file) {
        loadFromDisk();   // loads immediately (expensive!)
    }

    void display() override {
        cout << "[RealImage] Displaying: " << filename << endl;
    }
};

// ============ Proxy (lazy loading) ============
class ProxyImage : public Image {
    string filename;
    RealImage* realImage = nullptr;   // not loaded yet

public:
    ProxyImage(const string& file) : filename(file) {
        cout << "[Proxy] Created proxy for: " << filename << " (no load yet)" << endl;
    }

    void display() override {
        // Only load the real image when display() is first called
        if (realImage == nullptr) {
            realImage = new RealImage(filename);   // lazy load
        }
        realImage->display();
    }

    ~ProxyImage() { delete realImage; }
};

int main() {
    cout << "Creating proxies (no disk load):" << endl;
    Image* img1 = new ProxyImage("photo1.jpg");
    Image* img2 = new ProxyImage("photo2.jpg");

    cout << "\nDisplaying img1 (loads now):" << endl;
    img1->display();

    cout << "\nDisplaying img1 again (already loaded):" << endl;
    img1->display();

    cout << "\nimg2 never displayed — never loaded from disk." << endl;

    delete img1;
    delete img2;
    return 0;
}
```

Output:

```
Creating proxies (no disk load):
[Proxy] Created proxy for: photo1.jpg (no load yet)
[Proxy] Created proxy for: photo2.jpg (no load yet)

Displaying img1 (loads now):
[RealImage] Loading from disk: photo1.jpg
[RealImage] Displaying: photo1.jpg

Displaying img1 again (already loaded):
[RealImage] Displaying: photo1.jpg

img2 never displayed — never loaded from disk.
```

---

## Protection Proxy: Access Control

```cpp
#include <iostream>
#include <string>
using namespace std;

// Subject
class BankAccount {
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual double getBalance() = 0;
    virtual ~BankAccount() {}
};

// Real subject
class RealBankAccount : public BankAccount {
    double balance;
public:
    RealBankAccount(double initial) : balance(initial) {}
    void deposit(double amount) override {
        balance += amount;
        cout << "[Bank] Deposited $" << amount << ". Balance: $" << balance << endl;
    }
    void withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;
            cout << "[Bank] Withdrew $" << amount << ". Balance: $" << balance << endl;
        } else {
            cout << "[Bank] Insufficient funds!" << endl;
        }
    }
    double getBalance() override { return balance; }
};

// Protection proxy
class BankAccountProxy : public BankAccount {
    RealBankAccount* account;
    string userRole;   // "admin", "user", "readonly"

public:
    BankAccountProxy(RealBankAccount* acc, const string& role)
        : account(acc), userRole(role) {}

    void deposit(double amount) override {
        if (userRole == "admin" || userRole == "user") {
            account->deposit(amount);
        } else {
            cout << "[Proxy] Access denied: deposit not allowed for " << userRole << endl;
        }
    }

    void withdraw(double amount) override {
        if (userRole == "admin") {
            account->withdraw(amount);
        } else {
            cout << "[Proxy] Access denied: withdraw not allowed for " << userRole << endl;
        }
    }

    double getBalance() override {
        // Everyone can read balance
        return account->getBalance();
    }
};

int main() {
    RealBankAccount* realAcc = new RealBankAccount(1000.0);

    cout << "=== Admin user ===" << endl;
    BankAccountProxy adminProxy(realAcc, "admin");
    adminProxy.deposit(500);
    adminProxy.withdraw(200);
    cout << "Balance: $" << adminProxy.getBalance() << endl;

    cout << "\n=== Readonly user ===" << endl;
    BankAccountProxy readonlyProxy(realAcc, "readonly");
    readonlyProxy.deposit(500);    // denied
    readonlyProxy.withdraw(100);   // denied
    cout << "Balance: $" << readonlyProxy.getBalance() << endl;  // allowed

    delete realAcc;
    return 0;
}
```

---

## Proxy Flowchart

```
Client calls proxy->operation()
              │
              ▼
       ┌────────────────┐
       │     Proxy      │
       │                │
       │  Pre-check:    │
       │  - authenticate│
       │  - log call    │
       │  - check cache │
       └────────┬───────┘
                │
         Access granted?
                │
        YES ────┘──── NO
         │                │
         ▼                ▼
  Real->operation()   Return error
         │             or cached
         │             value
         ▼
  Post-processing:
  - log result
  - cache result
  - measure time
         │
         ▼
  Return to client
```

---

## Pros and Cons

| ✅ Pros                                            | ❌ Cons                                  |
| -------------------------------------------------- | ---------------------------------------- |
| Lazy loading — don't pay for what you don't use    | Adds an indirection layer                |
| Access control without modifying real object       | Response may be slower (slight overhead) |
| Can cache expensive calls                          | Code gets more complex                   |
| Logging/monitoring without touching business logic |                                          |

---

> 💡 **Real-world uses:** Hibernate/JPA lazy-loaded entities, Spring AOP proxies, CDN caches, API gateway access control, `std::shared_ptr` reference counting.
