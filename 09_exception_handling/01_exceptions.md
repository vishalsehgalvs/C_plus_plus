# C++ Exception Handling

> Source: https://www.programiz.com/cpp-programming/exception-handling

---

## What Are Exceptions?

An **exception** is an unusual condition that happens during program execution — like dividing by zero, opening a file that doesn't exist, or running out of memory.

> 🔁 **Analogy:** Exceptions are like a fire alarm in a building. Normal program flow = people going about their day. An exception = fire alarm goes off. The program "throws" the alarm, and we "catch" it to handle it safely instead of letting the building burn down (crash).

**Without exception handling — crashes:**

```cpp
int a = 10, b = 0;
int result = a / b;  // crash! program terminates
cout << result;      // never runs
```

**With exception handling — graceful:**

```cpp
try {
    int result = a / b;  // might throw
    cout << result;
}
catch (exception &e) {
    cout << "Error: " << e.what() << endl;  // handle gracefully
}
```

---

## The `try-catch` Block

```
try {
    // code that might throw an exception
    // if exception occurs → jumps to catch
} catch (ExceptionType &e) {
    // code that handles the exception
}

Flow:
  ▼
try block starts
  ├── no exception → runs normally → skips catch
  └── exception thrown → jumps to matching catch block
```

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

int divide(int a, int b) {
    if (b == 0) {
        throw runtime_error("Division by zero!");  // throw exception
    }
    return a / b;
}

int main() {
    try {
        cout << divide(10, 2) << endl;   // 5 — no exception
        cout << divide(10, 0) << endl;   // throws!
        cout << "This never runs" << endl;
    }
    catch (runtime_error &e) {
        cout << "Caught: " << e.what() << endl;
        // Output: Caught: Division by zero!
    }

    cout << "Program continues normally" << endl;
    return 0;
}
```

---

## `throw` Statement

Throw **any type** as an exception:

```cpp
// Throw a string
throw "Something went wrong";

// Throw an int
throw 42;

// Throw a standard exception (preferred)
throw runtime_error("Descriptive error message");
throw invalid_argument("Parameter must be positive");
throw out_of_range("Index out of bounds");
throw overflow_error("Value too large");
```

---

## Multiple Catch Blocks

Handle different exceptions differently:

```cpp
void process(int choice) {
    if (choice == 1) throw runtime_error("Runtime error");
    if (choice == 2) throw invalid_argument("Bad argument");
    if (choice == 3) throw 99;         // throwing an int
    if (choice == 4) throw "Oops!";   // throwing a string
}

try {
    process(2);
}
catch (invalid_argument &e) {
    cout << "Invalid argument: " << e.what() << endl;
}
catch (runtime_error &e) {
    cout << "Runtime error: " << e.what() << endl;
}
catch (int code) {
    cout << "Error code: " << code << endl;
}
catch (const char *msg) {
    cout << "Message: " << msg << endl;
}
catch (...) {
    // Catch-all: handles any exception not caught above
    cout << "Unknown exception occurred!" << endl;
}
```

> ⚠️ Always put specific exceptions **before** the catch-all `catch(...)`.

---

## Standard Exception Hierarchy

```
std::exception
    ├── logic_error
    │       ├── invalid_argument   ← bad function argument
    │       ├── domain_error       ← math domain error
    │       ├── length_error       ← too long
    │       └── out_of_range       ← index out of range
    │
    └── runtime_error
            ├── overflow_error     ← arithmetic overflow
            ├── underflow_error    ← arithmetic underflow
            └── range_error        ← result out of range
```

All standard exceptions have the `.what()` method that returns an error description.

---

## Custom Exceptions

Create your own exception classes by inheriting from `std::exception`:

```cpp
#include <exception>
#include <string>
using namespace std;

class InsufficientFundsException : public exception {
private:
    string message;

public:
    InsufficientFundsException(double amount) {
        message = "Insufficient funds! Tried to withdraw $" + to_string(amount);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Using the custom exception
class BankAccount {
    double balance = 100.0;
public:
    void withdraw(double amount) {
        if (amount > balance) {
            throw InsufficientFundsException(amount);
        }
        balance -= amount;
    }
};

int main() {
    BankAccount acc;
    try {
        acc.withdraw(200.0);
    }
    catch (InsufficientFundsException &e) {
        cout << e.what() << endl;
        // Insufficient funds! Tried to withdraw $200.0
    }
}
```

---

## `finally` — There Is None!

C++ has no `finally` block (unlike Java/Python). Use **RAII** instead:

```cpp
// Problem: resource not released if exception occurs
void processFile() {
    FILE *f = fopen("data.txt", "r");
    // ... if exception here, fclose never called!
    fclose(f);  // ← might be skipped
}

// Solution: RAII — resource released in destructor
#include <fstream>
void processFileSafe() {
    ifstream file("data.txt");  // auto-closes when goes out of scope!
    // ... even if exception occurs, destructor closes file
}
```

> 💡 **RAII (Resource Acquisition Is Initialization):** Tie resource management to object lifetime. When the object is destroyed (even via exception), the destructor cleans up.

---

## `noexcept` Specifier

Mark functions that will **never throw**:

```cpp
int square(int n) noexcept {
    return n * n;
}
// Compiler can optimize; calling code knows it won't throw
```

---

## Exception Safety Levels

| Level            | Guarantee                                            |
| ---------------- | ---------------------------------------------------- |
| **No-throw**     | Function never throws (use `noexcept`)               |
| **Strong**       | Either completes fully or throws (no partial change) |
| **Basic**        | No resource leaks, but state may have changed        |
| **No guarantee** | Anything might happen (avoid!)                       |

---

## Key Takeaways

- `throw` sends an exception; `try-catch` handles it
- Any type can be thrown, but prefer `std::exception` subclasses (have `.what()` message)
- Multiple catch blocks: most specific types first, `catch(...)` last
- Standard exceptions: `runtime_error`, `invalid_argument`, `out_of_range` etc. from `<stdexcept>`
- Create custom exceptions by inheriting from `std::exception` and overriding `what()`
- C++ has no `finally` — use RAII (destructor handles cleanup)
- Mark functions `noexcept` if they will never throw — enables compiler optimizations
