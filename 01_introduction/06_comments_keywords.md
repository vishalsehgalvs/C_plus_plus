# C++ Comments & Keywords

> Source: https://www.programiz.com/cpp-programming/comments

---

## Comments

Comments are notes in your code that the **compiler completely ignores**. They exist only for humans — you or other developers reading your code.

> 🔁 **Analogy:** Comments are like sticky notes on a textbook. The book (program) works exactly the same with or without them, but they help you understand what's going on.

### Single-Line Comments (`//`)

```cpp
// This is a single-line comment
int age = 25;  // this is also a comment (end of line)

// Explain complex logic:
int result = n * (n + 1) / 2;  // formula for sum of 1..n
```

### Multi-Line Comments (`/* */`)

```cpp
/* This is a
   multi-line comment.
   It can span as many lines as you want. */

/*
 * Conventionally, developers add * at the start of each line
 * to make multi-line comments more readable.
 * This function calculates the area of a circle.
 */
double circleArea(double radius) {
    return 3.14159 * radius * radius;
}
```

---

## When to Comment (and When NOT To)

### ✅ Good comments:

```cpp
// Convert Celsius to Fahrenheit: F = C * 9/5 + 32
double toFahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

// Check if year is a leap year
// Leap year: divisible by 4, but not by 100, unless also by 400
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
```

### ❌ Useless comments (state the obvious):

```cpp
// Add 1 to i
i = i + 1;  // this comment is noise — the code already says this

// Set x to 5
int x = 5;  // again, obvious
```

> 💡 **Rule of thumb:** Comment _why_ you're doing something, not _what_. The code itself shows _what_. The comment should explain the reasoning.

### Use comments to disable code during debugging:

```cpp
// int x = 5;   // temporarily disabled
int x = 10;

/*
cout << debugValue;    // turned off for production
debugStep = 3;
*/
```

---

## C++ Keywords (Reserved Words)

Keywords are **words reserved by C++** for specific purposes. You cannot use them as variable names, function names, or identifiers.

### Complete keyword list:

```
alignas      alignof     and         and_eq      asm
auto         bitand      bitor       bool        break
case         catch       char        char8_t     char16_t
char32_t     class       compl       concept     const
consteval    constexpr   constinit   const_cast  continue
co_await     co_return   co_yield    decltype    default
delete       do          double      dynamic_cast else
enum         explicit    export      extern      false
float        for         friend      goto        if
inline       int         long        mutable     namespace
new          noexcept    not         not_eq      nullptr
operator     or          or_eq       private     protected
public       register    reinterpret_cast        requires
return       short       signed      sizeof      static
static_assert static_cast struct     switch      template
this         thread_local throw      true        try
typedef      typeid      typename    union       unsigned
using        virtual     void        volatile    wchar_t
while        xor         xor_eq
```

---

## Common Keywords You'll Use Often

```cpp
// Type keywords
int, double, float, char, bool, void, auto

// Control flow
if, else, switch, case, break, continue, return

// Loops
for, while, do

// OOP
class, struct, public, private, protected, virtual, this

// Memory
new, delete, nullptr

// Modern C++
auto, const, constexpr, nullptr, override, final
```

---

## Identifiers (Your Own Names)

An identifier is any name you create — for variables, functions, classes, etc.

### Rules for valid identifiers:

```cpp
// ✅ Valid
int age;
int myAge;
int _secret;
int age2;
int TOTAL_ITEMS;

// ❌ Invalid
int 2fast;         // starts with digit
int my-var;        // hyphen not allowed
int for;           // reserved keyword
int hello world;   // space not allowed
```

### C++ is case-sensitive:

```cpp
int age = 25;
int AGE = 30;    // completely different variable!
int Age = 28;    // yet another different variable!
```

---

## Key Takeaways

- `//` is single-line comment; `/* */` is multi-line comment
- Comments are ignored by the compiler — they're for humans only
- Comment _why_ you're doing something, not _what_ (the code shows _what_)
- Keywords are reserved — you can't use them as variable or function names
- Common keywords: `int`, `if`, `for`, `while`, `return`, `class`, `new`, `delete`
- Identifiers (your names) can't start with a digit, can't contain spaces or hyphens, and can't be keywords
- C++ is **case-sensitive**: `age`, `Age`, and `AGE` are three different things
