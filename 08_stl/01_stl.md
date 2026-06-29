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

|              | `map`             | `unordered_map`   |
| ------------ | ----------------- | ----------------- |
| Order        | Sorted by key     | No order          |
| Lookup speed | O(log n)          | O(1) average      |
| Insert speed | O(log n)          | O(1) average      |
| Memory       | Less              | More (hash table) |
| Use when     | Need sorted order | Need speed        |

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

## `deque` — Double-Ended Queue

Like `vector` but you can push/pop from **both** the front and back efficiently:

```
deque layout:
 front                          back
   ↓                             ↓
 [ 10 | 20 | 30 | 40 | 50 ]
   ↑ push_front / pop_front      ↑ push_back / pop_back
```

```cpp
#include <deque>

deque<int> dq = {20, 30, 40};

dq.push_back(50);   // add to back  → {20, 30, 40, 50}
dq.push_front(10);  // add to front → {10, 20, 30, 40, 50}

dq.pop_front();     // remove front → {20, 30, 40, 50}
dq.pop_back();      // remove back  → {20, 30, 40}

cout << dq.front();  // 20
cout << dq.back();   // 40
cout << dq[1];       // 30 (random access like vector)
```

> 💡 Use `deque` when you need fast insertion/removal at **both** ends. Use `vector` when you only need the back.

---

## `list` — Doubly Linked List

