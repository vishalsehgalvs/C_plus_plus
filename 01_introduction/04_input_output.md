# C++ Input and Output (I/O)

> Source: https://www.programiz.com/cpp-programming/input-output

---

## The `<iostream>` Library

C++ handles input and output through **streams** — think of them as pipes through which data flows.

> 🔁 **Analogy:** `cout` is like a loudspeaker (you broadcast to the screen), and `cin` is like a microphone (you receive from the keyboard).

```
Keyboard ──► [ cin  ] ──► Your program ──► [ cout ] ──► Screen
                                        ──► [ cerr ] ──► Screen (errors)
                                        ──► [ clog ] ──► Screen (log)
```

```cpp
#include <iostream>  // required for cin, cout, cerr, endl
using namespace std;
```

---

## Output with `cout`

```cpp
#include <iostream>
using namespace std;

int main() {
    // Basic output
    cout << "Hello, World!";

    // With newline (two ways)
    cout << "Hello\n";       // \n = newline escape
    cout << "World" << endl; // endl = newline + flush buffer

    // Multiple values chained
    int age = 25;
    string name = "Alice";
    cout << "Name: " << name << ", Age: " << age << endl;

    // Arithmetic in output
    cout << "2 + 3 = " << (2 + 3) << endl;

    return 0;
}
```

**Output:**
```
Hello
World
Name: Alice, Age: 25
2 + 3 = 5
```

### `\n` vs `endl`

| | `\n` | `endl` |
|--|------|--------|
| What it does | Just newline | Newline + flushes buffer |
| Speed | ⚡ Faster | 🐢 Slightly slower |
| When to use | Normal output | When you need immediate flush |

> 💡 **Prefer `'\n'`** over `endl` in most cases — `endl` flushes the buffer each time which is slow in loops.

---

## Input with `cin`

```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    cout << "Enter your age: ";
    cin >> age;   // read integer from keyboard
    cout << "You are " << age << " years old." << endl;

    return 0;
}
```

**Session:**
```
Enter your age: 25
You are 25 years old.
```

### Reading multiple values

```cpp
int a, b;
cout << "Enter two numbers: ";
cin >> a >> b;   // reads both, separated by space/enter
cout << a + b;
```

### Reading a full line (with spaces)

```cpp
string name;
cout << "Enter full name: ";
getline(cin, name);   // reads entire line including spaces
cout << "Hello, " << name;
```

> ⚠️ **Common bug:** If you use `cin >>` before `getline`, a leftover newline character can cause `getline` to read an empty string. Fix:

```cpp
int age;
cin >> age;
cin.ignore();          // ← consume the leftover newline
string name;
getline(cin, name);    // now works correctly
```

---

## Output Formatting

```cpp
#include <iostream>
#include <iomanip>   // for setw, setprecision, fixed
using namespace std;

int main() {
    double pi = 3.14159265;

    // Set decimal precision
    cout << fixed << setprecision(2) << pi << endl; // 3.14
    cout << fixed << setprecision(4) << pi << endl; // 3.1416

    // Field width (padding)
    cout << setw(10) << "Hello" << endl;   //      Hello (right-aligned)
    cout << left << setw(10) << "Hello" << endl; // Hello      (left-aligned)

    // Fill character
    cout << setfill('*') << setw(10) << "Hi" << endl; // ********Hi

    return 0;
}
```

**Output:**
```
3.14
3.1416
     Hello
Hello     
********Hi
```

---

## Error Output with `cerr`

```cpp
int x = -1;
if (x < 0) {
    cerr << "Error: negative value!" << endl;  // goes to stderr
}
```

Use `cerr` for error messages — it's separate from `cout` so errors and normal output can be redirected independently on the command line.

---

## Complete I/O Example

```cpp
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string name;
    int age;
    double gpa;

    cout << "=== Student Registration ===" << endl;
    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter age: ";
    cin >> age;

    cout << "Enter GPA: ";
    cin >> gpa;

    cout << "\n--- Summary ---" << endl;
    cout << left << setw(10) << "Name:"  << name << endl;
    cout << left << setw(10) << "Age:"   << age  << endl;
    cout << left << setw(10) << "GPA:"   << fixed << setprecision(2) << gpa << endl;

    return 0;
}
```

---

## Key Takeaways

- `#include <iostream>` is required for input/output
- `cout <<` prints to the screen; chain values with `<<`
- `cin >>` reads from keyboard; reads one word at a time (stops at space)
- `getline(cin, str)` reads a whole line including spaces
- Use `cin.ignore()` to clear leftover newline before using `getline` after `cin >>`
- `'\n'` is faster than `endl` (no buffer flush); use `endl` when you need immediate output
- `cerr` is for error messages — separate stream from `cout`
- `#include <iomanip>` enables formatting: `setw()`, `setprecision()`, `fixed`, `left`, `right`
