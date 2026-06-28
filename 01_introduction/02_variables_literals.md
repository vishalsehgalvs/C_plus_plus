# C++ Variables, Literals & Constants

> Source: https://www.programiz.com/cpp-programming/variables-literals

---

## What Is a Variable?

A variable is a **named storage location in memory** that holds a value you can use and change.

> 🔁 **Analogy:** A variable is like a labeled box. The label is the variable name, and whatever is inside the box is the value. You can look inside, change the contents, or empty the box.

```
Memory:
┌─────────────────────────────────────────────────┐
│  [ age = 25 ]   [ price = 9.99 ]   [ name = A ]│
│     int            double              char      │
└─────────────────────────────────────────────────┘
       ↑                ↑                  ↑
    variable          variable           variable
```

---

## Declaring and Initializing Variables

```cpp
#include <iostream>
using namespace std;

int main() {
    // Declaration (reserve memory, no value yet)
    int age;

    // Initialization (assign a value)
    age = 25;

    // Declaration + Initialization (both at once — preferred)
    int score = 100;
    double price = 9.99;
    char grade = 'A';
    bool isActive = true;

    // Multiple variables of same type
    int x = 1, y = 2, z = 3;

    cout << "Age: " << age << endl;
    cout << "Score: " << score << endl;
    cout << "Price: " << price << endl;
    cout << "Grade: " << grade << endl;

    return 0;
}
```

**Output:**
```
Age: 25
Score: 100
Price: 9.99
Grade: A
```

---

## Variable Naming Rules

```cpp
// ✅ Valid variable names
int age;
int myAge;
int my_age;
int age2;
int _secret;
int camelCaseWorks;

// ❌ Invalid variable names
int 2age;         // cannot start with a number
int my-age;       // hyphens not allowed
int int;          // "int" is a reserved keyword
int my age;       // spaces not allowed
```

### Naming conventions used in practice:

| Style | Example | Used in |
|-------|---------|---------|
| camelCase | `myVariable` | Functions, variables |
| snake_case | `my_variable` | Standard library, C-style |
| PascalCase | `MyClass` | Classes, structs |
| UPPER_CASE | `MAX_SIZE` | Constants |

---

## Literals: Fixed Values in Code

A **literal** is a fixed value written directly in code — it doesn't come from a variable.

```cpp
int a = 10;          // 10 is an integer literal
double pi = 3.14159; // 3.14159 is a floating-point literal
char c = 'Z';        // 'Z' is a character literal
bool flag = true;    // true is a boolean literal
string s = "Hello";  // "Hello" is a string literal
```

### Types of integer literals:

```cpp
int decimal     = 42;       // base 10 (normal)
int octal       = 052;      // base 8  (starts with 0)
int hexadecimal = 0x2A;     // base 16 (starts with 0x)
int binary      = 0b101010; // base 2  (C++14, starts with 0b)

// All of these equal 42!
```

### Floating-point literal suffixes:

```cpp
double d = 3.14;    // double (default)
float  f = 3.14f;   // float  (f suffix)
long double ld = 3.14L; // long double (L suffix)
```

### Escape sequences in character/string literals:

| Escape | Meaning |
|--------|---------|
| `\n` | newline |
| `\t` | tab |
| `\\` | backslash |
| `\"` | double quote |
| `\'` | single quote |
| `\0` | null character |

```cpp
cout << "Line 1\nLine 2\n";   // two lines
cout << "Name:\t\"Alice\"";   // tab + quoted name
```

---

## Constants: Variables That Never Change

Use `const` to declare a variable whose value cannot be modified after initialization.

```cpp
const double PI = 3.14159265;
const int MAX_SIZE = 100;
const string APP_NAME = "MyCoolApp";

PI = 3.0;  // ❌ ERROR: cannot change a const
```

> 💡 **Best practice:** Use `const` whenever you know a value won't change. It prevents bugs and helps the compiler optimize.

### `#define` vs `const`

```cpp
// Old C-style (avoid in modern C++)
#define PI 3.14159
#define MAX 100

// Modern C++ (preferred)
const double PI = 3.14159;
const int MAX = 100;
```

Prefer `const` over `#define` — it has type safety and plays nicely with debuggers.

### `constexpr` (Compile-Time Constant)

```cpp
constexpr int BOARD_SIZE = 8;     // evaluated at compile time
constexpr double GRAVITY = 9.81;  // faster than runtime const
```

---

## Variable Scope

Where you declare a variable determines where you can use it:

```
┌──────────────── Global Scope ───────────────────┐
│  int globalVar = 10;                             │
│                                                  │
│  int main() {                                    │
│  ┌─────────── Function Scope ──────────────┐    │
│  │  int localVar = 5;  // only here        │    │
│  │                                          │    │
│  │  if (true) {                             │    │
│  │  ┌──────── Block Scope ──────────────┐  │    │
│  │  │  int blockVar = 1;  // only here  │  │    │
│  │  └───────────────────────────────────┘  │    │
│  │  // blockVar is GONE here               │    │
│  └──────────────────────────────────────── ┘    │
│  }                                               │
└──────────────────────────────────────────────────┘
```

```cpp
int globalVar = 10;    // accessible everywhere

int main() {
    int localVar = 5;  // only in main()

    {
        int blockVar = 1;  // only in this block
        cout << blockVar;  // ✅ works
    }
    // cout << blockVar;   // ❌ out of scope!

    cout << globalVar;     // ✅ works anywhere
    return 0;
}
```

---

## Key Takeaways

- Variables are named memory locations; declare them with a type: `int x = 5;`
- Literals are fixed values written directly in code (`42`, `3.14`, `'A'`, `"hello"`)
- Use `const` for values that shouldn't change — safer and faster than regular variables
- Variable names can't start with numbers, contain spaces/hyphens, or use reserved keywords
- Scope determines where a variable is accessible — block scope, function scope, global scope
- Prefer camelCase for variables, UPPER_CASE for constants, PascalCase for classes
