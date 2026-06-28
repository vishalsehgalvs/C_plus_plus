# C++ Templates

> Source: https://www.programiz.com/cpp-programming/templates

---

## What Are Templates?

Templates let you write **generic** code that works with any data type, without rewriting the same logic for each type.

> 🔁 **Analogy:** A template is like a cookie cutter. The cutter's shape works for any type of dough (chocolate, vanilla, gingerbread). You don't need a different cutter for each flavor — just different dough.

**Without templates — repetitive:**
```cpp
int addInt(int a, int b)       { return a + b; }
double addDouble(double a, double b) { return a + b; }
float addFloat(float a, float b)     { return a + b; }
// Same logic, 3 functions...
```

**With templates — one function:**
```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

cout << add(1, 2);         // int — 3
cout << add(1.5, 2.5);     // double — 4.0
cout << add(1.5f, 2.5f);   // float — 4.0
```

---

## Function Templates

```cpp
template <typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

cout << findMax(10, 20);        // 20 (int)
cout << findMax(3.14, 2.72);    // 3.14 (double)
cout << findMax('a', 'z');      // 'z' (char comparison)

// Two type parameters
template <typename T, typename U>
void displayPair(T first, U second) {
    cout << first << " and " << second << endl;
}

displayPair(42, "hello");       // int and string
displayPair(3.14, 100);         // double and int
```

---

## Class Templates

```cpp
template <typename T>
class Box {
private:
    T value;

public:
    Box(T v) : value(v) {}

    T getValue() {
        return value;
    }

    void setValue(T v) {
        value = v;
    }

    void display() {
        cout << "Box contains: " << value << endl;
    }
};

int main() {
    Box<int>    intBox(42);
    Box<string> strBox("Hello");
    Box<double> dblBox(3.14);

    intBox.display();   // Box contains: 42
    strBox.display();   // Box contains: Hello
    dblBox.display();   // Box contains: 3.14
}
```

### Template class with multiple types:

```cpp
template <typename K, typename V>
class Pair {
private:
    K key;
    V value;

public:
    Pair(K k, V v) : key(k), value(v) {}

    K getKey()   { return key; }
    V getValue() { return value; }

    void print() {
        cout << key << " -> " << value << endl;
    }
};

Pair<string, int>    p1("age", 25);
Pair<int, double>    p2(1, 3.14);
Pair<string, string> p3("city", "Seattle");

p1.print();  // age -> 25
p2.print();  // 1 -> 3.14
```

---

## Template Specialization

Provide a **specific implementation** for a particular type:

```cpp
// Generic template
template <typename T>
void print(T value) {
    cout << "Value: " << value << endl;
}

// Specialization for bool
template <>
void print<bool>(bool value) {
    cout << "Boolean: " << (value ? "true" : "false") << endl;
}

print(42);          // Value: 42
print(3.14);        // Value: 3.14
print(true);        // Boolean: true  ← uses specialization
```

---

## Default Template Parameters

```cpp
template <typename T = int, int Size = 10>
class Array {
private:
    T data[Size];

public:
    int size() { return Size; }
};

Array<> a1;           // Array<int, 10> — defaults
Array<double, 20> a2; // Array<double, 20>
Array<string, 5>  a3; // Array<string, 5>
```

---

## How Templates Work

Templates are a **compile-time** mechanism. The compiler generates separate code for each type you use:

```
add<int>    → compiler generates: int add(int a, int b) { return a + b; }
add<double> → compiler generates: double add(double a, double b) { return a + b; }
```

This is called **template instantiation**.

> ⚠️ If you use a template with a type that doesn't support the operations used inside (e.g., `a + b` where T doesn't have `+`), you'll get a compile-time error.

---

## STL Containers Are Templates

All of the Standard Template Library uses templates:

```cpp
vector<int>         v1;     // vector of ints
vector<string>      v2;     // vector of strings
vector<MyClass>     v3;     // vector of your own class!

map<string, int>    m1;     // map: string keys, int values
map<int, MyClass>   m2;     // map: int keys, MyClass values

pair<string, int>   p1;     // pair of string and int
```

---

## Key Takeaways

- Templates write code **once** that works for **any type**
- `template <typename T>` before a function or class = function/class template
- The compiler **generates** separate code for each type used (compile-time, not runtime)
- Use `template <>` to specialize for a specific type
- Default template parameters: `template <typename T = int>`
- All STL containers (`vector`, `map`, `set`) are template classes
- Templates are in header files (`.h`) because the compiler needs the full definition to instantiate
