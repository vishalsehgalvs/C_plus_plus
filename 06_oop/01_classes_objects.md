# C++ Classes and Objects (OOP)

> Source: https://www.programiz.com/cpp-programming/object-class

---

## What Is OOP?

**Object-Oriented Programming** organizes code around **objects** — things that have data (properties) and behavior (methods).

> 🔁 **Analogy:** In the real world, a "Car" has properties (color, brand, speed) and behaviors (accelerate, brake, honk). OOP lets you model real-world things in code.

```
┌──────────────────────────────────────────┐
│  CLASS: Blueprint / Template             │
│  (like the architect's drawing)          │
└──────────────────────────────────────────┘
              │ create instances
              ▼
┌──────────────────────────────────────────┐
│  OBJECT: Actual thing in memory          │
│  myCar = new Car (the actual car)        │
└──────────────────────────────────────────┘
```

The four pillars of OOP:

- **Encapsulation** — hide data, expose only what's needed
- **Inheritance** — create new classes from existing ones
- **Polymorphism** — same interface, different behaviors
- **Abstraction** — hide complex implementation, show simple interface

---

## Defining a Class

```cpp
class ClassName {
public:     // access specifier
    // data members (properties)
    int age;
    string name;

    // member functions (methods)
    void greet() {
        cout << "Hi, I'm " << name << endl;
    }
};
```

### Access Specifiers

```
public:    ← anyone can access from outside
private:   ← only accessible within the class itself
protected: ← accessible within class and derived classes
```

---

## Creating Objects

```cpp
class Dog {
public:
    string name;
    string breed;
    int age;

    void bark() {
        cout << name << " says: Woof!" << endl;
    }

    void describe() {
        cout << name << " is a " << age << " year old " << breed << endl;
    }
};

int main() {
    Dog dog1;           // create an object
    dog1.name = "Rex";
    dog1.breed = "Labrador";
    dog1.age = 3;
    dog1.bark();        // Rex says: Woof!

    Dog dog2;           // another object
    dog2.name = "Buddy";
    dog2.breed = "Poodle";
    dog2.age = 2;
    dog2.describe();    // Buddy is a 2 year old Poodle

    return 0;
}
```

---

## Constructors

A **constructor** is a special function that runs automatically when an object is created. It initializes the object's data.

```cpp
class Car {
public:
    string brand;
    int year;
    double speed;

    // Default constructor
    Car() {
        brand = "Unknown";
        year = 2020;
        speed = 0.0;
    }

    // Parameterized constructor
    Car(string b, int y) {
        brand = b;
        year = y;
        speed = 0.0;
    }

    // Constructor with initializer list (preferred)
    Car(string b, int y, double s) : brand(b), year(y), speed(s) {}

    void display() {
        cout << year << " " << brand << " | Speed: " << speed << endl;
    }
};

int main() {
    Car c1;                       // uses default constructor
    Car c2("Toyota", 2022);       // parameterized
    Car c3("BMW", 2023, 200.0);   // all three

    c1.display();  // 2020 Unknown | Speed: 0
    c2.display();  // 2022 Toyota | Speed: 0
    c3.display();  // 2023 BMW | Speed: 200
}
```

---

## Destructors

A **destructor** runs automatically when an object is destroyed (goes out of scope or is deleted):

```cpp
class Logger {
public:
    string name;

    Logger(string n) : name(n) {
        cout << name << " created" << endl;
    }

    ~Logger() {  // destructor: ~ + class name, no params, no return
        cout << name << " destroyed" << endl;
    }
};

int main() {
    Logger a("A");   // prints: A created
    {
        Logger b("B");   // B created
    }                    // B destroyed (out of scope)
    // a destroyed when main() ends
}
```

---

## Encapsulation — Data Hiding

Keep data `private`, provide `public` getters and setters:

```cpp
class BankAccount {
private:
    string owner;
    double balance;

public:
    // Constructor
    BankAccount(string o, double b) : owner(o), balance(b) {}

    // Getter — read-only access
    double getBalance() const {
        return balance;
    }

    string getOwner() const {
        return owner;
    }

    // Methods that validate before modifying
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!" << endl;
            return;
        }
        balance += amount;
        cout << "Deposited: $" << amount << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return;
        }
        balance -= amount;
        cout << "Withdrew: $" << amount << endl;
    }
};

int main() {
    BankAccount acc("Alice", 1000.0);

    acc.deposit(500);
    acc.withdraw(200);
    cout << "Balance: $" << acc.getBalance() << endl;

    // acc.balance = -99999;  // ❌ Error! balance is private
}
```

