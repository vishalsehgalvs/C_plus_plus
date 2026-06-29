# Preprocessor Directives

> Source reference: https://www.tutorialspoint.com/cplusplus/cpp_preprocessor.htm

---

## What Is the Preprocessor?

Before your C++ code gets compiled, a special program called the **preprocessor** runs first. It processes all lines that start with `#` — these are called **preprocessor directives**.

> 🔁 **Analogy:** The preprocessor is like a text editor that runs on your code _before_ the compiler reads it. It does find-and-replace, copy-pasting, and conditional skipping — all before the real compilation starts.

```
Your .cpp file
     │
     ▼
┌────────────────┐
│  PREPROCESSOR  │  ← handles all #lines
│  • #include    │
│  • #define     │
│  • #ifdef      │
└────────────────┘
     │
     ▼
Expanded .cpp (intermediate)
     │
     ▼
┌────────────────┐
│   COMPILER     │  ← now compiles the expanded code
└────────────────┘
     │
     ▼
  .exe / .o
```

---

## `#include` — Copy-Paste a File

`#include` tells the preprocessor: "copy the contents of this file right here."

```cpp
#include <iostream>     // angle brackets = system library
#include "myfile.h"     // quotes = your own file
```

```
Before preprocessing:         After preprocessing:
──────────────────────        ─────────────────────────────────────
#include <iostream>     →     [entire contents of iostream pasted here]
int main() { ... }            int main() { ... }
```

> 💡 This is why you can use `cout`, `cin`, etc. — their declarations live in `iostream` and get pasted into your file.

---

## `#define` — Create a Macro (Constant or Mini-Function)

### Constant Macros

```cpp
#define PI 3.14159
#define MAX_SIZE 100
#define APP_NAME "MyApp"

int main() {
    double area = PI * r * r;    // PI gets replaced with 3.14159
    int arr[MAX_SIZE];           // MAX_SIZE replaced with 100
}
```

> ⚠️ `#define` is a **text substitution** — it has no type! The compiler never sees `PI`, it only sees `3.14159`. Prefer `const` or `constexpr` in modern C++.

### Function-Like Macros

```cpp
#define SQUARE(x)    ((x) * (x))
#define MAX(a, b)    ((a) > (b) ? (a) : (b))
#define MIN(a, b)    ((a) < (b) ? (a) : (b))

int main() {
    cout << SQUARE(5);        // → ((5) * (5)) = 25
    cout << MAX(10, 20);      // → ((10) > (20) ? (10) : (20)) = 20
}
```

> ⚠️ **Parentheses are critical!** Without them:
>
> ```cpp
> #define BAD_SQUARE(x)  x * x
> BAD_SQUARE(2 + 3)  →  2 + 3 * 2 + 3 = 11  ❌ (should be 25)
> ```

---

## Conditional Compilation — `#ifdef`, `#ifndef`, `#if`, `#else`, `#endif`

This lets you include or skip chunks of code based on conditions — very useful for platform-specific code or debug builds.

```
#ifdef DEBUG
    ┌──────────────────┐
    │ compile this code │  ← only if DEBUG is defined
    └──────────────────┘
#else
    ┌──────────────────┐
    │ compile this code │  ← only if DEBUG is NOT defined
    └──────────────────┘
#endif
```

### Example: Debug Logging

```cpp
#define DEBUG    // comment this out to disable debug logs

#include <iostream>
using namespace std;

int main() {
    int x = 42;

#ifdef DEBUG
    cout << "[DEBUG] x = " << x << endl;    // only compiled in debug mode
#endif

    cout << "Program running..." << endl;
    return 0;
}
```

### Example: Platform-Specific Code

```cpp
#ifdef _WIN32
    cout << "Running on Windows" << endl;
#elif defined(__linux__)
    cout << "Running on Linux" << endl;
#elif defined(__APPLE__)
    cout << "Running on Mac" << endl;
#else
    cout << "Unknown platform" << endl;
#endif
```

### `#ifndef` — "If Not Defined" (Header Guards)

The most common use of `#ifndef` is **header guards** — preventing a file from being included twice:

