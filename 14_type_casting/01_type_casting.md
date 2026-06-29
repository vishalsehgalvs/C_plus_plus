# Type Casting in C++

> Source reference: https://www.tutorialspoint.com/cplusplus/cpp_casting_operators.htm

---

## What Is Type Casting?

Type casting is **converting a value from one data type to another**. C++ gives you multiple ways to do this — from the simple (C-style cast) to the precise and safe (modern C++ casts).

> 🔁 **Analogy:** Think of data types as containers. A type cast is like pouring water from one container into another — you might lose some (truncation), it might overflow, or it might fit perfectly. Knowing _which cast to use_ tells you what risks you're taking.

```
Data Type Hierarchy (widening = safe, narrowing = risky):

double ←──── float ←──── long ←──── int ←──── short ←──── char
  ↑ wider                                                  narrower ↑
  └── widening cast (safe, implicit)   narrowing cast (explicit needed) ──┘
```

---

## Implicit Conversion (Automatic)

C++ automatically converts types when it's safe (no data loss):

```cpp
int i = 42;
double d = i;        // int → double: safe, d = 42.0

float f = 3.14f;
double d2 = f;       // float → double: safe

char c = 'A';
int ascii = c;       // char → int: safe, ascii = 65
```

---

## C-Style Cast — `(type)value`

The old way, inherited from C:

```cpp
double pi = 3.14159;
int truncated = (int)pi;      // 3 — decimal part lost!

int a = 10, b = 3;
double result = (double)a / b;   // 3.333... (without cast: 3)

// Feels natural but DANGEROUS — no checks at all
```

> ⚠️ **Avoid C-style casts in C++!** They're too powerful — they can do anything without warning. Use the named casts below instead.

---

## The Four Named Casts (Modern C++)

```
┌─────────────────────────────────────────────────────────────┐
│              C++ NAMED CASTS                                │
├──────────────────┬──────────────────────────────────────────┤
│ static_cast      │ Most common. Safe conversions.           │
│ dynamic_cast     │ Runtime check for polymorphism.          │
│ const_cast       │ Add/remove const qualifier.              │
│ reinterpret_cast │ Raw bit-level reinterpretation.          │
└──────────────────┴──────────────────────────────────────────┘
```

---

## 1. `static_cast` — General Purpose, Compile-Time

Use for: numeric conversions, explicit narrowing, pointer conversions in class hierarchies (when you're SURE it's safe).

```cpp
// Numeric conversions
double pi = 3.14159;
int i = static_cast<int>(pi);        // 3 (truncated, but explicit)

int a = 7, b = 2;
double d = static_cast<double>(a) / b;  // 3.5 (correct division)

// enum to int
enum Color { RED, GREEN, BLUE };
int colorNum = static_cast<int>(GREEN);  // 1

// void* to specific pointer (common in C callbacks)
void* ptr = &i;
int* intPtr = static_cast<int*>(ptr);
```

```
static_cast<TargetType>(value)
         │
         ▼
   Compile-time check:
   Is this conversion known and valid?
   YES → compile it
   NO  → compile error ❌
   (No runtime checks)
```

---

## 2. `dynamic_cast` — Safe Downcasting (Runtime Check)

Use for: casting down a class hierarchy (base → derived) when you're not sure of the actual type at runtime. Requires **virtual functions** in the base class.

```cpp
class Animal {
public:
    virtual ~Animal() {}   // virtual needed for dynamic_cast!
    virtual void speak() = 0;
};

class Dog : public Animal {
public:
    void speak() override { cout << "Woof!" << endl; }
    void fetch() { cout << "Fetching..." << endl; }
};

class Cat : public Animal {
public:
    void speak() override { cout << "Meow!" << endl; }
};

int main() {
    Animal* a = new Dog();    // base pointer to derived object

    // Try to cast to Dog
    Dog* d = dynamic_cast<Dog*>(a);
    if (d != nullptr) {
        d->fetch();           // safe! it IS a Dog
    }

    // Try to cast to Cat
    Cat* c = dynamic_cast<Cat*>(a);
    if (c == nullptr) {
        cout << "Not a Cat!" << endl;    // this runs
    }

    delete a;
    return 0;
}
```