---

## The `this` Pointer

Inside any member function, `this` is a pointer to the current object:

```cpp
class Rectangle {
private:
    double width, height;

public:
    void setWidth(double width) {
        this->width = width;   // this->width = member, width = parameter
    }

    void setHeight(double height) {
        this->height = height;
    }

    double area() {
        return this->width * this->height;
    }

    // Method chaining with this
    Rectangle& setDimensions(double w, double h) {
        this->width = w;
        this->height = h;
        return *this;  // return reference to self for chaining
    }
};
```

---

## Static Members

`static` members belong to the **class itself**, not individual objects — shared across all instances:

```cpp
class Counter {
private:
    static int count;  // shared by all objects
    int id;

public:
    Counter() {
        count++;
        id = count;
    }

    static int getCount() {  // static method
        return count;
    }

    int getId() { return id; }
};

// Initialize static member outside class
int Counter::count = 0;

int main() {
    Counter c1, c2, c3;
    cout << Counter::getCount() << endl;  // 3
    cout << c1.getId() << endl;           // 1
    cout << c2.getId() << endl;           // 2
}
```

---

## Class Diagram

```
┌──────────────────────────────┐
│         BankAccount          │
├──────────────────────────────┤
│ - owner: string   (private)  │
│ - balance: double (private)  │
├──────────────────────────────┤
│ + BankAccount(string, double)│
│ + getBalance(): double       │
│ + deposit(double): void      │
│ + withdraw(double): void     │
└──────────────────────────────┘
```

---

## Copy Constructor and Copy Assignment

When you assign one object to another, C++ needs to know **how** to copy it. By default it does a shallow (memberwise) copy — which breaks if your class owns heap memory:

```
Shallow copy problem:
  obj1  ──→  [heap data]  ←──  obj2
  Both point to SAME memory.
  When obj1 destroys it, obj2 has a dangling pointer! 💥

Deep copy (correct):
  obj1  ──→  [heap data]
  obj2  ──→  [copy of heap data]   ← separate allocation
```

```cpp
class Buffer {
    int*   data;
    size_t size;
public:
    Buffer(size_t s) : size(s), data(new int[s]) {
        cout << "Constructed" << endl;
    }

    // Copy constructor — called when: Buffer b2 = b1;  or  Buffer b2(b1);
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        copy(other.data, other.data + size, data);   // deep copy!
        cout << "Copied" << endl;
    }

    // Copy assignment — called when: b2 = b1;  (b2 already exists)
    Buffer& operator=(const Buffer& other) {
        if (this == &other) return *this;   // guard: b = b; case
        delete[] data;                       // free old data
        size = other.size;
        data = new int[size];
        copy(other.data, other.data + size, data);
        cout << "Copy assigned" << endl;
        return *this;
    }

    ~Buffer() { delete[] data; cout << "Destroyed" << endl; }
};
```

---

## Move Constructor and Move Assignment

Copying is expensive when dealing with large data. **Move semantics** (C++11) let you _steal_ resources from temporaries instead of copying:

```cpp
class Buffer {
    // ... (same as above, plus:)

    // Move constructor — called when object is a temporary/rvalue
    Buffer(Buffer&& other) noexcept
        : size(other.size), data(other.data) {
        other.data = nullptr;   // leave 'other' in empty valid state
        other.size = 0;
        cout << "Moved" << endl;
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        data = other.data;
        other.data = nullptr;
        other.size = 0;
        cout << "Move assigned" << endl;
        return *this;
    }
};

// Usage
Buffer a(100);
Buffer b = move(a);           // move constructor — no copy!
vector<Buffer> v;
v.push_back(Buffer(50));      // move from temporary
```

### Rule of 0 / 3 / 5

