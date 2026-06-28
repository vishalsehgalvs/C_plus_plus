# C++ Operators

> Source: https://www.programiz.com/cpp-programming/operators

---

## What Are Operators?

Operators are symbols that perform operations on **operands** (variables or values).

> 🔁 **Analogy:** Operators are like verbs in a sentence. `a + b` means "add a and b." The operator (`+`) tells C++ *what to do* with the operands (`a` and `b`).

---

## 1. Arithmetic Operators

| Operator | Name | Example | Result |
|----------|------|---------|--------|
| `+` | Addition | `5 + 3` | `8` |
| `-` | Subtraction | `5 - 3` | `2` |
| `*` | Multiplication | `5 * 3` | `15` |
| `/` | Division | `5 / 2` | `2` (int!) |
| `%` | Modulo (remainder) | `5 % 2` | `1` |

```cpp
int a = 10, b = 3;

cout << a + b << endl;  // 13
cout << a - b << endl;  // 7
cout << a * b << endl;  // 30
cout << a / b << endl;  // 3   ← integer division (truncates)
cout << a % b << endl;  // 1   ← 10 = 3×3 + 1, remainder is 1

// Integer division pitfall:
cout << 7 / 2 << endl;   // 3 (NOT 3.5!)
cout << 7.0 / 2 << endl; // 3.5 (one float operand → float division)
```

> ⚠️ **Integer division truncates** — `7/2` is `3`, not `3.5`. If you want decimals, cast first: `(double)7 / 2`

### Modulo uses:

```cpp
// Check even/odd
if (n % 2 == 0) cout << "even";
else cout << "odd";

// Wrap around (circular index)
int index = (current + 1) % arraySize;

// Get last digit
int lastDigit = number % 10;
```

---

## 2. Assignment Operators

```cpp
int x = 10;

x += 5;   // x = x + 5  → 15
x -= 3;   // x = x - 3  → 12
x *= 2;   // x = x * 2  → 24
x /= 4;   // x = x / 4  → 6
x %= 4;   // x = x % 4  → 2

// Also works with strings:
string s = "Hello";
s += " World";  // s = "Hello World"
```

---

## 3. Increment & Decrement Operators

```cpp
int a = 5;

// Prefix (change THEN use)
++a;  // a = 6
--a;  // a = 5

// Postfix (use THEN change)
a++;  // use 5, then a = 6
a--;  // use 6, then a = 5
```

### Prefix vs Postfix:

```cpp
int a = 5;
int b = ++a;  // a becomes 6, then b = 6  (prefix: increment first)
int c = a++;  // c = 6, then a becomes 7  (postfix: use first, then increment)

cout << a << " " << b << " " << c;  // 7 6 6
```

> 💡 In most cases (standalone `i++` or `++i`) it doesn't matter. Use `++i` in loops — slightly more efficient (especially with iterators).

---

## 4. Relational (Comparison) Operators

These return `true` (1) or `false` (0):

| Operator | Meaning | Example |
|----------|---------|---------|
| `==` | Equal to | `5 == 5` → `true` |
| `!=` | Not equal | `5 != 3` → `true` |
| `>` | Greater than | `5 > 3` → `true` |
| `<` | Less than | `5 < 3` → `false` |
| `>=` | Greater or equal | `5 >= 5` → `true` |
| `<=` | Less or equal | `3 <= 5` → `true` |

```cpp
int age = 18;
cout << (age >= 18) << endl;  // 1 (true)
cout << (age == 21) << endl;  // 0 (false)

// ⚠️ Common mistake: = vs ==
if (age = 18) { ... }   // ❌ ASSIGNS 18 (not comparison!)
if (age == 18) { ... }  // ✅ COMPARES correctly
```

---

## 5. Logical Operators

Combine multiple conditions:

| Operator | Name | Example | Meaning |
|----------|------|---------|---------|
| `&&` | AND | `a > 0 && b > 0` | Both must be true |
| `\|\|` | OR | `a > 0 \|\| b > 0` | At least one true |
| `!` | NOT | `!isLoggedIn` | Flip true/false |

```cpp
int age = 20;
bool hasTicket = true;

// AND: both conditions must be true
if (age >= 18 && hasTicket) {
    cout << "You can enter!" << endl;
}

// OR: at least one condition true
if (age < 5 || age > 65) {
    cout << "Free admission" << endl;
}

// NOT: reverse the condition
if (!hasTicket) {
    cout << "Buy a ticket first!" << endl;
}
```

### Short-circuit evaluation:

```cpp
// && stops at first false
if (ptr != nullptr && ptr->value > 0) {
    // If ptr is null, the second part is NEVER checked (safe!)
}

// || stops at first true
if (isAdmin() || hasPermission()) {
    // If isAdmin() is true, hasPermission() is never called
}
```

---

## 6. Bitwise Operators

Operate on individual bits of integers:

| Operator | Name | Example |
|----------|------|---------|
| `&` | AND | `5 & 3` = `1` |
| `\|` | OR | `5 \| 3` = `7` |
| `^` | XOR | `5 ^ 3` = `6` |
| `~` | NOT (complement) | `~5` = `-6` |
| `<<` | Left shift | `5 << 1` = `10` |
| `>>` | Right shift | `5 >> 1` = `2` |

```cpp
// 5 = 0101, 3 = 0011
cout << (5 & 3);   // 0001 = 1
cout << (5 | 3);   // 0111 = 7
cout << (5 ^ 3);   // 0110 = 6
cout << (5 << 1);  // 1010 = 10 (multiply by 2)
cout << (5 >> 1);  // 0010 = 2  (divide by 2)
```

---

## 7. Ternary (Conditional) Operator

A compact if-else in one line:

```cpp
// Syntax: condition ? value_if_true : value_if_false

int age = 20;
string status = (age >= 18) ? "adult" : "minor";
cout << status;  // adult

// Another example
int a = 5, b = 10;
int max = (a > b) ? a : b;
cout << max;  // 10
```

---

## Operator Precedence (Simplified)

Higher means evaluated first:

```
1. ()              Parentheses (highest)
2. ++  --          Prefix increment/decrement
3. !  ~            Logical/bitwise NOT
4. *  /  %         Multiplication, division, modulo
5. +  -            Addition, subtraction
6. <<  >>          Bit shifts
7. <  <=  >  >=    Comparison
8. ==  !=           Equality
9. &               Bitwise AND
10. ^              Bitwise XOR
11. |              Bitwise OR
12. &&             Logical AND
13. ||             Logical OR
14. ?:             Ternary
15. =  +=  -=  ... Assignment (lowest)
```

> 💡 **When in doubt, use parentheses!** `(a + b) * c` is clearer than `a + b * c`.

---

## Key Takeaways

- `+`, `-`, `*`, `/`, `%` are arithmetic; integer division **truncates** (use cast for decimals)
- `%` (modulo) gives the **remainder** — use for even/odd checks, circular indexing
- `==` compares, `=` assigns — mixing them is a classic bug
- `&&`, `||`, `!` are logical operators — use short-circuit evaluation to prevent null crashes
- `++i` (prefix) increments first, `i++` (postfix) uses value first then increments
- Ternary `? :` is a compact if-else: `condition ? true_val : false_val`
- Use parentheses to make operator precedence explicit and code readable