Each element knows its previous and next neighbour. No random access (`list[i]` doesn't work), but **fast insert/erase anywhere**:

```
list layout:
 [10] ⟷ [20] ⟷ [30] ⟷ [40]
```

```cpp
#include <list>

list<int> lst = {10, 30, 40};

lst.push_front(5);   // front → {5, 10, 30, 40}
lst.push_back(50);   // back  → {5, 10, 30, 40, 50}

// Insert before position
auto it = lst.begin();
advance(it, 2);          // move iterator 2 steps forward
lst.insert(it, 99);      // {5, 10, 99, 30, 40, 50}

lst.remove(99);          // remove by VALUE (all occurrences)
lst.erase(lst.begin());  // remove by position

// list-specific operations
lst.sort();              // built-in sort (std::sort won't work on list!)
lst.reverse();
lst.unique();            // remove consecutive duplicates

for (int x : lst) cout << x << " ";
```

| Feature              | `vector`       | `list`               |
| -------------------- | -------------- | -------------------- |
| Random access `v[i]` | ✅ O(1)        | ❌                   |
| Insert at end        | O(1) amortized | O(1)                 |
| Insert in middle     | O(n)           | O(1)                 |
| Memory layout        | Contiguous     | Scattered (pointers) |

---

## `priority_queue` — Heap

Always gives you the **largest (or smallest) element first**. Like a VIP queue — most important goes first:

```
max-heap (default):      min-heap:
      9                      1
     / \                    / \
    5   8                  4   3
   / \                    / \
  2   4                  8   6
```

```cpp
#include <queue>

// MAX heap (default) — largest element at top
priority_queue<int> maxPQ;
maxPQ.push(5);
maxPQ.push(2);
maxPQ.push(9);
maxPQ.push(1);

cout << maxPQ.top();  // 9 (largest)
maxPQ.pop();
cout << maxPQ.top();  // 5

// MIN heap — smallest element at top
priority_queue<int, vector<int>, greater<int>> minPQ;
minPQ.push(5);
minPQ.push(2);
minPQ.push(9);

cout << minPQ.top();  // 2 (smallest)

// Priority queue of pairs — sorted by first element
priority_queue<pair<int,string>> taskQueue;
taskQueue.push({3, "Low priority task"});
taskQueue.push({9, "Critical bug"});
taskQueue.push({5, "Feature request"});

while (!taskQueue.empty()) {
    auto [pri, name] = taskQueue.top();
    cout << pri << ": " << name << endl;
    taskQueue.pop();
}
// 9: Critical bug
// 5: Feature request
// 3: Low priority task
```

> 💡 **Common use cases:** Dijkstra's shortest path, scheduling, finding top-K elements.

---

## `unordered_set` — Fast Unique Values

Like `set` but uses a **hash table** — faster lookup but no sorted order:

```cpp
#include <unordered_set>

unordered_set<string> visited;
visited.insert("page1");
visited.insert("page2");
visited.insert("page1");   // duplicate — ignored

cout << visited.count("page1");  // 1
cout << visited.count("page3");  // 0

// Use case: "have we seen this before?"
vector<int> nums = {1, 2, 3, 2, 1, 4};
unordered_set<int> seen;
for (int x : nums) {
    if (seen.count(x)) cout << x << " is a duplicate!" << endl;
    seen.insert(x);
}
```

|            | `set`    | `unordered_set` |
| ---------- | -------- | --------------- |
| Order      | Sorted   | No order        |
| Lookup     | O(log n) | O(1) average    |
| Duplicates | No       | No              |

---

## `multimap` and `multiset` — Allowing Duplicates

Normal `map`/`set` reject duplicates. `multimap`/`multiset` **allow** them:

```cpp
#include <map>
#include <set>

// multiset — sorted, duplicates allowed
multiset<int> ms = {5, 2, 8, 2, 5, 1};
for (int x : ms) cout << x << " ";
// Output: 1 2 2 5 5 8

ms.erase(ms.find(2));  // remove just ONE occurrence of 2
for (int x : ms) cout << x << " ";
// Output: 1 2 5 5 8

// multimap — multiple values per key
multimap<string, string> phonebook;
phonebook.insert({"Alice", "111-1111"});
phonebook.insert({"Alice", "222-2222"});  // Alice has two numbers!
phonebook.insert({"Bob",   "333-3333"});

// Find all numbers for Alice
auto range = phonebook.equal_range("Alice");
for (auto it = range.first; it != range.second; ++it) {
    cout << it->first << ": " << it->second << endl;
}
// Alice: 111-1111
// Alice: 222-2222
```

---

## `std::array` — Fixed-Size Modern Array

A safer, STL-compatible wrapper around C-style arrays. Size is fixed at compile time:

```cpp
#include <array>

array<int, 5> arr = {3, 1, 4, 1, 5};

arr[0] = 10;
arr.at(1) = 20;   // bounds-checked

cout << arr.size();   // 5  (always known at compile time)
cout << arr.front();  // 10
cout << arr.back();   // 5

sort(arr.begin(), arr.end());

// Works with range-for
for (int x : arr) cout << x << " ";

// Pass to function (unlike C arrays, it doesn't decay to pointer)
auto printArr = [](array<int, 5>& a) {
    for (int x : a) cout << x << " ";
};
```

> 🔁 **Analogy:** `std::array` is a C array wearing a suit — same raw speed, but now it knows its own size and works with all STL algorithms.

---

## `pair` and `tuple` — Bundling Values Together

### `pair` — exactly two values of potentially different types

```cpp
#include <utility>

pair<string, int> p1 = {"Alice", 30};
cout << p1.first << " is " << p1.second << " years old" << endl;

// make_pair — type deduction
auto p2 = make_pair("Bob", 25);

// Very common in maps
map<string, int> ages;
ages.insert(make_pair("Carol", 35));

// Sorting vector of pairs — sorts by first, then second
vector<pair<int,string>> scores = {{95,"Alice"},{87,"Bob"},{95,"Carol"}};
sort(scores.begin(), scores.end());   // sorts by score, then name
```

### `tuple` — any number of values

```cpp
#include <tuple>

tuple<string, int, double> person = {"Alice", 30, 5.6};

cout << get<0>(person);  // "Alice"
cout << get<1>(person);  // 30
cout << get<2>(person);  // 5.6

// C++17 structured bindings — much cleaner!
auto [name, age, height] = person;
cout << name << " " << age << " " << height << endl;

// tie — unpack into existing variables
string n; int a; double h;
tie(n, a, h) = person;
```

---

## `emplace_back` vs `push_back`

Both add elements to the end of a container, but:

```cpp
vector<pair<int, string>> v;

// push_back: you create the object THEN copy/move it in
v.push_back(make_pair(1, "Alice"));     // creates temp, then moves it in
v.push_back({2, "Bob"});                // same

// emplace_back: constructs DIRECTLY inside the vector (no temp object)
v.emplace_back(3, "Carol");             // passes args straight to constructor
v.emplace_back(4, "Dave");             // always prefer this!
```

> 💡 **Rule of thumb:** Prefer `emplace_back` — it's never slower and often faster. Use `push_back` only when you already have a finished object.

---

## `vector` Memory Management — `reserve` and `capacity`

`vector` doubles its internal buffer whenever it runs out of space. This causes copying:

```
push_back calls:   1     2     3     4     5     6     7     8     9
buffer doubles:   [_]  [__]  [____]              [________]
                   1    2     4                       8
```

```cpp
vector<int> v;
cout << v.capacity();  // 0 (no memory allocated yet)

v.push_back(1);
cout << v.capacity();  // 1

v.push_back(2);
cout << v.capacity();  // 2

v.push_back(3);
cout << v.capacity();  // 4 (doubled!)

// SOLUTION: reserve upfront if you know the size
vector<int> fast;
fast.reserve(1000);   // allocate memory for 1000 elements now
cout << fast.capacity();  // 1000
cout << fast.size();      // 0  (reserved ≠ filled)

for (int i = 0; i < 1000; i++) fast.push_back(i);  // no reallocations!

// shrink_to_fit — release unused memory
fast.shrink_to_fit();
```

---

## More Useful Algorithms (`<algorithm>` + `<numeric>`)

```cpp
#include <algorithm>
#include <numeric>
vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5};

// binary_search (requires sorted input!)
sort(v.begin(), v.end());  // {1, 1, 2, 3, 4, 5, 5, 6, 9}
bool found = binary_search(v.begin(), v.end(), 5);  // true

// lower_bound — first element >= target
auto lb = lower_bound(v.begin(), v.end(), 5);   // points to first 5
cout << (lb - v.begin());  // index 5

// upper_bound — first element > target
auto ub = upper_bound(v.begin(), v.end(), 5);   // points to 6
cout << (ub - v.begin());  // index 7

// Count occurrences using bounds
cout << (ub - lb);  // 2  (how many 5s exist)

// copy_if — copy elements matching condition
vector<int> evens;
copy_if(v.begin(), v.end(), back_inserter(evens), [](int x){ return x % 2 == 0; });
// evens: {2, 4, 6}

// remove_if — doesn't actually remove! returns new logical end
auto newEnd = remove_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
v.erase(newEnd, v.end());   // now actually erase them
// v: {1, 1, 3, 5, 5, 9}

// fill — set all elements to a value
vector<int> filled(5);
fill(filled.begin(), filled.end(), 7);  // {7, 7, 7, 7, 7}

// iota — fill with incrementing values
vector<int> seq(5);
iota(seq.begin(), seq.end(), 1);  // {1, 2, 3, 4, 5}

// unique — collapse consecutive duplicates (requires sorted!)
vector<int> u = {1, 1, 2, 3, 3, 3, 4};
auto uEnd = unique(u.begin(), u.end());
u.erase(uEnd, u.end());  // {1, 2, 3, 4}

// next_permutation — cycle through all arrangements
vector<int> perm = {1, 2, 3};
do {
    for (int x : perm) cout << x << " ";
    cout << endl;
} while (next_permutation(perm.begin(), perm.end()));
// 1 2 3 / 1 3 2 / 2 1 3 / 2 3 1 / 3 1 2 / 3 2 1

// nth_element — guarantees element at position k is what it would be in sorted order
vector<int> n2 = {7, 3, 1, 8, 4, 2};
nth_element(n2.begin(), n2.begin() + 2, n2.end());
cout << n2[2];  // 3 (3rd smallest) — others may be in any order

// partial_sum — running total
vector<int> vals = {1, 2, 3, 4, 5};
vector<int> running(5);
partial_sum(vals.begin(), vals.end(), running.begin());
// running: {1, 3, 6, 10, 15}
```

---

## Iterators — Categories and Usage

Iterators are like pointers that navigate through containers. Different containers give different **iterator strengths**:

```
Iterator Category Hierarchy:
                     Random Access (vector, deque, array)
                           |  supports: it+n, it-n, it[n], <, >
                     Bidirectional (list, map, set)
                           |  supports: ++it, --it
                     Forward (forward_list, unordered_map)
                           |  supports: ++it only
                     Input / Output
                              (streams)
```

```cpp
vector<int> v = {10, 20, 30, 40, 50};

// Explicit iterator
vector<int>::iterator it = v.begin();
it += 2;           // jump ahead 2 (random access)
cout << *it;       // 30

// Reverse iterator
for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
    cout << *rit << " ";   // 50 40 30 20 10
}

// Const iterator (can't modify elements)
for (auto cit = v.cbegin(); cit != v.cend(); ++cit) {
    cout << *cit << " ";
}

// std::advance — works on ALL iterator types (even non-random-access)
list<int> lst = {1, 2, 3, 4, 5};
auto lit = lst.begin();
advance(lit, 3);   // move 3 steps forward
cout << *lit;      // 4

// std::distance — count steps between two iterators
cout << distance(lst.begin(), lit);  // 3

// std::next / std::prev — get iterator at offset (C++11)
auto next3 = next(v.begin(), 3);   // v.begin() + 3
auto prev1 = prev(v.end(), 1);     // last element
cout << *next3 << " " << *prev1;   // 40 50
```

---

## Quick Container Chooser

```
What do you need?
        │
        ├── Need key-value pairs?
        │       ├── Yes → sorted? → map  (O log n)
        │       │         no?    → unordered_map  (O 1)
        │       │         duplicates? → multimap
        │       └── No ↓
        │
        ├── Need unique elements only?
        │       ├── sorted? → set
        │       └── fast?   → unordered_set
        │
        ├── Need sequence of elements?
        │       ├── index access + push_back → vector  ← default choice
        │       ├── fast front+back insert   → deque
        │       ├── fast middle insert/erase → list
        │       └── fixed compile-time size  → std::array
        │
        ├── Need LIFO (stack)?        → stack
        ├── Need FIFO (queue)?        → queue
        └── Need highest/lowest first? → priority_queue
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

**Containers:**

- `vector<T>` — dynamic array, default choice for sequences
- `deque<T>` — fast push/pop at both ends
- `list<T>` — fast insert/erase anywhere, no random access
- `array<T,N>` — fixed size, stack-allocated, safer than C arrays
- `map<K,V>` — sorted key-value, O(log n); `unordered_map` for O(1)
- `set<T>` — unique sorted values; `unordered_set` for O(1) lookup
- `multimap` / `multiset` — allow duplicate keys/values
- `stack<T>` — LIFO; `queue<T>` — FIFO; `priority_queue<T>` — always pop largest
- `pair<A,B>` — two values; `tuple<...>` — any number of values

**Algorithms (`<algorithm>` + `<numeric>`):**

- `sort`, `reverse`, `find`, `count`, `min_element`, `max_element`
- `binary_search`, `lower_bound`, `upper_bound` — for sorted ranges
- `copy_if`, `remove_if` — filter elements
- `transform`, `for_each` — apply function to elements
- `any_of`, `all_of`, `none_of` — test conditions
- `fill`, `iota`, `accumulate`, `partial_sum` — fill and reduce
- `unique`, `nth_element`, `next_permutation` — advanced manipulation
- `emplace_back` over `push_back` — construct in-place, no temp object
- `reserve` on vector upfront when size is known — avoids reallocations

**Iterators:**

- All containers expose `begin()`/`end()` — work with all algorithms
- `rbegin()`/`rend()` for reverse traversal
- `advance`, `next`, `prev`, `distance` — iterator utilities
- Use `auto` to avoid writing out verbose iterator types
