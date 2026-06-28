# C++ if, if...else, and Nested Conditions

> Source: https://www.programiz.com/cpp-programming/if-else

---

## What Is Flow Control?

By default, C++ runs code line-by-line, top to bottom. **Flow control** lets you skip, repeat, or jump to different parts of the program based on conditions.

> 🔁 **Analogy:** Like a GPS navigation. "IF traffic on Route A is bad, ELSE take Route B." The decision changes the path you take.

---

## The `if` Statement

Run code **only if** a condition is true:

```
Condition
    │
    ▼
 ┌──────┐
 │ true │──► Execute block
 └──────┘
 │ false│──► Skip block
 └──────┘
```

```cpp
int age = 20;

if (age >= 18) {
    cout << "You are an adult." << endl;
}
// If age < 18, this block is completely skipped
```

---

## The `if...else` Statement

Choose between two paths:

```
Condition
    │
    ├─ true  ──► Block A
    │
    └─ false ──► Block B
```

```cpp
int age = 15;

if (age >= 18) {
    cout << "Adult — can vote." << endl;
} else {
    cout << "Minor — cannot vote yet." << endl;
}
// Output: Minor — cannot vote yet.
```

---

## `if...else if...else` (Multiple Conditions)

Check several conditions in sequence:

```
        ┌─────────────┐
        │ condition 1 │── true ──► Block 1 ──► done
        └─────────────┘
               │ false
               ▼
        ┌─────────────┐
        │ condition 2 │── true ──► Block 2 ──► done
        └─────────────┘
               │ false
               ▼
        ┌─────────────┐
        │   else      │──────────► Block 3 ──► done
        └─────────────┘
```

```cpp
int score = 75;

if (score >= 90) {
    cout << "Grade: A" << endl;
} else if (score >= 80) {
    cout << "Grade: B" << endl;
} else if (score >= 70) {
    cout << "Grade: C" << endl;
} else if (score >= 60) {
    cout << "Grade: D" << endl;
} else {
    cout << "Grade: F" << endl;
}
// Output: Grade: C
```

> 💡 Once a true condition is found, the rest are **skipped** — C++ doesn't check the remaining conditions.

---

## Nested `if` Statements

An `if` inside another `if`:

```cpp
int age = 20;
bool hasLicense = true;

if (age >= 16) {
    if (hasLicense) {
        cout << "You can drive!" << endl;
    } else {
        cout << "Get a license first." << endl;
    }
} else {
    cout << "Too young to drive." << endl;
}
```

> ⚠️ Deep nesting is a code smell. If you're nesting more than 2-3 levels, consider restructuring.

---

## Ternary Operator (Compact if-else)

One-line if-else for simple assignments:

```cpp
// Syntax:
// condition ? value_if_true : value_if_false

int age = 20;
string status = (age >= 18) ? "adult" : "minor";
cout << status;  // adult

// Avoid overusing for readability — if complex, use if-else
string result = (a > b) ? ((a > c) ? "a" : "c") : ((b > c) ? "b" : "c");
// ↑ This is hard to read — just use if-else
```

---

## Common Conditions

```cpp
// Checking ranges
if (temp > 0 && temp < 100) { ... }         // between 0 and 100
if (temp <= 0 || temp >= 100) { ... }        // outside range

// Checking strings
string s = "hello";
if (s == "hello") { ... }                   // string comparison with ==
if (s.empty()) { ... }                       // empty string check
if (s.length() > 5) { ... }

// Checking for null
int* ptr = nullptr;
if (ptr != nullptr) { ptr->doSomething(); } // safe null check
if (ptr) { ... }                             // shorter form (same thing)

// Boolean flags
bool isReady = true;
if (isReady) { ... }         // same as: if (isReady == true)
if (!isReady) { ... }        // same as: if (isReady == false)
```

---

## Classic Mistakes

```cpp
// ❌ Assignment instead of comparison
int x = 5;
if (x = 10) {   // ASSIGNS 10 to x, always true (non-zero)!
    cout << "x is 10";
}

// ✅ Correct comparison
if (x == 10) {
    cout << "x is 10";
}

// ✅ "Yoda condition" to prevent this mistake (optional style):
if (10 == x) {  // if you accidentally type = instead of ==, compiler errors
    cout << "x is 10";
}

// ❌ Dangling else (ambiguous indentation)
if (a > 0)
    if (b > 0)
        cout << "both positive";
else               // ← this else belongs to INNER if, not outer!
    cout << "a not positive";

// ✅ Always use braces to be explicit:
if (a > 0) {
    if (b > 0) {
        cout << "both positive";
    }
} else {
    cout << "a not positive";
}
```

---

## Real-World Example: Login System

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    const string CORRECT_USER = "admin";
    const string CORRECT_PASS = "password123";

    string username, password;
    int attempts = 0;

    cout << "=== Login ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == CORRECT_USER && password == CORRECT_PASS) {
        cout << "✅ Login successful! Welcome, " << username << endl;
    } else if (username == CORRECT_USER) {
        cout << "❌ Wrong password." << endl;
    } else {
        cout << "❌ User not found." << endl;
    }

    return 0;
}
```

---

## Key Takeaways

- `if (condition)` runs a block only when condition is true
- `if-else` chooses between two paths; `if-else if-else` handles multiple cases
- Once a true condition is found, remaining conditions are skipped
- Nested `if` is fine but don't go deeper than 2-3 levels — refactor instead
- Ternary `?:` is compact but use it only for simple one-liner assignments
- **Always use `{}` braces** even for single-line if blocks — prevents the "dangling else" bug
- `=` assigns, `==` compares — never mix them up in conditions
