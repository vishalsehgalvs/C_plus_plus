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

## `constexpr` — Compute at Compile Time

`constexpr` tells the compiler: "compute this at compile time if possible":

```cpp
// constexpr function — runs at compile time when given constants
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

constexpr int f5 = factorial(5);   // calculated at compile time: 120
// No runtime cost at all — compiler just puts 120 in the binary!

// At runtime too (with a non-const arg)
int n;
cin >> n;
cout << factorial(n);   // runs at runtime, still works

// constexpr variables
constexpr double PI    = 3.14159265358979;
constexpr int    LIMIT = 100;

// Works in if conditions and array sizes
int arr[factorial(4)];    // arr[24] — size known at compile time
```

---

## `if constexpr` — Compile-Time Branching (C++17)

`if constexpr` chooses code paths **at compile time**, not runtime. Unused branches aren't even compiled:

```cpp
template <typename T>
void process(T value) {
    if constexpr (is_integral_v<T>) {
        cout << "Integer: " << value << " (bit count: " << sizeof(T)*8 << ")" << endl;
    } else if constexpr (is_floating_point_v<T>) {
        cout << fixed << setprecision(4);
        cout << "Float: " << value << endl;
    } else {
        cout << "Other: " << value << endl;
    }
    // Only the matching branch is compiled for each T
}

process(42);        // Integer: 42 (bit count: 32)
process(3.14);      // Float: 3.1400
process("hello");   // Other: hello
```

> 💡 With regular `if`, all branches must compile even if never taken. `if constexpr` avoids that — critical for template code where some branches would be compile errors for certain types.

---

## `std::variant` — Type-Safe Union (C++17)

A variable that can hold **one of several types**, but you always know which one it holds:

```cpp
#include <variant>

variant<int, double, string> v;

v = 42;          // now holds int
cout << get<int>(v) << endl;    // 42

v = 3.14;        // now holds double
cout << get<double>(v) << endl; // 3.14

v = "hello";     // now holds string
cout << get<string>(v) << endl; // hello

// Check what type it holds
cout << v.index() << endl;      // 2 (index of string in the variant list)
cout << holds_alternative<string>(v) << endl;  // true

// get_if — safe access (returns pointer, null if wrong type)
if (auto* s = get_if<string>(&v)) {
    cout << "String value: " << *s << endl;
}

// visit — handle all cases (like a switch for types)
visit([](auto& val) {
    cout << "Value is: " << val << endl;
}, v);

// Real-world use: represent a result that's either data or an error
variant<string, int> result;
result = "Error: file not found";   // error case
result = 200;                        // success code
```

> 💡 `std::variant` replaces the old C-style `union`. Unlike union, it tracks which type is active and won't let you accidentally read the wrong type.

---

## `std::any` — Hold Any Type (C++17)

`std::any` stores a value of **any type** (unlike `variant`, the types don't need to be listed upfront):

```cpp
#include <any>

any a = 42;
cout << any_cast<int>(a) << endl;   // 42

a = string("hello");
cout << any_cast<string>(a) << endl;  // hello

a = 3.14;
cout << any_cast<double>(a) << endl;  // 3.14

// Check type before casting
if (a.type() == typeid(double)) {
    cout << "It's a double: " << any_cast<double>(a) << endl;
}

// any_cast with pointer — returns null if wrong type (no exception)
if (auto* p = any_cast<double>(&a)) {
    cout << *p << endl;
}

// Heterogeneous container — store different types in one vector
vector<any> bag = { 1, 2.5, string("hello"), true };
for (auto& item : bag) {
    if (item.type() == typeid(int))    cout << "int: "    << any_cast<int>(item) << endl;
    if (item.type() == typeid(double)) cout << "double: " << any_cast<double>(item) << endl;
    if (item.type() == typeid(string)) cout << "string: " << any_cast<string>(item) << endl;
}
```

> ⚠️ `std::any` is flexible but has runtime overhead and loses type-safety. Prefer `std::variant` when you know the possible types upfront.

---

## Concepts — Template Constraints (C++20)

Concepts let you specify **requirements** for template parameters. No more cryptic 100-line error messages:

```cpp
#include <concepts>

// Old way: works but gives unreadable errors if T is wrong
template <typename T>
T addOld(T a, T b) { return a + b; }

// New way (C++20): requires T to be a number type
template <typename T>
requires numeric<T>          // built-in concept
T addNew(T a, T b) { return a + b; }

// Or inline with 'auto' (cleaner syntax)
auto multiply(auto a, auto b) requires numeric<decltype(a)> {
    return a * b;
}

// Define your own concept
template <typename T>
concept Printable = requires(T t) {
    { cout << t };   // T must be printable with <<
};

template <Printable T>
void print(T value) { cout << value << endl; }

print(42);       // OK
print("hello");  // OK
// print(vector<int>{});  // ERROR: vector doesn't support << (clear message!)

// Built-in standard concepts (from <concepts>)
// integral<T>        — T is an integer type
// floating_point<T>  — T is float/double
// same_as<T, U>      — T and U are the same type
// convertible_to<T>  — can convert to T
// invocable<F, Args> — F is callable with Args
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
- **`constexpr`** — evaluate at compile time; zero runtime cost for constant inputs
- **`if constexpr`** (C++17) — compile-time branch selection in templates; unused branches aren't compiled
- **`std::variant<A,B,C>`** (C++17) — type-safe union; holds exactly one of the listed types
- **`std::any`** (C++17) — holds any type at runtime; use `variant` when types are known upfront
- **Concepts** (C++20) — constrain template parameters with readable requirements; gives clear error messages
