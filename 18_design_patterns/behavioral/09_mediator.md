# Mediator Pattern

**Category:** Behavioral

---

## What Is It?

The **Mediator** pattern defines an object that **encapsulates how a set of objects interact**. Instead of objects communicating directly, they all talk through the mediator.

> 🔁 **Analogy:** Air traffic control (ATC). Planes don't talk directly to each other ("Hey Flight 101, are you on runway 3?"). They all communicate through the ATC tower (mediator), which coordinates everything. This prevents chaos when many planes talk simultaneously.

---

## When to Use It?

- Many objects communicate in complex, hard-to-understand ways
- Reusing an object is difficult because it depends on too many other objects
- You want to reduce dependencies between many objects

---

## The Problem Without Mediator

```
Without Mediator (spaghetti communication):
A ←──────────────────────────────────────► B
│ ↘                                      ↗ │
│   ↘                                  ↗   │
│     ↘                              ↗     │
│       ↘                          ↗       │
└──────► C ◄────────────────────► D ◄──────┘
         │ ↘                    ↗ │
         └───► E ◄──────────► F ◄─┘

n objects → up to n*(n-1)/2 connections

With Mediator:
A ─┐                    ┌─ B
C ─┤──► Mediator (M) ◄──┤─ D
E ─┘                    └─ F

n objects → n connections (through mediator)
```

---

## Structure

```
Colleague (interface)
│ -mediator: Mediator*
│ +send(message)    → mediator->relay(this, message)
│ +receive(message)
└──────┬──────┐
    ColleagueA  ColleagueB

Mediator (interface)
│ +relay(Colleague*, message)
└── ConcreteMediator
    │ -colleagues: list<Colleague*>
    │ relay() → decides who gets the message
```

---

## C++ Implementation: Chat Room

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Forward declaration
class ChatMediator;

// ============ Colleague ============
class User {
protected:
    string name;
    ChatMediator* mediator;

public:
    User(const string& n, ChatMediator* m) : name(n), mediator(m) {}

    virtual void send(const string& message) = 0;
    virtual void receive(const string& from, const string& message) = 0;

    string getName() const { return name; }
    virtual ~User() {}
};

// ============ Mediator Interface ============
class ChatMediator {
public:
    virtual void addUser(User* user) = 0;
    virtual void relay(User* from, const string& message) = 0;
    virtual void relayTo(User* from, const string& to, const string& message) = 0;
    virtual ~ChatMediator() {}
};

// ============ Concrete Mediator ============
class ChatRoom : public ChatMediator {
    vector<User*> users;

public:
    void addUser(User* user) override {
        users.push_back(user);
        cout << "[ChatRoom] " << user->getName() << " joined." << endl;
    }

    // Broadcast to all
    void relay(User* from, const string& message) override {
        for (User* u : users) {
            if (u != from) {   // don't send back to sender
                u->receive(from->getName(), message);
            }
        }
    }

    // Send to specific user
    void relayTo(User* from, const string& to, const string& message) override {
        for (User* u : users) {
            if (u->getName() == to) {
                u->receive(from->getName(), "[DM] " + message);
                return;
            }
        }
        cout << "[ChatRoom] User '" << to << "' not found." << endl;
    }
};

// ============ Concrete Colleague ============
class ChatUser : public User {
public:
    ChatUser(const string& name, ChatMediator* m) : User(name, m) {}

    void send(const string& message) override {
        cout << name << " → (all): " << message << endl;
        mediator->relay(this, message);
    }

    void sendTo(const string& targetName, const string& message) {
        cout << name << " → " << targetName << ": " << message << endl;
        mediator->relayTo(this, targetName, message);
    }

    void receive(const string& from, const string& message) override {
        cout << "  [" << name << " received] " << from << ": " << message << endl;
    }
};

int main() {
    ChatRoom room;

    ChatUser alice("Alice", &room);
    ChatUser bob("Bob", &room);
    ChatUser charlie("Charlie", &room);

    room.addUser(&alice);
    room.addUser(&bob);
    room.addUser(&charlie);

    cout << "\n--- Broadcast ---" << endl;
    alice.send("Hello everyone!");

    cout << "\n--- Direct Message ---" << endl;
    bob.sendTo("Alice", "Hey Alice, how's it going?");

    cout << "\n--- Another Broadcast ---" << endl;
    charlie.send("Goodnight all!");

    return 0;
}
```

Output:

```
[ChatRoom] Alice joined.
[ChatRoom] Bob joined.
[ChatRoom] Charlie joined.

--- Broadcast ---
Alice → (all): Hello everyone!
  [Bob received] Alice: Hello everyone!
  [Charlie received] Alice: Hello everyone!

--- Direct Message ---
Bob → Alice: Hey Alice, how's it going?
  [Alice received] Bob: [DM] Hey Alice, how's it going?

--- Another Broadcast ---
Charlie → (all): Goodnight all!
  [Alice received] Charlie: Goodnight all!
  [Bob received] Charlie: Goodnight all!
```

---

## Real-World Example: Air Traffic Control

```cpp
class Plane;

class ATC {
public:
    virtual void report(Plane* plane, const string& msg) = 0;
    virtual ~ATC() {}
};

class Plane {
    string callSign;
    ATC* tower;
public:
    Plane(string sign, ATC* atc) : callSign(sign), tower(atc) {}

    void report(const string& msg) {
        cout << callSign << " → ATC: " << msg << endl;
        tower->report(this, msg);
    }

    void receive(const string& instruction) {
        cout << "  " << callSign << " ← ATC: " << instruction << endl;
    }

    string getCallSign() const { return callSign; }
};

class ControlTower : public ATC {
    vector<Plane*> planes;
public:
    void register_plane(Plane* p) { planes.push_back(p); }

    void report(Plane* from, const string& msg) override {
        // ATC coordinates and sends back instructions
        string response = "Acknowledged. Proceed to runway 2.";
        cout << "  [ATC] Processing report from " << from->getCallSign() << endl;
        from->receive(response);
    }
};
```

---

## Mediator vs Observer

```
Mediator:                         Observer:
────────────────────────────      ──────────────────────────────────
All colleagues talk to ONE        One subject notifies many observers
central mediator
                                  One-to-many relationship
Many-to-many communication
centralized                       Observers are passive recipients

Mediator has complex logic        Subject doesn't coordinate responses
to coordinate responses
```

---

## Pros and Cons

| ✅ Pros                              | ❌ Cons                                           |
| ------------------------------------ | ------------------------------------------------- |
| Loose coupling between colleagues    | Mediator can become a "god object"                |
| Centralized control logic            | Single point of failure                           |
| Easy to add/remove colleagues        | Can be hard to understand complex mediation logic |
| Reduces dependencies between objects |                                                   |

---

> 💡 **Used in:** Chat applications, ATC systems, GUI frameworks (button clicks coordinated by form), game AI (agents communicate through a coordinator), microservices (API gateway as mediator).
