# C++ Standard Template Library (STL)

> Source: https://www.programiz.com/cpp-programming/standard-template-library

---

## What Is the STL?

The **Standard Template Library** is a collection of ready-to-use data structures, algorithms, and iterators included with C++.

> 🔁 **Analogy:** The STL is like a professional chef's kitchen. Instead of building your own tools from scratch (knife, pot, whisk), you use the professional-grade ones already there. They're well-tested, optimized, and work great.

```
STL Components:
┌────────────────────────────────────────────────────┐
│  Containers  │  Algorithms  │  Iterators            │
│  (store data)│  (work on    │  (navigate through    │
│              │   containers)│   containers)         │
├──────────────┼──────────────┼───────────────────────┤
│ vector       │ sort         │ begin / end           │
│ list         │ find         │ iterator types        │
│ map          │ count        │ auto traversal        │
│ set          │ transform    │                       │
│ queue        │ for_each     │                       │
│ stack        │ binary_search│                       │
└──────────────┴──────────────┴───────────────────────┘
```

---

## `vector` — Dynamic Array

The most commonly used STL container. Like an array that **grows automatically**.

```cpp
#include <vector>
using namespace std;

vector<int> v;            // empty vector
vector<int> v2 = {1, 2, 3, 4, 5};
vector<int> v3(5, 0);     // 5 elements, all = 0

// Add elements
v.push_back(10);
v.push_back(20);
v.push_back(30);

// Access
cout << v[1];        // 20 (no bounds check)
cout << v.at(1);     // 20 (with bounds check)
cout << v.front();   // 10 (first)
cout << v.back();    // 30 (last)

// Size
cout << v.size();    // 3

// Remove last element
v.pop_back();        // removes 30

// Iterate
for (int x : v) cout << x << " ";

// Sort
#include <algorithm>
sort(v.begin(), v.end());   // ascending
sort(v.begin(), v.end(), greater<int>());  // descending

// Insert at position
v.insert(v.begin() + 1, 99);  // insert 99 at index 1

// Remove at position
v.erase(v.begin() + 1);  // remove element at index 1

// Clear all
v.clear();

// Check if empty
if (v.empty()) cout << "Empty!";
```

---

## `map` — Key-Value Pairs (Sorted)

A sorted dictionary — stores unique key-value pairs, automatically sorted by key.

```cpp
#include <map>

map<string, int> ages;

// Insert
ages["Alice"] = 30;
ages["Bob"] = 25;
ages["Carol"] = 35;
ages.insert({"Dave", 28});

// Access
cout << ages["Alice"];   // 30
cout << ages.at("Bob");  // 25

// Iterate (sorted by key!)
for (auto &pair : ages) {
    cout << pair.first << ": " << pair.second << endl;
}
// Alice: 30
// Bob: 25
// Carol: 35
// Dave: 28

// Check if key exists
if (ages.count("Alice")) {
    cout << "Alice found";
}

if (ages.find("Alice") != ages.end()) {
    cout << "Alice found";
}

// Delete
ages.erase("Bob");

// Size
cout << ages.size();  // 3
```

---

## `unordered_map` — Key-Value Pairs (Faster, Unsorted)

Like `map` but uses hash table — **faster** (O(1) average) but **no ordering**:

```cpp
#include <unordered_map>

unordered_map<string, int> scores;
scores["Alice"] = 95;
scores["Bob"] = 87;
scores["Carol"] = 92;

// Same API as map, but no guaranteed order when iterating
for (auto &[name, score] : scores) {  // structured binding C++17
    cout << name << ": " << score << endl;
}
```

| | `map` | `unordered_map` |
|--|-------|-----------------|
| Order | Sorted by key | No order |
| Lookup speed | O(log n) | O(1) average |
| Insert speed | O(log n) | O(1) average |
| Memory | Less | More (hash table) |
| Use when | Need sorted order | Need speed |

---

## `set` — Unique Sorted Values

Stores **unique** elements in **sorted order**. No duplicates allowed:

```cpp
#include <set>

set<int> s;
s.insert(5);
s.insert(2);
s.insert(8);
s.insert(2);   // duplicate — ignored!
s.insert(1);

for (int x : s) cout << x << " ";
// Output: 1 2 5 8  (sorted! duplicates gone!)

cout << s.count(5);    // 1 (exists)
cout << s.count(99);   // 0 (doesn't exist)

s.erase(2);
cout << s.size();  // 3
```

---

## `stack` — LIFO

Last-In, First-Out. Like a stack of plates:

```cpp
#include <stack>

stack<int> st;
st.push(1);   // add to top
st.push(2);
st.push(3);

cout << st.top();   // 3 (peek top — doesn't remove)
st.pop();           // remove top
cout << st.top();   // 2
cout << st.size();  // 2
cout << st.empty(); // false
```

---

## `queue` — FIFO

First-In, First-Out. Like a line at a store:

```cpp
#include <queue>

queue<string> q;
q.push("Alice");  // add to back
q.push("Bob");
q.push("Carol");

cout << q.front();  // "Alice" (first in)
q.pop();            // remove front
cout << q.front();  // "Bob"
cout << q.size();   // 2
```

---

## Common STL Algorithms (`<algorithm>`)

```cpp
#include <algorithm>
#include <vector>

vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// Sort
sort(v.begin(), v.end());   // {1, 1, 2, 3, 4, 5, 6, 9}

// Reverse
reverse(v.begin(), v.end()); // {9, 6, 5, 4, 3, 2, 1, 1}

// Find
auto it = find(v.begin(), v.end(), 5);
if (it != v.end()) cout << "Found 5 at index " << (it - v.begin());

// Count
int cnt = count(v.begin(), v.end(), 1);  // 2

// Min/Max element
auto minIt = min_element(v.begin(), v.end());  // iterator to minimum
auto maxIt = max_element(v.begin(), v.end());
cout << *minIt << " " << *maxIt;

// Sum (accumulate)
#include <numeric>
int sum = accumulate(v.begin(), v.end(), 0);  // 0 = starting value

// Check conditions
bool anyNeg = any_of(v.begin(), v.end(), [](int x){ return x < 0; });
bool allPos = all_of(v.begin(), v.end(), [](int x){ return x > 0; });

// Transform (like map in JS)
vector<int> doubled(v.size());
transform(v.begin(), v.end(), doubled.begin(), [](int x){ return x * 2; });

// for_each
for_each(v.begin(), v.end(), [](int x){ cout << x << " "; });
```

---

## Iterators

Iterators are like pointers that navigate through containers:

```cpp
vector<int> v = {10, 20, 30, 40, 50};

// Using iterator explicitly
vector<int>::iterator it;
for (it = v.begin(); it != v.end(); it++) {
    cout << *it << " ";    // dereference to get value
}

// With auto (much cleaner!)
for (auto it = v.begin(); it != v.end(); it++) {
    cout << *it << " ";
}

// Range-based for uses iterators under the hood
for (int x : v) cout << x << " ";
```

---

## Key Takeaways

- `vector<T>` — dynamic array: `push_back`, `pop_back`, `size`, `sort`
- `map<K,V>` — sorted key-value store: `O(log n)` lookup; `unordered_map` for `O(1)` speed
- `set<T>` — unique sorted values; `unordered_set` for faster unsorted version
- `stack<T>` — LIFO; `queue<T>` — FIFO
- `#include <algorithm>` — `sort`, `find`, `count`, `transform`, `for_each`, `any_of`, `all_of`
- All containers have `begin()`/`end()` for iterators and work with range-based `for`
- Use `auto` with iterators to avoid verbose type names
