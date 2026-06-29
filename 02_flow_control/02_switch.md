# C++ Switch Statement

> Source: https://www.programiz.com/cpp-programming/switch-case

---

## What Is a Switch Statement?

A `switch` statement is a clean alternative to a long chain of `if-else if` when you're comparing **one variable against many exact values**.

> 🔁 **Analogy:** A switch is like a TV remote. You press a specific button (case) and the TV jumps to that channel. Pressing an unknown button does nothing (or a default action).

```
                 ┌─────────────┐
                 │  switch(x)  │
                 └──────┬──────┘
                        │
         ┌──────────────┼──────────────┐
         ▼              ▼              ▼
    case 1:         case 2:        default:
    Block A         Block B        Block C
```

---

## Basic Syntax

```cpp
switch (expression) {
    case value1:
        // code to run if expression == value1
        break;
    case value2:
        // code to run if expression == value2
        break;
    case value3:
        // code to run if expression == value3
        break;
    default:
        // code to run if no case matched
        break;
}
```

---

## Real Example: Day of Week

```cpp
#include <iostream>
using namespace std;

int main() {
    int day = 3;

    switch (day) {
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5:
            cout << "Friday" << endl;
            break;
        case 6:
            cout << "Saturday" << endl;
            break;
        case 7:
            cout << "Sunday" << endl;
            break;
        default:
            cout << "Invalid day number" << endl;
            break;
    }

    return 0;
}
// Output: Wednesday
```

---

## The `break` Statement — Critical!

Without `break`, execution **falls through** to the next case:

```cpp
int x = 2;
switch (x) {
    case 1:
        cout << "one\n";
        break;
    case 2:
        cout << "two\n";
        // ← NO BREAK! falls through to case 3
    case 3:
        cout << "three\n";
        break;
    case 4:
        cout << "four\n";
        break;
}
// Output: two
//         three    ← OOPS! this runs too (fall-through)
```

> ⚠️ **Always add `break`** unless you intentionally want fall-through. Missing `break` is one of the most common C++ bugs.

---

## Intentional Fall-Through (Grouping Cases)

Sometimes you WANT multiple cases to do the same thing:

```cpp
int month = 4;

switch (month) {
    case 1: case 3: case 5: case 7:
    case 8: case 10: case 12:
        cout << "31 days" << endl;
        break;
    case 4: case 6: case 9: case 11:
        cout << "30 days" << endl;
        break;
    case 2:
        cout << "28 or 29 days" << endl;
        break;
    default:
        cout << "Invalid month" << endl;
}
// Output: 30 days
```

---

## Switch with Characters

```cpp
char grade = 'B';

switch (grade) {
    case 'A':
        cout << "Excellent!" << endl;
        break;
    case 'B':
        cout << "Good job!" << endl;
        break;
    case 'C':
        cout << "Average." << endl;
        break;
    case 'D':
        cout << "Below average." << endl;
        break;
    case 'F':
        cout << "Failed." << endl;
        break;
    default:
        cout << "Invalid grade." << endl;
}
// Output: Good job!
```

---

## Switch vs if-else: When to Use Which

```cpp
// ✅ Use switch when:
// - Comparing ONE variable against EXACT values
// - You have 3+ cases
// - The values are integers, chars, or enums

switch (menuChoice) {
    case 1: doOption1(); break;
    case 2: doOption2(); break;
    case 3: doOption3(); break;
}

// ✅ Use if-else when:
// - Checking ranges or complex conditions
// - Comparing different variables
// - Using strings (switch doesn't work with std::string)

if (age < 13) cout << "child";
else if (age < 18) cout << "teen";
else cout << "adult";
```

|                          | `switch`                         | `if-else if`  |
| ------------------------ | -------------------------------- | ------------- |
| Readability (many cases) | ✅ Cleaner                       | ❌ Long chain |
| Ranges                   | ❌ Not possible                  | ✅ Works      |
| Strings                  | ❌ Doesn't work (without tricks) | ✅ Works      |
| Enum values              | ✅ Perfect                       | ✅ Works      |
| Performance              | ✅ Often faster (jump table)     | Depends       |

---

## Simple Calculator Example

```cpp
#include <iostream>
using namespace std;

int main() {
    double a, b;
    char op;

    cout << "Enter expression (e.g. 5 + 3): ";
    cin >> a >> op >> b;

    switch (op) {
        case '+':
            cout << a << " + " << b << " = " << (a + b) << endl;
            break;
        case '-':
            cout << a << " - " << b << " = " << (a - b) << endl;
            break;
        case '*':
            cout << a << " * " << b << " = " << (a * b) << endl;
            break;
        case '/':
            if (b != 0)
                cout << a << " / " << b << " = " << (a / b) << endl;
            else
                cout << "Error: divide by zero!" << endl;
            break;
        default:
            cout << "Unknown operator: " << op << endl;
    }

    return 0;
}
```

---

## `[[fallthrough]]` Attribute (C++17)

When you intentionally want fall-through, mark it explicitly so the compiler and readers know it's on purpose:

```cpp
int day = 3;
switch (day) {
    case 1:
        cout << "Monday";
        break;
    case 2:
        cout << "Tuesday";
        break;
    case 3:
        cout << "Mid-week — Wednesday";
        [[fallthrough]];     // ✅ explicit: YES, I meant to fall through
    case 4:
        cout << " or Thursday — hang in there!" << endl;
        break;
    case 5:
        cout << "Friday!" << endl;
        break;
    default:
        cout << "Weekend!" << endl;
}
```

> Without `[[fallthrough]]`, many compilers will warn about the accidental fall-through. This attribute silences the warning AND documents intent to future readers.

---

## Switch with `enum class` (Best Practice)

```cpp
enum class Direction { NORTH, SOUTH, EAST, WEST };

Direction dir = Direction::NORTH;

switch (dir) {
    case Direction::NORTH: cout << "Going North"; break;
    case Direction::SOUTH: cout << "Going South"; break;
    case Direction::EAST:  cout << "Going East";  break;
    case Direction::WEST:  cout << "Going West";  break;
    // no default needed — compiler warns if you forget a case!
}
```

> 💡 Pairing `switch` with `enum class` is a powerful pattern. The compiler warns you if you add a new enum value and forget to handle it in the switch — prevents bugs.

---

## Key Takeaways

- `switch` compares one expression against multiple exact values — cleaner than long `if-else if` chains
- **Always add `break`** at the end of each case — missing `break` causes fall-through to next case
- `default` handles any value that doesn't match any case (like a final `else`)
- Fall-through is intentional when you group multiple cases to do the same thing: `case 1: case 2: case 3:`
- Switch works with `int`, `char`, and `enum` — NOT with `float`, `double`, or `string`
- Use `if-else` when checking ranges, complex conditions, or strings
- **`[[fallthrough]]`** (C++17) — marks intentional fall-through explicitly; silences compiler warnings
- **Pair with `enum class`** — compiler warns if you add a new enum value and forget a case