```cpp
// myclass.h
#ifndef MYCLASS_H     // if MYCLASS_H is NOT defined...
#define MYCLASS_H     // ...define it, then include this content

class MyClass {
public:
    void greet();
};

#endif                // end of guard
```

```
First #include "myclass.h"  → MYCLASS_H not defined → include content → define MYCLASS_H
Second #include "myclass.h" → MYCLASS_H IS defined  → skip everything → no duplicate!
```

> 💡 Modern C++ alternative: `#pragma once` (one line at the top of the header — does the same thing)

---

## `#undef` — Remove a Definition

```cpp
#define TEMP 100
cout << TEMP;     // 100

#undef TEMP       // remove the definition

// cout << TEMP;  // ERROR: TEMP is no longer defined
```

---

## `#pragma` — Compiler-Specific Instructions

`#pragma` gives special instructions to the compiler. The most common ones:

```cpp
#pragma once              // header guard (modern alternative to #ifndef)
#pragma warning(disable : 4996)   // suppress specific warnings (MSVC)
#pragma pack(1)           // change struct memory alignment
```

> ⚠️ `#pragma` directives are **not standard** — they vary between compilers (MSVC, GCC, Clang). Use with caution.

---

## Predefined Macros

The compiler provides these macros automatically — you don't define them:

| Macro         | Meaning             | Example           |
| ------------- | ------------------- | ----------------- |
| `__FILE__`    | Current file name   | `"main.cpp"`      |
| `__LINE__`    | Current line number | `42`              |
| `__DATE__`    | Compilation date    | `"Jun 29 2026"`   |
| `__TIME__`    | Compilation time    | `"14:30:00"`      |
| `__cplusplus` | C++ version number  | `201703L` (C++17) |

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "File: " << __FILE__ << endl;
    cout << "Line: " << __LINE__ << endl;
    cout << "Compiled on: " << __DATE__ << " at " << __TIME__ << endl;
    cout << "C++ version: " << __cplusplus << endl;
    return 0;
}
```

Output:

```
File: main.cpp
Line: 6
Compiled on: Jun 29 2026 at 14:30:00
C++ version: 201703
```

---

## Stringification (`#`) and Token Pasting (`##`)

Advanced macro tricks:

```cpp
// # turns the argument into a string literal
#define TOSTRING(x)  #x
cout << TOSTRING(hello world);  // prints: hello world

// ## pastes two tokens together
#define MAKE_VAR(name, num)  name##num
int MAKE_VAR(x, 1) = 10;   // creates variable: x1
int MAKE_VAR(x, 2) = 20;   // creates variable: x2
```

---

## Full Flowchart: What Preprocessor Does to Your File

```
Source Code (.cpp)
       │
       ▼
  ┌──────────────────────────────────────────┐
  │  PREPROCESSOR PASS                       │
  │                                          │
  │  1. #include  → paste file contents      │
  │  2. #define   → text replacement         │
  │  3. #ifdef/   → remove skipped blocks    │
  │     #ifndef                              │
  │  4. #undef    → remove definition        │
  │  5. #pragma   → pass hint to compiler    │
  └──────────────────────────────────────────┘
       │
       ▼
  Translation Unit (preprocessed code)
       │
       ▼
  COMPILER (sees no # directives, only pure C++)
```

---

## Quick Summary

| Directive                            | Purpose                                      |
| ------------------------------------ | -------------------------------------------- |
| `#include`                           | Paste another file here                      |
| `#define`                            | Create a macro (constant or function-like)   |
| `#undef`                             | Remove a macro                               |
| `#ifdef` / `#ifndef`                 | Compile block only if macro is/isn't defined |
| `#if` / `#elif` / `#else` / `#endif` | Full conditional compilation                 |
| `#pragma once`                       | Include this file only once (header guard)   |
| `#pragma`                            | Compiler-specific hints                      |
| `__FILE__`, `__LINE__`               | Built-in info macros                         |

> 💡 **Rule of thumb:** In modern C++, prefer `const`, `constexpr`, and `inline` over `#define` for constants. Use `#define` mainly for header guards and conditional compilation.
