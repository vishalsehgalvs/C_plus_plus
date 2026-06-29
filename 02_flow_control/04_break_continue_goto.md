# C++ break, continue, and goto

> Source: https://www.programiz.com/cpp-programming/break-statement

---

## `break` — Exit the Loop Early

`break` immediately **stops the loop** and jumps to the code after it.

> 🔁 **Analogy:** Like an emergency exit in a building. When something critical happens (you find what you're looking for, or an error occurs), you take the emergency exit immediately.

```
while (condition) {
    if (special_case) break;  ──► exits the loop NOW
    normal code;
}
code_after_loop;  ← execution jumps here after break
```

```cpp
// Find first even number in a list
int arr[] = {3, 7, 11, 4, 9, 2};

for (int i = 0; i < 6; i++) {
    if (arr[i] % 2 == 0) {
        cout << "First even number: " << arr[i] << endl;
        break;  // found it — stop searching
    }
}
// Output: First even number: 4
```

### Practical: search in array

```cpp
#include <iostream>
using namespace std;

int main() {
    int data[] = {10, 25, 3, 47, 8, 99};
    int target = 47;
    bool found = false;

    for (int i = 0; i < 6; i++) {
        if (data[i] == target) {
            cout << "Found " << target << " at index " << i << endl;
            found = true;
            break;  // no need to keep searching
        }
    }

    if (!found) cout << target << " not found." << endl;

    return 0;
}
// Output: Found 47 at index 3
```

### `break` in nested loops

⚠️ `break` only exits the **innermost** loop:

```cpp
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (j == 1) break;  // ← only exits the j loop
        cout << i << "," << j << " ";
    }
}
// Output: 0,0  1,0  2,0
// (breaks out of j loop each time j==1, but i loop continues)
```

---

## `continue` — Skip This Iteration

`continue` skips the **rest of the current iteration** and jumps to the next one.

> 🔁 **Analogy:** Like skipping a bad song on a playlist. You don't stop listening — you just skip this one and go to the next.

```
for (int i = 0; i < 10; i++) {
    if (skip_condition) continue;  ──► skip, go to next i
    process_normally;
}
```

```cpp
// Print only odd numbers
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) continue;  // skip even numbers
    cout << i << " ";
}
// Output: 1 3 5 7 9
```

```cpp
// Skip invalid values
int scores[] = {85, -1, 92, -1, 78, 100};

int total = 0, count = 0;
for (int i = 0; i < 6; i++) {
    if (scores[i] < 0) continue;  // skip invalid scores
    total += scores[i];
    count++;
}
cout << "Average: " << (double)total / count << endl;
// Average: 88.75
```

---

## `break` vs `continue` — Side by Side

```cpp
// break: exit the loop entirely
for (int i = 0; i < 10; i++) {
    if (i == 5) break;
    cout << i << " ";
}
// Output: 0 1 2 3 4

// continue: skip just this iteration
for (int i = 0; i < 10; i++) {
    if (i == 5) continue;
    cout << i << " ";
}
// Output: 0 1 2 3 4 6 7 8 9
//                       ↑ 5 is missing but loop continues!
```

```
break:
[0][1][2][3][4][X]──stop here
                 ↑ exit at 5

continue:
[0][1][2][3][4][skip][6][7][8][9]
                 ↑ skip 5, keep going
```

---

## `break` in `switch`

`break` is also used in `switch` to prevent fall-through:

```cpp
int choice = 2;
switch (choice) {
    case 1: cout << "one"; break;
    case 2: cout << "two"; break;  // ← without break, falls to case 3
    case 3: cout << "three"; break;
}
```

---

## `goto` — Jump Anywhere (Use Sparingly)

`goto` jumps to a **labeled** position in the code.

> ⚠️ **Avoid `goto`** in modern C++. It makes code hard to follow ("spaghetti code"). There's almost always a better way using loops, break, or functions.

```cpp
#include <iostream>
using namespace std;

int main() {
    int i = 0;

    loop_start:  // ← label (ends with :)
    if (i < 5) {
        cout << i << " ";
        i++;
        goto loop_start;  // jump back to label
    }
    // Output: 0 1 2 3 4
    return 0;
}
```

The one legitimate use case: breaking out of deeply nested loops (where `break` only exits the innermost):

```cpp
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
        for (int k = 0; k < 10; k++) {
            if (someCondition(i, j, k)) {
                goto done;  // exits ALL three loops at once
            }
        }
    }
}
done:
cout << "Exited all loops" << endl;
```

Even for this case, consider refactoring into a function with `return` instead.

---

## Key Takeaways

- `break` immediately exits the current loop (or switch case)
- `continue` skips the rest of the current iteration and moves to the next
- In nested loops, `break`/`continue` only affect the **innermost** loop
- `goto` jumps to a labeled location — avoid it in modern code (hard to maintain)
- Use `break` when you've found what you're looking for and don't need to continue
- Use `continue` to skip invalid/unwanted values without exiting the entire loop
