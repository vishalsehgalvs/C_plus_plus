# Singleton Pattern

**Category:** Creational

---

## What Is It?

The **Singleton** pattern ensures that a class has **only one instance** and provides a global point of access to it.

> 🔁 **Analogy:** The president of a country — there's only ONE president at a time, and everyone refers to the same person when they say "the president". No matter how many times you ask "who's the president?", you get the same one person.

---

## When to Use It?

- **Logger** — you want all parts of your app writing to the same log file
- **Config manager** — one place that holds all configuration
- **Database connection pool** — share a limited number of connections
- **Thread pool** — single shared pool of worker threads

---

## Structure

```
┌─────────────────────────────────┐
│          Singleton              │
├─────────────────────────────────┤
│ - instance: Singleton* (static) │  ← the one and only instance
│ - Singleton() (private)         │  ← can't call new from outside
├─────────────────────────────────┤
│ + getInstance(): Singleton*     │  ← the only way to get it
│ + doSomething()                 │  ← actual functionality
└─────────────────────────────────┘
         │
         │ all callers get THIS same object
         ▼
   Client A ──┐
   Client B ──┼──► getInstance() ──► same instance
   Client C ──┘
```

---

## Basic Implementation

```cpp
#include <iostream>
using namespace std;

class Singleton {
private:
    // 1. Static pointer to the single instance
    static Singleton* instance;

    // 2. Private constructor — prevents direct instantiation
    Singleton() {
        cout << "Singleton created!" << endl;
    }

    // 3. Delete copy constructor and assignment — prevents copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // 4. Static method — the only way to get the instance
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();   // create only once
        }
        return instance;
    }

    void doWork() {
        cout << "Singleton doing work at address: " << this << endl;
    }
};

// Initialize static member
Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    Singleton* s3 = Singleton::getInstance();

    s1->doWork();
    s2->doWork();
    s3->doWork();

    // All three point to the SAME object
    cout << "Same instance? " << (s1 == s2 && s2 == s3 ? "YES" : "NO") << endl;

    return 0;
}
```

Output:

```
Singleton created!        ← only once!
Singleton doing work at address: 0x1a2b3c4d
Singleton doing work at address: 0x1a2b3c4d
Singleton doing work at address: 0x1a2b3c4d
Same instance? YES
```

---

## Modern C++11 Implementation (Thread-Safe, Meyer's Singleton)

```cpp
class Singleton {
private:
    Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance() {
        // Static local — initialized once, thread-safe since C++11
        static Singleton instance;
        return instance;
    }

    void doWork() {
        cout << "Working!" << endl;
    }
};

int main() {
    Singleton::getInstance().doWork();
    Singleton::getInstance().doWork();
    // Same instance, guaranteed
}
```

> 💡 This is the **preferred modern approach** — the C++11 standard guarantees this is thread-safe.

---

## Real-World Example: Logger

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Logger {
private:
    ofstream logFile;
    int messageCount;

    Logger() : messageCount(0) {
        logFile.open("app.log", ios::app);
        log("Logger initialized");
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const string& message) {
        messageCount++;
        cout << "[LOG #" << messageCount << "] " << message << endl;
        if (logFile.is_open()) {
            logFile << "[LOG #" << messageCount << "] " << message << "\n";
        }
    }

    ~Logger() {
        log("Logger shutting down");
        logFile.close();
    }
};

// Usage across different parts of the application
void moduleA() {
    Logger::getInstance().log("Module A started");
}

void moduleB() {
    Logger::getInstance().log("Module B doing work");
}

int main() {
    Logger::getInstance().log("Application starting");
    moduleA();
    moduleB();
    Logger::getInstance().log("Application done");
    return 0;
}
```

Output:

```
[LOG #1] Logger initialized
[LOG #2] Application starting
[LOG #3] Module A started
[LOG #4] Module B doing work
[LOG #5] Application done
[LOG #6] Logger shutting down
```

---

## Flowchart: `getInstance()` Logic

```
Call getInstance()
        │
        ▼
  instance == nullptr?
        │
   YES ─┘── NO
    │            │
    ▼            │
 Create new      │
 Singleton()     │
    │            │
    └────────────┘
        │
        ▼
  Return instance
```

---

## Pros and Cons

| ✅ Pros                                         | ❌ Cons                                                    |
| ----------------------------------------------- | ---------------------------------------------------------- |
| Only one instance guaranteed                    | Global state — can be hard to test                         |
| Lazy initialization (created when first needed) | Can cause hidden dependencies                              |
| Easy global access                              | Thread safety needs care (use Meyer's)                     |
| Saves resources (shared connection, log file)   | Violates Single Responsibility (manages itself + its work) |

---

> 💡 **Rule of thumb:** Singleton is one of the most overused patterns. Before using it, ask: "Do I truly need only one instance, or am I just being lazy about passing the object around?"
