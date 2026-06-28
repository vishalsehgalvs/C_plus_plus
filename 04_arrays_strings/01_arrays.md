# C++ Arrays

> Source: https://www.programiz.com/cpp-programming/arrays

---

## What Is an Array?

An array is a **collection of elements of the same type** stored in **contiguous memory**, accessible by index.

> 🔁 **Analogy:** An array is like a row of lockers. Each locker (element) has a number (index) starting from 0. You access any locker directly by its number.

```
Index:   0     1     2     3     4
       ┌─────┬─────┬─────┬─────┬─────┐
arr:   │ 10  │ 20  │ 30  │ 40  │ 50  │
       └─────┴─────┴─────┴─────┴─────┘
       ↑ first                  ↑ last (size-1)
```

---

## Declaring and Initializing Arrays

```cpp
// Declare array of 5 integers (uninitialized)
int scores[5];

// Declare and initialize
int scores[5] = {85, 92, 78, 95, 88};

// C++ deduces size automatically
int scores[] = {85, 92, 78, 95, 88};  // size = 5

// Partial initialization (rest = 0)
int arr[5] = {1, 2};  // {1, 2, 0, 0, 0}

// All zeros
int zeros[5] = {};  // {0, 0, 0, 0, 0}

// Fixed size with const
const int SIZE = 5;
int data[SIZE];
```

---

## Accessing Elements

```cpp
int arr[] = {10, 20, 30, 40, 50};

cout << arr[0];   // 10 (first element)
cout << arr[2];   // 30 (third element)
cout << arr[4];   // 50 (last element)

// Modify elements
arr[0] = 100;
cout << arr[0];   // now 100
```

> ⚠️ **Array index out of bounds** is undefined behavior — C++ does NOT check bounds for you!
```cpp
int arr[5] = {1, 2, 3, 4, 5};
cout << arr[10];  // ❌ undefined behavior — could crash, corrupt memory, anything
```

---

## Looping Through Arrays

```cpp
int scores[] = {85, 92, 78, 95, 88};
int size = 5;

// Classic for loop
for (int i = 0; i < size; i++) {
    cout << scores[i] << " ";
}
// 85 92 78 95 88

// Range-based for (C++11) — cleaner!
for (int score : scores) {
    cout << score << " ";
}

// With auto
for (auto score : scores) {
    cout << score << " ";
}
```

---

## Common Array Operations

```cpp
int arr[] = {64, 25, 12, 22, 11};
int n = 5;

// Sum and average
int sum = 0;
for (int i = 0; i < n; i++) sum += arr[i];
double avg = (double)sum / n;
cout << "Sum: " << sum << ", Avg: " << avg << endl;

// Find maximum
int maxVal = arr[0];
for (int i = 1; i < n; i++) {
    if (arr[i] > maxVal) maxVal = arr[i];
}
cout << "Max: " << maxVal << endl;

// Find minimum
int minVal = arr[0];
for (int i = 1; i < n; i++) {
    if (arr[i] < minVal) minVal = arr[i];
}

// Count occurrences of a value
int target = 22, count = 0;
for (int i = 0; i < n; i++) {
    if (arr[i] == target) count++;
}
```

---

## Passing Arrays to Functions

```cpp
// Arrays are passed by pointer (original can be modified!)
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Double all elements
void doubleArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // modifies original!
    }
}

int main() {
    int nums[] = {1, 2, 3, 4, 5};
    printArray(nums, 5);   // 1 2 3 4 5
    doubleArray(nums, 5);
    printArray(nums, 5);   // 2 4 6 8 10
}
```

> ⚠️ When you pass an array to a function, C++ doesn't know its size! Always pass the size as a separate parameter.

---

## Multidimensional Arrays

### 2D Array (Matrix)

```cpp
// Declare: type name[rows][cols]
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

// Access: matrix[row][col]
cout << matrix[0][0];  // 1 (top-left)
cout << matrix[1][2];  // 6 (row 1, col 2)
cout << matrix[2][2];  // 9 (bottom-right)

// Loop through 2D array
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        cout << matrix[i][j] << " ";
    }
    cout << "\n";
}
/*
Output:
1 2 3
4 5 6
7 8 9
*/
```

---

## `std::array` (Modern C++ — Safer)

The C-style array (`int arr[5]`) has no bounds checking and loses size info when passed to functions. `std::array` is safer:

```cpp
#include <array>
using namespace std;

array<int, 5> arr = {1, 2, 3, 4, 5};

cout << arr.size();    // 5 — knows its own size!
cout << arr[2];        // 3
cout << arr.at(2);     // 3 — with bounds checking (throws exception if out of range)

// Range-based for works
for (int x : arr) cout << x << " ";
```

---

## Array vs Vector

For most real work, use `vector` (dynamic size) instead of a fixed-size array:

```cpp
#include <vector>

vector<int> v = {1, 2, 3};
v.push_back(4);   // add element — grows automatically
v.push_back(5);
cout << v.size();  // 5
```

| | C-style array | `std::array` | `std::vector` |
|--|--------------|--------------|---------------|
| Size | Fixed at compile time | Fixed at compile time | Dynamic (can grow) |
| Size info | No | `arr.size()` | `v.size()` |
| Bounds check | No | `at()` yes, `[]` no | `at()` yes, `[]` no |
| Pass to function | Loses size | Passes with size | Passes with size |
| Overhead | None | Minimal | Small (heap alloc) |

---

## Key Takeaways

- Arrays store same-type elements in contiguous memory, accessed by zero-based index
- `int arr[5] = {1,2,3,4,5}` — declare and initialize
- Loop with `for (int i = 0; i < size; i++)` or range-based `for (int x : arr)`
- Always pass array size separately when passing to functions — arrays don't know their own size
- **Never** access out-of-bounds indices — undefined behavior!
- `std::array<int, 5>` is the modern safe version (knows its size, optional bounds checking)
- For dynamic sizes, prefer `std::vector` — it grows automatically
