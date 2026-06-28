# Modern C++ (C++11 and Beyond)

> Source: https://www.programiz.com/cpp-programming/cpp11

---

## What Is "Modern C++"?

C++11 (released 2011) and later standards (C++14, C++17, C++20) added many features that make C++ cleaner, safer, and more expressive. These are the features every modern C++ developer should know.

> 🔁 **Analogy:** Old C++ was like driving a stick-shift with a map. Modern C++ adds GPS, automatic transmission, and lane assist — same powerful car, much smoother ride.

---

## `auto` — Type Inference

`auto` lets the compiler **deduce the type** automatically:

```cpp
// Old way
int x = 42;
double pi = 3.14;
vector<int>::iterator it = v.begin();

// Modern way
auto x = 42;           // int
auto pi = 3.14;        // double
auto it = v.begin();   // vector<int>::iterator — much cleaner!

auto name = string("Alice");   // string
auto nums = vector<int>{1,2,3};

// Great for complex types
map<string, vector<int>> data;
for (auto &pair : data) {   // instead of: map<string, vector<int>>::iterator
    // ...
}
```

> ⚠️ Be careful: `auto` can surprise you with const/reference:
```cpp
const int x = 5;
auto y = x;    // y is int (drops const)
auto &z = x;  // z is const int& (keeps const because of &)
```

---

## `decltype` — Get Type of Expression

```cpp
int x = 5;
decltype(x) y = 10;    // y is int (same type as x)

auto add(int a, int b) -> decltype(a + b) {  // trailing return type
    return a + b;
}
```

---

## Range-Based `for` Loop (Revisited)

```cpp
vector<int> nums = {1, 2, 3, 4, 5};

for (auto n : nums) {      // copy — can't modify
    cout << n << " ";
}

for (auto &n : nums) {     // reference — CAN modify
    n *= 2;
}

for (const auto &n : nums) {  // const reference — read only, no copy
    cout << n << " ";
}
```

---

## `nullptr` Instead of `NULL`

```cpp
// Old
int *p = NULL;   // NULL is just 0 — confusing

// Modern
int *p = nullptr;  // clearly a null pointer (not the number 0)

void foo(int x) { }
void foo(int *p) { }

foo(NULL);     // ❌ ambiguous — which overload?
foo(nullptr);  // ✅ clearly calls the pointer version
```

---

## Lambda Expressions

Anonymous (unnamed) functions — great for passing behavior to algorithms:

```cpp
// Basic lambda
auto greet = []() {
    cout << "Hello!" << endl;
};
greet();  // Hello!

// Lambda with parameters
auto add = [](int a, int b) {
    return a + b;
};
cout << add(3, 4);  // 7

// Lambda with capture
int multiplier = 3;
auto triple = [multiplier](int x) {
    return x * multiplier;  // captures multiplier from outer scope
};
cout << triple(5);  // 15

// Capture by reference (can modify outer variable)
int count = 0;
auto increment = [&count]() {
    count++;
};
increment(); increment(); increment();
cout << count;  // 3

// Capture all by value [=] or all by reference [&]
auto f = [=](int x) { return x + multiplier; };  // captures everything by copy
auto g = [&](int x) { count++; return x; };       // captures everything by reference
```

### Lambdas with STL algorithms:

```cpp
vector<int> v = {5, 2, 8, 1, 9, 3};

// Sort with custom comparator
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });  // descending

// Filter with remove_if
v.erase(remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), v.end());
// removes even numbers

// for_each with lambda
for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
```

---

## Smart Pointers

Raw pointers (`new`/`delete`) are error-prone — you can forget to `delete`. Smart pointers auto-delete:

### `unique_ptr` — One Owner

```cpp
#include <memory>

// Owns the object — automatically deleted when goes out of scope
unique_ptr<int> ptr = make_unique<int>(42);
cout << *ptr;   // 42

// No need for delete — auto-cleaned!
// ptr goes out of scope → int is automatically deleted

// Can't copy (only one owner)
// unique_ptr<int> ptr2 = ptr;  // ❌ Error!

// Can move ownership
unique_ptr<int> ptr2 = move(ptr);   // ptr is now null
cout << *ptr2;  // 42
```

### `shared_ptr` — Shared Ownership

```cpp
// Multiple owners — deleted when ALL owners are gone
shared_ptr<int> a = make_shared<int>(100);
shared_ptr<int> b = a;   // both point to same object, ref count = 2

cout << a.use_count();   // 2
{
    shared_ptr<int> c = a;   // ref count = 3
}  // c destroyed, ref count = 2

// deleted only when ref count reaches 0
```

### `weak_ptr` — Non-Owning Observer

```cpp
// Doesn't increase reference count — doesn't prevent deletion
shared_ptr<int> strong = make_shared<int>(5);
weak_ptr<int> weak = strong;

cout << weak.use_count();   // 1 (weak doesn't count)

// Must lock to use
if (auto locked = weak.lock()) {
    cout << *locked;   // safe to use
} else {
    cout << "Object deleted";
}
```

---

## Move Semantics

Avoid expensive copies by **moving** resources from temporaries:

```cpp
vector<int> original = {1, 2, 3, 4, 5};

// Copy — duplicates all elements (expensive)
vector<int> copy1 = original;

// Move — steals the internal data (free!)
vector<int> moved = move(original);
// original is now empty! its data was "moved" to moved

cout << moved.size();    // 5
cout << original.size(); // 0
```

```cpp
// Move constructor
class Resource {
    int *data;
public:
    Resource(int size) : data(new int[size]) {}

    // Move constructor — steal data from rvalue
    Resource(Resource &&other) noexcept : data(other.data) {
        other.data = nullptr;  // leave other in valid empty state
    }

    ~Resource() { delete[] data; }
};
```

---

## Structured Bindings (C++17)

Unpack multiple values elegantly:

```cpp
// Unpack pair
pair<string, int> p = {"Alice", 30};
auto [name, age] = p;   // structured binding!
cout << name << " is " << age;

// Unpack map iteration (no more .first and .second!)
map<string, int> ages = {{"Alice", 30}, {"Bob", 25}};
for (auto &[name, age] : ages) {
    cout << name << ": " << age << endl;
}

// Unpack tuple
tuple<int, string, double> t = {1, "hello", 3.14};
auto [i, s, d] = t;
```

---

## `std::optional` (C++17)

Represent a value that **might not exist**:

```cpp
#include <optional>

optional<int> findIndex(vector<int> &v, int target) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == target) return i;   // found
    }
    return nullopt;   // not found
}

vector<int> v = {10, 20, 30};
auto result = findIndex(v, 20);

if (result.has_value()) {
    cout << "Found at index: " << result.value();
} else {
    cout << "Not found";
}

// Shorthand
if (result) {
    cout << "Index: " << *result;
}
```

---

## Key Takeaways

- `auto` deduces types automatically — great for iterators and complex types
- `nullptr` is clearer than `NULL` — use it for null pointers
- Lambda expressions: `[capture](params) { body }` — pass behavior as a value
- Smart pointers auto-manage memory: `unique_ptr` (one owner), `shared_ptr` (shared), `weak_ptr` (non-owning)
- `make_unique<T>()` and `make_shared<T>()` are the preferred way to create smart pointers
- `std::move()` transfers ownership/resources without copying
- Structured bindings `auto [a, b] = pair` — C++17 unpacking syntax
- `std::optional<T>` — represent a value that may or may not exist (better than returning `-1` or `null`)
