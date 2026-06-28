# C++ Loops: for, while, do...while

> Source: https://www.programiz.com/cpp-programming/for-loop

---

## Why Loops?

Loops let you run the same code multiple times without copy-pasting.

> 🔁 **Analogy:** Imagine writing "I will not be late" 100 times as punishment. A loop is like a stamp that does it automatically, once per repetition.

C++ has 3 types of loops:
```
for loop       → when you know how many times to repeat
while loop     → when you repeat until a condition changes
do...while     → like while, but always runs at least once
```

---

## 1. The `for` Loop

Best when you know **exactly how many times** to repeat.

```
for (init; condition; update)
      │         │         │
      │         │         └─ runs after each iteration (i++)
      │         └─ checked before each iteration
      └─ runs once at start (int i = 0)
```

```
start
  │
  ▼
init (i = 0)
  │
  ▼
condition ──── false ──► done
  │ true
  ▼
execute body
  │
  ▼
update (i++)
  │
  └──────────────────► back to condition
```

```cpp
// Print numbers 1 to 5
for (int i = 1; i <= 5; i++) {
    cout << i << " ";
}
// Output: 1 2 3 4 5
```

### Anatomy:

```cpp
for (int i = 0;   i < 5;   i++) {
//   ─────────   ──────   ────
//   init        cond.    update
//   runs once   checked  runs each
//   at start    before   iteration
//                each
```

### Common patterns:

```cpp
// Count up
for (int i = 0; i < 10; i++) { }     // 0,1,2,...,9

// Count down
for (int i = 10; i > 0; i--) { }     // 10,9,...,1

// Count by 2
for (int i = 0; i <= 20; i += 2) { } // 0,2,4,...,20

// Loop over array
int arr[] = {10, 20, 30, 40};
for (int i = 0; i < 4; i++) {
    cout << arr[i] << " ";
}
// Output: 10 20 30 40
```

---

## 2. The `while` Loop

Best when you repeat **until something changes**, and you don't know upfront how many iterations.

```
while (condition) {
    // body
}

Flow:
  ▼
condition ──── false ──► done
  │ true
  ▼
execute body
  │
  └──► back to condition
```

```cpp
// Print while count is less than 5
int count = 1;
while (count <= 5) {
    cout << count << " ";
    count++;   // ← update! don't forget or infinite loop
}
// Output: 1 2 3 4 5
```

### User input validation with while:

```cpp
int number;
cout << "Enter a number between 1 and 10: ";
cin >> number;

while (number < 1 || number > 10) {
    cout << "Invalid! Try again: ";
    cin >> number;
}
cout << "Valid number: " << number;
```

---

## 3. The `do...while` Loop

Same as `while`, but the body **always runs at least once** before checking the condition.

```
do {
    body runs FIRST
} while (condition);

Flow:
  ▼
execute body  ← always runs at least once!
  │
  ▼
condition ──── true ──► back to body
  │ false
  ▼
done
```

```cpp
int count = 1;
do {
    cout << count << " ";
    count++;
} while (count <= 5);
// Output: 1 2 3 4 5

// The key difference — even when condition starts false:
int x = 10;
do {
    cout << "Runs once even though x > 5" << endl;
} while (x < 5);
// Output: Runs once even though x > 5
```

### Great for menus:

```cpp
int choice;
do {
    cout << "\n=== Menu ===\n";
    cout << "1. Start game\n";
    cout << "2. Settings\n";
    cout << "0. Quit\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
        case 1: cout << "Starting game...\n"; break;
        case 2: cout << "Opening settings...\n"; break;
        case 0: cout << "Goodbye!\n"; break;
        default: cout << "Invalid option.\n";
    }
} while (choice != 0);
```

---

## Range-Based `for` Loop (C++11)

A cleaner way to iterate over collections:

```cpp
// Iterate over an array
int arr[] = {10, 20, 30, 40, 50};
for (int x : arr) {
    cout << x << " ";
}
// Output: 10 20 30 40 50

// Iterate over a string
string s = "Hello";
for (char c : s) {
    cout << c << " ";
}
// Output: H e l l o

// Iterate over a vector
#include <vector>
vector<int> nums = {1, 2, 3, 4, 5};
for (int n : nums) {
    cout << n << " ";
}

// Use auto to avoid writing the type
for (auto x : arr) {
    cout << x << " ";
}
```

---

## Nested Loops

A loop inside a loop — used for 2D patterns, grids, matrices:

```cpp
// Multiplication table
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        cout << i * j << "\t";
    }
    cout << "\n";
}
/*
Output:
1  2  3
2  4  6
3  6  9
*/

// Printing a triangle
for (int i = 1; i <= 5; i++) {
    for (int j = 1; j <= i; j++) {
        cout << "* ";
    }
    cout << "\n";
}
/*
Output:
*
* *
* * *
* * * *
* * * * *
*/
```

---

## Choosing the Right Loop

| Situation | Use |
|-----------|-----|
| Know exact count | `for` |
| Know stopping condition, check first | `while` |
| Must run at least once | `do...while` |
| Iterating over collection | range-based `for` |

---

## Infinite Loops

```cpp
// Intentional infinite loop (needs a break inside)
while (true) {
    // process...
    if (done) break;
}

// Accidental infinite loop (bug)
int i = 0;
while (i < 10) {
    cout << i;
    // ← forgot i++! runs forever
}
```

---

## Key Takeaways

- `for` loop: best when you know the count — `for (init; condition; update)`
- `while` loop: best when you don't know the count — runs while condition is true
- `do...while`: like while, but body runs at least once before checking condition
- Range-based `for (auto x : collection)` is the cleanest way to iterate over arrays/vectors (C++11)
- Nested loops for 2D data (grids, matrices, patterns)
- Always update the loop variable to avoid infinite loops
