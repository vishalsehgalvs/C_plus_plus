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

## Key Takeaways

- A **class** is a blueprint; an **object** is an instance of that blueprint
- `public` members are accessible from anywhere; `private` members only from within the class
- **Constructors** initialize objects automatically when created — same name as class, no return type
- **Destructors** clean up when objects are destroyed — prefix with `~`
- **Encapsulation**: keep data `private`, provide controlled `public` getters/setters
- `this` is a pointer to the current object — useful when parameter names clash with member names
- `static` members belong to the class, not individual objects — shared across all instances
