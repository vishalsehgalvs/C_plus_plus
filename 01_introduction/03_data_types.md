# C++ Data Types

> Source: https://www.programiz.com/cpp-programming/data-types

---

## What Is a Data Type?

A data type tells the compiler **what kind of data** a variable holds and **how much memory** to reserve.

> 🔁 **Analogy:** Think of different-sized containers in a kitchen. A shot glass (char) holds less than a mug (int), which holds less than a bucket (long long). You pick the right container for the right job.

```
Memory layout (typical 64-bit system):
┌──────┐  1 byte   char
├──────┤
├──────┤
├──────┤  4 bytes  int
├──────┤
├──────┤
│      │
│      │
└──────┘  8 bytes  double / long long
```

---

## Fundamental Data Types

### Integer Types

| Type | Size | Range |
|------|------|-------|
| `short` | 2 bytes | −32,768 to 32,767 |
| `int` | 4 bytes | −2.1B to 2.1B |
| `long` | 4 or 8 bytes | platform-dependent |
| `long long` | 8 bytes | ±9.2 × 10¹⁸ |

```cpp
short  s  = 32000;
int    i  = 2000000000;
long   l  = 1234567890L;
long long ll = 9000000000000LL;

// Unsigned versions (no negatives, double the positive range)
unsigned int u  = 4000000000u;
unsigned long long ull = 18000000000000000000ull;
```

### Floating-Point Types

| Type | Size | Precision |
|------|------|-----------|
| `float` | 4 bytes | ~7 decimal digits |
| `double` | 8 bytes | ~15 decimal digits |
| `long double` | 10–16 bytes | ~18–19 digits |

```cpp
float  f  = 3.14f;         // suffix f for float
double d  = 3.14159265358; // default floating point
long double ld = 3.14L;    // suffix L for long double
```

> ⚠️ **Precision matters:** Never use `float` for money or anything requiring precision. Use `double` or a decimal library.

### Character Type

```cpp
char c1 = 'A';         // single character (single quotes)
char c2 = 65;          // also 'A' — char is stored as ASCII number
wchar_t wc = L'€';    // wide character (Unicode)
char16_t c16 = u'€';  // UTF-16
char32_t c32 = U'€';  // UTF-32

cout << c1;   // prints: A
cout << (int)c1; // prints: 65 (ASCII value)
```

### Boolean Type

```cpp
bool isOpen  = true;
bool isClosed = false;

cout << isOpen;   // prints: 1 (true = 1)
cout << boolalpha << isOpen; // prints: true (with boolalpha flag)

// Any non-zero value is true:
bool x = 42;   // true
bool y = 0;    // false
bool z = -5;   // true
```

---

## ASCII Chart (Most Common)

```
32 = space     48–57  = '0'–'9'
65–90  = 'A'–'Z'
97–122 = 'a'–'z'

'A' + 32 = 'a'   (lowercase = uppercase + 32)
```

---

## Type Sizes (Check on Your System)

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "char:       " << sizeof(char)       << " bytes\n";
    cout << "int:        " << sizeof(int)        << " bytes\n";
    cout << "long long:  " << sizeof(long long)  << " bytes\n";
    cout << "float:      " << sizeof(float)      << " bytes\n";
    cout << "double:     " << sizeof(double)     << " bytes\n";
    cout << "bool:       " << sizeof(bool)       << " bytes\n";
    return 0;
}
```

---

## Type Conversion

### Implicit (Automatic)

```cpp
int    i = 10;
double d = i;    // int → double (safe, no data loss)
// d is now 10.0

double x = 9.99;
int    y = x;    // double → int (data loss! .99 chopped off)
// y is 9  ← truncated, not rounded
```

### Explicit (Casting)

```cpp
double x = 9.99;
int y = (int)x;        // C-style cast → 9
int z = static_cast<int>(x);  // C++ style cast (preferred) → 9

// Safe cast example:
double result = (double)7 / 2;  // 3.5 (not 3)
// Without cast: 7 / 2 = 3 (integer division!)
```

### String to Number (and back)

```cpp
#include <string>

string s = "42";
int n = stoi(s);        // string to int
double d = stod(s);     // string to double
string back = to_string(n); // int to string
```

---

## `auto` Keyword (Type Inference)

Let the compiler figure out the type automatically:

```cpp
auto x = 10;       // int
auto y = 3.14;     // double
auto z = 'A';      // char
auto s = "Hello";  // const char*
auto b = true;     // bool

// Useful in complex types:
auto it = myVector.begin();  // instead of: vector<int>::iterator it
```

> 💡 Use `auto` to reduce verbosity, but don't overuse it — be explicit when readability matters.

---

## Data Type Diagram

```
C++ Data Types
├── Fundamental
│   ├── Integer:  short, int, long, long long  (+ unsigned versions)
│   ├── Float:    float, double, long double
│   ├── Char:     char, wchar_t, char16_t, char32_t
│   └── Bool:     bool (true/false)
│
├── Derived
│   ├── Arrays    (int arr[10])
│   ├── Pointers  (int* ptr)
│   ├── References (int& ref)
│   └── Functions
│
└── User-Defined
    ├── struct
    ├── class
    ├── union
    └── enum
```

---

## Key Takeaways

- Choose the right type for the job: `int` for whole numbers, `double` for decimals, `char` for characters, `bool` for true/false
- All values are stored as numbers — `char 'A'` is stored as `65` (ASCII)
- Use `sizeof()` to check how many bytes a type uses on your system
- Implicit conversion: C++ automatically converts compatible types, but may lose precision (double → int)
- Explicit cast: `static_cast<int>(x)` is the modern C++ way to cast
- `auto` lets the compiler infer the type — handy but use with care
- Never use `float` for financial calculations — use `double` or a decimal library
