# Namespaces in C++

> Source reference: https://www.tutorialspoint.com/cplusplus/cpp_namespaces.htm

---

## What Is a Namespace?

A **namespace** is a container that groups related code (functions, classes, variables) under a name to **avoid naming conflicts**.

> 🔁 **Analogy:** Imagine two people both named "John" in the same office. You distinguish them by department: "John from HR" vs "John from Engineering". Namespaces do the same — `Math::add()` vs `Physics::add()` can both exist without conflict.

```
Without namespaces:                With namespaces:
─────────────────────────         ─────────────────────────────
int add(int a, int b);   ←──┐    namespace Math {
int add(float a, float b); ←┘     int add(int a, int b);
// CONFLICT! Same name             double add(double a, double b);
                                  }
                                  namespace Physics {
                                   int add(int a, int b);  // OK!
                                  }
```

---

## Defining a Namespace

```cpp
#include <iostream>
using namespace std;

namespace Math {
    const double PI = 3.14159;

    int add(int a, int b) {
        return a + b;
    }

    double circleArea(double r) {
        return PI * r * r;
    }
}

int main() {
    cout << Math::PI << endl;                 // 3.14159
    cout << Math::add(3, 4) << endl;          // 7
    cout << Math::circleArea(5.0) << endl;    // 78.539
    return 0;
}
```

The `::` is called the **scope resolution operator** — it means "look inside this namespace".

---

## The `using` Directive

Instead of writing `Math::` every time, you can bring names into scope:

### `using namespace` — Bring Everything In

```cpp
using namespace Math;   // bring all of Math into scope

int main() {
    cout << PI;           // no need for Math::
    cout << add(3, 4);    // works directly
}
```

> ⚠️ **Avoid `using namespace std;` in header files!** It pollutes the global namespace for anyone who includes your header.

### `using` — Bring a Single Name In

```cpp
using Math::PI;         // only bring PI

int main() {
    cout << PI;         // works
    cout << add(1, 2);  // ERROR: add not brought in
    cout << Math::add(1, 2);  // must still use qualifier
}
```

---

## Namespace Resolution Flowchart

```
You write: add(1, 2)
               │
               ▼
   Is there a local variable/function called add?
               │
        Yes ───┘─── No
         │              │
         ▼              ▼
      Use it      Check current namespace
                        │
                 Found? ─── Yes → Use it
                        │
                        No
                        │
                        ▼
              Check using namespace declarations
                        │
                 Found? ─── Yes → Use it
                        │
                        No
                        │
                        ▼
                 Check global namespace
                        │
                 Found? ─── Yes → Use it
                        │
                        No
                        │
                        ▼
                   COMPILE ERROR ❌
```

---

## Nested Namespaces

Namespaces can be nested inside each other:

```cpp
namespace Company {
    namespace HR {
        void printPolicy() {
            cout << "HR Policy" << endl;
        }
    }

    namespace Engineering {
        void buildApp() {
            cout << "Building app..." << endl;
        }
    }
}

int main() {
    Company::HR::printPolicy();
    Company::Engineering::buildApp();
}
```

### C++17 Shorthand for Nested Namespaces

```cpp
// C++11 way (verbose):
namespace Company {
    namespace Engineering {
        namespace Backend { ... }
    }
}

// C++17 way (clean):
namespace Company::Engineering::Backend {
    void deploy() { ... }
}
```

---

## Namespace Aliases

Long namespace names can be aliased:

```cpp
namespace VeryLongCompanyNameEngineering = Company::Engineering;

// Now use the short alias
VeryLongCompanyNameEngineering::buildApp();
```

---

## Anonymous (Unnamed) Namespaces

An anonymous namespace makes its contents available only within the **current file** — essentially the same as `static` at file scope:

```cpp
namespace {    // no name!
    int secretValue = 42;

    void helperFunction() {
        cout << "Internal helper" << endl;
    }
}

int main() {
    cout << secretValue << endl;    // works — same file
    helperFunction();               // works — same file
}
// secretValue and helperFunction NOT accessible from other .cpp files
```

> 💡 **Use anonymous namespaces** instead of `static` for file-local variables and functions in modern C++.

---

## `std` Namespace — The Standard Library

Everything in the C++ standard library lives in the `std` namespace:

```
std::
 ├── cout, cin, endl     (iostream)
 ├── string              (string)
 ├── vector              (vector)
 ├── map, set            (map, set)
 ├── sort, find          (algorithm)
 ├── runtime_error       (stdexcept)
 └── ... hundreds more
```

```cpp
// Full qualification (recommended in headers):
std::cout << "Hello" << std::endl;
std::vector<int> v = {1, 2, 3};

// using directive (OK in .cpp files):
using namespace std;
cout << "Hello" << endl;
vector<int> v = {1, 2, 3};
```

---

## Extending a Namespace

You can spread a namespace across multiple files or add to it later:

```cpp
// file1.cpp
namespace Math {
    int add(int a, int b) { return a + b; }
}

// file2.cpp — same namespace, extended
namespace Math {
    int multiply(int a, int b) { return a * b; }
}
// Both add and multiply are now in Math
```

---

## Quick Summary

| Concept          | Syntax                          | Purpose                 |
| ---------------- | ------------------------------- | ----------------------- |
| Define namespace | `namespace Name { ... }`        | Group related code      |
| Access member    | `Name::member`                  | Qualify which namespace |
| Bring all names  | `using namespace Name;`         | Skip writing `Name::`   |
| Bring one name   | `using Name::member;`           | Import single name      |
| Nested           | `namespace A::B { }`            | Sub-grouping (C++17)    |
| Alias            | `namespace short = Long::Name;` | Rename for convenience  |
| Anonymous        | `namespace { }`                 | File-private code       |

> 💡 **Best practice:** Use full qualification (`std::cout`) in headers. In `.cpp` files, `using` directives are fine.
