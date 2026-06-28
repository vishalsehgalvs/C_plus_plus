# C++ Functions

> Source: https://www.programiz.com/cpp-programming/function

---

## What Is a Function?

A function is a **named, reusable block of code** that performs a specific task. You define it once and call it as many times as you need.

> 🔁 **Analogy:** A function is like a recipe. You write the recipe once ("how to make pasta"), then anyone can follow it anytime. You don't rewrite the recipe each time you cook.

**Benefits:**
- **Reusability** — write once, use many times
- **Readability** — break large programs into small, named pieces
- **Maintainability** — fix a bug in one place, not everywhere
- **Testing** — test each function independently

---

## Anatomy of a Function

```
return_type  function_name (parameters)
     │             │              │
     │             │              └── inputs the function accepts
     │             └── what you call it
     └── type of value it returns (void = nothing)

Example:
    int    add        (int a, int b)
    ─────  ───        ───────────────
    returns int  named "add"  takes two ints
```

```cpp
// Function definition
int add(int a, int b) {
    return a + b;   // return sends value back to caller
}

// Calling the function
int result = add(3, 5);  // result = 8
cout << result;
```

---

## Parts of a Function

```cpp
// 1. Declaration (prototype) — tells compiler the function exists
int multiply(int a, int b);   // no body, just signature

// 2. Definition — the actual code
int multiply(int a, int b) {
    return a * b;
}

// 3. Call — using the function
int x = multiply(4, 5);   // x = 20
```

> 💡 If you define a function **before** `main()`, you don't need a declaration. If it's **after** `main()`, you need a declaration (forward declaration) at the top.

---

## Function Return Types

```cpp
// Returns an int
int square(int n) {
    return n * n;
}

// Returns a double
double average(double a, double b) {
    return (a + b) / 2.0;
}

// Returns nothing (void)
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
    // no return needed (or use bare "return;")
}

// Returns a bool
bool isEven(int n) {
    return n % 2 == 0;
}
```

---

## Parameters vs Arguments

```
Parameters: placeholders in function definition
Arguments:  actual values you pass when calling

int add(int a, int b)   ← a, b are PARAMETERS
    add(3, 5)           ← 3, 5 are ARGUMENTS
```

### Pass by Value (default)

The function gets a **copy** — changes don't affect the original:

```cpp
void doubleIt(int n) {
    n = n * 2;  // modifies only the LOCAL copy
}

int x = 5;
doubleIt(x);
cout << x;  // still 5! original unchanged
```

### Pass by Reference

The function gets the **actual variable** — changes DO affect the original:

```cpp
void doubleIt(int &n) {  // & = reference
    n = n * 2;  // modifies the ORIGINAL
}

int x = 5;
doubleIt(x);
cout << x;  // now 10! original changed
```

### Pass by Const Reference (for read-only)

Safe and efficient for large objects (no copy, no modification):

```cpp
void printName(const string &name) {
    cout << name;
    // name = "other";  // ❌ error — const prevents modification
}
```

---

## Default Arguments

Provide default values so callers can skip some arguments:

```cpp
void greet(string name, string msg = "Hello") {
    cout << msg << ", " << name << "!" << endl;
}

greet("Alice");            // Hello, Alice!
greet("Bob", "Hey");       // Hey, Bob!
```

> ⚠️ Default arguments must be at the **right side** of the parameter list:
```cpp
void f(int a, int b = 5, int c = 10);  // ✅ valid
void f(int a = 5, int b, int c = 10);  // ❌ error
```

---

## Function Overloading

Multiple functions with the **same name** but different parameter types or counts:

```cpp
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

cout << add(1, 2);         // calls int version    → 3
cout << add(1.5, 2.5);     // calls double version → 4.0
cout << add(1, 2, 3);      // calls 3-param version → 6
```

> C++ picks the right version based on the arguments you pass (called **overload resolution**).

---

## Recursive Functions

A function that **calls itself**:

```cpp
int factorial(int n) {
    if (n <= 1) return 1;         // base case (stop condition)
    return n * factorial(n - 1);  // recursive call
}

cout << factorial(5);  // 120
// Trace: 5 * 4 * 3 * 2 * 1 = 120
```

```
factorial(5)
  └── 5 * factorial(4)
            └── 4 * factorial(3)
                      └── 3 * factorial(2)
                                └── 2 * factorial(1)
                                          └── 1 (base case)
```

---

## Inline Functions

Hint to the compiler to **expand the function in place** (avoids function call overhead for tiny functions):

```cpp
inline int square(int n) {
    return n * n;
}
```

> 💡 The compiler may ignore `inline` and decide on its own. Modern compilers are smart about this. Use it for tiny, frequently called functions.

---

## Function Diagram

```
main()
  │
  ├── calls add(3, 5)  ──────► add function runs
  │                               returns 8
  │   ◄────────────────────── result = 8
  │
  ├── calls greet("Alice")  ──► greet function runs
  │                               prints "Hello, Alice!"
  │   ◄────────────────────── returns nothing (void)
  │
  └── end
```

---

## Key Takeaways

- Functions encapsulate reusable logic — define once, call many times
- Syntax: `return_type name(parameters) { body }`
- `void` return type means the function doesn't return a value
- Pass by value: function gets a copy (original unchanged)
- Pass by reference (`&`): function can modify the original
- Pass by const reference (`const &`): read-only access to original (no copy, no change)
- Default arguments let callers skip optional parameters
- Function overloading: same name, different parameter types — C++ picks the right one
- Recursive functions call themselves — always need a base case to stop