| Rule          | When to use                                               | Special members needed                          |
| ------------- | --------------------------------------------------------- | ----------------------------------------------- |
| **Rule of 0** | Class uses only smart pointers/containers (no raw memory) | Don't write any — compiler handles it           |
| **Rule of 3** | Class manually manages resources (raw `new`/`delete`)     | destructor + copy constructor + copy assignment |
| **Rule of 5** | Same as Rule of 3 + want move performance                 | All 5: + move constructor + move assignment     |

> 💡 **Best advice:** Design classes to follow **Rule of 0** — use `unique_ptr`/`vector` etc. so you never need to write any of these manually.

---

## Operator Overloading

You can teach C++ how to use `+`, `-`, `<<`, `==` etc. with your own types:

```cpp
class Vector2D {
public:
    double x, y;
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // Arithmetic: v1 + v2
    Vector2D operator+(const Vector2D& other) const {
        return {x + other.x, y + other.y};
    }

    // Arithmetic: v1 - v2
    Vector2D operator-(const Vector2D& other) const {
        return {x - other.x, y - other.y};
    }

    // Scalar multiply: v * 3.0
    Vector2D operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

    // Equality: v1 == v2
    bool operator==(const Vector2D& other) const {
        return x == other.x && y == other.y;
    }

    // Compound assignment: v1 += v2
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x; y += other.y; return *this;
    }

    // Stream output: cout << v
    // (defined as free function below — needs access to x and y)
    friend ostream& operator<<(ostream& os, const Vector2D& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};

// Usage
Vector2D a(1, 2), b(3, 4);
Vector2D c = a + b;           // (4, 6)
Vector2D d = c * 2.0;         // (8, 12)
cout << d << endl;            // (8, 12)
cout << (a == b) << endl;     // false
```

> ⚠️ **Don't overload everything.** Only overload operators when the meaning is natural and obvious. Overloading `+` for a money class makes sense. Overloading `*` for a person class does not.

---

## Const Member Functions

A `const` member function promises not to modify the object. It can be called on `const` objects:

```cpp
class Temperature {
    double celsius;
public:
    Temperature(double c) : celsius(c) {}

    double getCelsius() const {          // const: won't modify anything
        return celsius;
    }
    double getFahrenheit() const {       // const: safe to call on const object
        return celsius * 9.0/5.0 + 32;
    }
    void setCelsius(double c) {          // NOT const: modifies the object
        celsius = c;
    }
};

const Temperature freezing(0.0);
cout << freezing.getCelsius();    // OK — const function on const object
// freezing.setCelsius(100);      // ERROR — can't call non-const on const object
```

> 💡 **Habit:** Mark every getter/read-only method as `const`. The compiler will catch accidental modifications.

---

## Friend Functions and Friend Classes

Sometimes an outside function needs access to private members. `friend` grants it:

```cpp
class BankAccount {
    double balance;     // private
public:
    BankAccount(double b) : balance(b) {}

    // Transfer needs to access private balance of BOTH accounts
    friend void transfer(BankAccount& from, BankAccount& to, double amount);
};

// This free function can access private 'balance'
void transfer(BankAccount& from, BankAccount& to, double amount) {
    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance   += amount;
    }
}

BankAccount alice(1000), bob(500);
transfer(alice, bob, 200);
// alice.balance = 800, bob.balance = 700
```

> ⚠️ **Use sparingly.** `friend` breaks encapsulation. Prefer designing your API so it isn't needed.

---

## Key Takeaways

- A **class** is a blueprint; an **object** is an instance of that blueprint
- `public` members are accessible from anywhere; `private` members only from within the class
- **Constructors** initialize objects automatically when created — same name as class, no return type
- **Destructors** clean up when objects are destroyed — prefix with `~`
- **Encapsulation**: keep data `private`, provide controlled `public` getters/setters
- `this` is a pointer to the current object — useful when parameter names clash with member names
- `static` members belong to the class, not individual objects — shared across all instances
- **Rule of 0**: let smart pointers/containers handle memory — don't write copy/move/destructor manually
- **Rule of 3/5**: if you write a destructor (raw memory), also write copy and move operations
- **Operator overloading**: teach C++ how to use `+`, `==`, `<<` etc. with your types — only when it's natural
- **`const` member functions**: mark read-only methods as `const` — can be called on const objects
- **`friend`**: grants outside access to private members — use sparingly