```
dynamic_cast<Derived*>(basePtr)
         │
         ▼
   Runtime RTTI check:
   Does the actual object match Derived?
   YES → return valid pointer
   NO  → return nullptr (for pointers)
         throw std::bad_cast (for references)
```

> 💡 `dynamic_cast` is the only cast that checks at **runtime**. It's slower but safe. Only use when you need the safety check.

---

## 3. `const_cast` — Add or Remove `const`

Use for: passing a `const` variable to a function that doesn't accept `const` (but you know it won't modify the data).

```cpp
void printMessage(char* msg) {    // old C API — doesn't take const char*
    cout << msg << endl;
}

int main() {
    const char* greeting = "Hello!";
    printMessage(const_cast<char*>(greeting));  // remove const to call old API
}
```

> ⚠️ **Never use `const_cast` to modify actually-const data** — that's undefined behavior!

```cpp
const int x = 10;
int* ptr = const_cast<int*>(&x);
*ptr = 20;    // UNDEFINED BEHAVIOR! x was truly const
```

---

## 4. `reinterpret_cast` — Raw Bit Reinterpretation

Use for: treating the raw bytes of one type as another type. Almost always low-level / system programming.

```cpp
int i = 65;
char* c = reinterpret_cast<char*>(&i);
cout << *c;    // 'A' on little-endian (65 = ASCII 'A')

// Often used for: memory-mapped I/O, serialization, type-punning
long addr = 0x00FF1234;
int* ptr = reinterpret_cast<int*>(addr);   // treat address as pointer
```

> ⚠️ **`reinterpret_cast` is dangerous.** It bypasses the type system entirely. Only use when you KNOW exactly what the memory layout is (e.g., device drivers, network protocols).

---

## Casting Cheatsheet

```
Which cast should I use?
          │
          ▼
  Is it a basic numeric / enum conversion?
          │
    YES ──┘── NO
     │             │
     ▼             ▼
 static_cast    Are you working with class hierarchies?
                    │
              YES ──┘── NO
               │             │
               ▼             ▼
         Do you need       Are you adding/removing const?
         runtime safety?         │
               │           YES ──┘── NO
         YES ──┘── NO       │            │
          │          │      ▼            ▼
          ▼          ▼  const_cast   reinterpret_cast
     dynamic_cast  static_cast      (raw bits — dangerous)
```

---

## Comparing All Four Casts

| Cast               | When to Use                       | Runtime Check | Safety       |
| ------------------ | --------------------------------- | ------------- | ------------ |
| `static_cast`      | General conversions, known safe   | No            | ✅ Good      |
| `dynamic_cast`     | Base → derived, polymorphic types | Yes           | ✅ Safest    |
| `const_cast`       | Remove/add const for old APIs     | No            | ⚠️ Careful   |
| `reinterpret_cast` | Raw memory / bit tricks           | No            | ❌ Dangerous |
| C-style `(T)`      | (Avoid in C++)                    | No            | ❌ Dangerous |

---

## Integer Promotion Example

```cpp
#include <iostream>
using namespace std;

int main() {
    // Narrowing — data can be lost
    double d = 9.99;
    int i = static_cast<int>(d);    // i = 9 (truncated, NOT rounded)
    cout << i << endl;              // 9

    // Widening — always safe
    int small = 42;
    long big = static_cast<long>(small);   // 42L

    // Division trap
    int x = 7, y = 2;
    cout << x / y << endl;                         // 3 (integer division!)
    cout << static_cast<double>(x) / y << endl;    // 3.5 (correct)

    return 0;
}
```

---

> 💡 **Summary rule:** Use `static_cast` for most things. Use `dynamic_cast` when you need safety in polymorphism. Avoid the other two unless you have a very specific reason.
