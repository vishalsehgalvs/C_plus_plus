# C++ Scope, Storage Classes & Recursion

> Source: https://www.programiz.com/cpp-programming/storage-class

---

## Scope

**Scope** determines where a variable is visible and accessible.

> 🔁 **Analogy:** Scope is like the walls of a room. Variables inside a room can't be seen from outside. But if you're in the living room (global scope), everyone in the house can see you.

### Types of Scope

```
┌─────────────────── Global Scope ───────────────────────┐
│  int globalVar = 100;    // accessible everywhere       │
│                                                         │
│  void functionA() {                                     │
│  ┌────── Function Scope ──────────────────────────┐    │
│  │  int localVar = 5;  // only in functionA        │    │
│  │                                                  │    │
│  │  for (int i = 0; i < 3; i++) {                  │    │
│  │  ┌──── Block Scope ────────────────────────┐   │    │
│  │  │  int blockVar = i;  // only in this for │   │    │
│  │  └─────────────────────────────────────────┘   │    │
│  │  // blockVar is GONE here                       │    │
│  └──────────────────────────────────────────────── ┘    │
│  }                                                       │
└─────────────────────────────────────────────────────────┘
```

```cpp
int globalVar = 100;   // global — accessible everywhere

void example() {
    int localVar = 5;  // local — only in this function

    {
        int blockVar = 1;  // block — only in this block
        cout << blockVar;  // ✅
    }
    // cout << blockVar;   // ❌ Error: out of scope

    cout << globalVar;     // ✅ can access global
    cout << localVar;      // ✅ can access local
}
```

### Variable Shadowing

When a local variable has the same name as a global:

```cpp
int x = 100;  // global

void foo() {
    int x = 50;    // local — shadows the global x
    cout << x;     // prints 50 (local)
    cout << ::x;   // prints 100 (global, using :: scope resolution)
}
```

---

## Storage Classes

Storage classes control a variable's **lifetime** (how long it exists) and **linkage** (where it can be accessed).

### 1. `auto` (default for local variables)

```cpp
void func() {
    auto x = 10;  // same as: int x = 10;
    // Created when function is called
    // Destroyed when function returns
}
```

### 2. `static` — Persists Between Calls

A `static` local variable keeps its value between function calls:

```cpp
void counter() {
    static int count = 0;  // initialized only ONCE
    count++;
    cout << count << endl;
}

counter();  // 1
counter();  // 2
counter();  // 3
// count persists! not reset to 0 each call
```

> 🔁 **Analogy:** A regular local variable is like a whiteboard erased after each meeting. A `static` variable is like a notebook that carries information from meeting to meeting.

Static member variables in classes (covered in OOP section) work the same — one shared copy for all instances.

### 3. `extern` — Share Across Files

When you have multiple `.cpp` files and want to share a global variable:

```cpp
// file1.cpp
int sharedValue = 42;   // defined here

// file2.cpp
extern int sharedValue;  // declared (not defined) — uses file1's variable
cout << sharedValue;     // 42
```

### 4. `register` (Deprecated in C++17)

Old hint to store variable in CPU register. Modern compilers ignore it and optimize automatically. Mentioned only for reference.

### 5. `mutable` (for class members)

Allows a member to be changed even in a `const` member function:

```cpp
class Logger {
    mutable int callCount = 0;  // can change even in const methods
public:
    void log(string msg) const {
        callCount++;  // ✅ allowed because mutable
        cout << msg;
    }
};
```

---

## Recursion Deep Dive

A function that **calls itself** to solve a problem by breaking it into smaller versions of the same problem.

### Anatomy of Recursion

```
Every recursive function MUST have:
1. Base case   — when to STOP (prevents infinite recursion)
2. Recursive case — calling itself with a SMALLER problem
```

```
fibonacci(5)
    ├── fibonacci(4)
    │       ├── fibonacci(3)
    │       │       ├── fibonacci(2)
    │       │       │       ├── fibonacci(1) ← base case: return 1
    │       │       │       └── fibonacci(0) ← base case: return 0
    │       │       └── fibonacci(1) ← base case: return 1
    │       └── fibonacci(2)
    │               ├── fibonacci(1) ← return 1
    │               └── fibonacci(0) ← return 0
    └── fibonacci(3)
            ...
```

### Examples:

```cpp
// Factorial: n! = n × (n-1) × ... × 1
int factorial(int n) {
    if (n <= 1) return 1;          // base case
    return n * factorial(n - 1);   // recursive case
}
// factorial(5) = 5 × 4 × 3 × 2 × 1 = 120

// Sum of digits
int digitSum(int n) {
    if (n < 10) return n;             // single digit: base case
    return n % 10 + digitSum(n / 10); // last digit + sum of rest
}
// digitSum(123) = 3 + 2 + 1 = 6

// Fibonacci
int fib(int n) {
    if (n <= 1) return n;             // base: fib(0)=0, fib(1)=1
    return fib(n - 1) + fib(n - 2);  // recursive
}
// fib(6) = 0 1 1 2 3 5 8 → 8
```

### Recursion vs Iteration:

```cpp
// Recursive factorial
int factRecursive(int n) {
    if (n <= 1) return 1;
    return n * factRecursive(n - 1);
}

// Iterative factorial
int factIterative(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
```

|             | Recursion               | Iteration              |
| ----------- | ----------------------- | ---------------------- |
| Readability | ✅ Often cleaner        | Depends                |
| Memory      | ❌ Uses call stack      | ✅ O(1)                |
| Risk        | ❌ Stack overflow       | Low                    |
| Speed       | Slower (call overhead)  | Faster                 |
| Best for    | Trees, divide & conquer | Loops with known count |

> ⚠️ **Stack overflow:** Each recursive call adds to the call stack. Deep recursion (10,000+ levels) will crash your program. Always ensure a base case exists!

---

## Key Takeaways

- **Scope** controls where variables are visible: global (everywhere), local (function), block (within `{}`)
- `::` accesses global scope when shadowed by a local variable
- `static` local variable: initialized once, persists across function calls
- `extern` shares a global variable across multiple source files
- **Recursion** = function calling itself with a smaller problem; always needs a **base case**
- Recursion is elegant for tree/divide-and-conquer problems but uses more stack memory
- For simple loops, prefer iteration over recursion (faster, no stack overflow risk)
