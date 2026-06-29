# C++ Inheritance and Polymorphism

> Source: https://www.programiz.com/cpp-programming/inheritance

---

## Inheritance

Inheritance lets a **derived class** inherit properties and methods from a **base class** (parent class). It models an "is-a" relationship.

> 🔁 **Analogy:** A `Dog` IS-A `Animal`. A `SavingsAccount` IS-A `BankAccount`. The derived class gets all the base class functionality, then adds or overrides its own.

```
      ┌──────────────────┐
      │     Animal       │  ← Base class
      │  + name          │
      │  + eat()         │
      │  + breathe()     │
      └──────────────────┘
              ▲
    ┌─────────┴──────────┐
    │                    │
┌───┴──────┐      ┌──────┴────┐
│   Dog    │      │   Cat     │  ← Derived classes
│ + bark() │      │ + meow()  │
└──────────┘      └───────────┘
```

---

## Syntax

```cpp
class Animal {
public:
    string name;
    int age;

    Animal(string n, int a) : name(n), age(a) {}

    void eat() {
        cout << name << " is eating." << endl;
    }

    void describe() {
        cout << name << " is " << age << " years old." << endl;
    }
};

// Dog inherits from Animal
class Dog : public Animal {
public:
    string breed;

    // Constructor calls base class constructor
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {}

    void bark() {
        cout << name << " says: Woof!" << endl;
    }
};

int main() {
    Dog d("Rex", 3, "Labrador");

    d.eat();      // inherited from Animal
    d.describe(); // inherited from Animal
    d.bark();     // Dog's own method

    return 0;
}
```

---

## Access Modifiers in Inheritance

| Member in Base | `public` inheritance | `protected` inheritance | `private` inheritance |
| -------------- | -------------------- | ----------------------- | --------------------- |
| `public`       | public               | protected               | private               |
| `protected`    | protected            | protected               | private               |
| `private`      | ❌ not inherited     | ❌ not inherited        | ❌ not inherited      |

> 💡 Use `public` inheritance most of the time — it means "Dog IS-A Animal". Use `protected` for "implementation detail" inheritance.

`protected` members: accessible within the class AND derived classes, but NOT from outside:

```cpp
class Animal {
protected:   // accessible in Dog but not from main()
    int heartRate;

public:
    Animal() : heartRate(70) {}
};

class Dog : public Animal {
public:
    void checkHealth() {
        cout << "Heart rate: " << heartRate;  // ✅ accessible
    }
};

// Dog d;
// d.heartRate;  // ❌ Error! protected, not accessible from main()
```

---

## Constructor Chain

When a derived object is created, the **base constructor runs first**:

```cpp
class Shape {
public:
    string color;
    Shape(string c) : color(c) {
        cout << "Shape constructor" << endl;
    }
};

class Circle : public Shape {
public:
    double radius;
    Circle(string c, double r) : Shape(c), radius(r) {
        cout << "Circle constructor" << endl;
    }
};

Circle c("Red", 5.0);
// Output:
// Shape constructor    ← base first
// Circle constructor   ← derived second
```

---

## Method Overriding

Derived class provides its **own version** of a base class method:

```cpp
class Animal {
public:
    virtual void makeSound() {  // virtual = can be overridden
        cout << "Some generic animal sound" << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {  // override keyword: clarity + compiler check
        cout << "Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "Meow!" << endl;
    }
};
```

---

## Polymorphism

**Polymorphism** = "many forms". The same function call behaves differently based on the actual object type at runtime.

```cpp
Animal *animals[3];
animals[0] = new Dog();
animals[1] = new Cat();
animals[2] = new Animal();

for (int i = 0; i < 3; i++) {
    animals[i]->makeSound();  // calls the right version each time!
}
// Output:
// Woof!
// Meow!
// Some generic animal sound
```

This is **runtime polymorphism** — the correct method is chosen while the program runs, not at compile time. It works because of **virtual functions**.

---

## Virtual Functions and vtable

When you mark a function `virtual`, C++ creates a **vtable** (virtual function table) — a lookup table of function pointers for each class:

```
vtable for Animal: { makeSound → Animal::makeSound }
vtable for Dog:    { makeSound → Dog::makeSound }
vtable for Cat:    { makeSound → Cat::makeSound }

When animals[0]->makeSound() is called:
  → check vtable for whatever type animals[0] actually is
  → it's a Dog → call Dog::makeSound()
```

> ⚠️ If you DON'T use `virtual`, method overriding won't work with base class pointers/references:

```cpp
// Without virtual — calls base class version!
Animal *a = new Dog();
a->makeSound();  // "Some generic animal sound" ← WRONG!

// With virtual — calls derived class version
// "Woof!" ← CORRECT
```

---

## Pure Virtual Functions and Abstract Classes

A **pure virtual function** has no implementation — it forces derived classes to provide one:

```cpp
class Shape {   // abstract class
public:
    virtual double area() = 0;       // pure virtual — must override
    virtual double perimeter() = 0;  // pure virtual

    void display() {  // not pure virtual — optional to override
        cout << "Area: " << area() << endl;
    }
};

// Can't create Shape directly:
// Shape s;  // ❌ Error!

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() override {
        return 3.14159 * radius * radius;
    }

    double perimeter() override {
        return 2 * 3.14159 * radius;
    }
};

class Rectangle : public Shape {
private:
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}

    double area() override { return w * h; }
    double perimeter() override { return 2 * (w + h); }
};

int main() {
    Shape *shapes[2];
    shapes[0] = new Circle(5);
    shapes[1] = new Rectangle(4, 6);

    for (int i = 0; i < 2; i++) {
        shapes[i]->display();
    }
}
```

---

## Virtual Destructor

When using polymorphism with base class pointers, always make the base destructor `virtual`:

```cpp
class Animal {
public:
    virtual ~Animal() {  // ← virtual destructor!
        cout << "Animal destroyed" << endl;
    }
};

class Dog : public Animal {
public:
    ~Dog() {
        cout << "Dog destroyed" << endl;
    }
};

Animal *a = new Dog();
delete a;
// Without virtual ~Animal: only "Animal destroyed" (memory leak!)
// With virtual ~Animal: both "Dog destroyed" then "Animal destroyed" ✅
```

---

## Multiple Inheritance

A class can inherit from **more than one base class**:

```cpp
class Flyable {
public:
    void fly() { cout << "Flying!" << endl; }
};

class Swimmable {
public:
    void swim() { cout << "Swimming!" << endl; }
};

// Duck can do both!
class Duck : public Flyable, public Swimmable {
public:
    void quack() { cout << "Quack!" << endl; }
};

Duck donald;
donald.fly();   // from Flyable
donald.swim();  // from Swimmable
donald.quack(); // Duck's own
```

---

## The Diamond Problem and Virtual Inheritance

Multiple inheritance can cause a problem when two base classes share a common ancestor:

```
        Animal
       /      \
    Flyable  Swimmable
       \      /
        Duck          ← which 'Animal' does Duck inherit? TWO copies?
```

```cpp
// Without virtual: Duck gets TWO copies of Animal — ambiguity!
class Animal { public: string name = "Animal"; };
class Flyable : public Animal {};
class Swimmable : public Animal {};
class Duck : public Flyable, public Swimmable {};

Duck d;
// d.name = "duck";       // ❌ ERROR: ambiguous! Which Animal::name?
// d.Animal::name;         // ❌ still ambiguous
d.Flyable::name = "duck"; // OK but ugly

// FIX: virtual inheritance — ensures only ONE copy of Animal
class Flyable    : public virtual Animal {};
class Swimmable  : public virtual Animal {};
class Duck       : public Flyable, public Swimmable {};

Duck d2;
d2.name = "duck";  // ✅ Now only ONE Animal — no ambiguity
```

> 💡 **In practice:** Multiple inheritance is often a design smell. Prefer composition or interfaces (abstract classes with only pure virtual methods) over deep multiple inheritance hierarchies.

---

## Method Hiding vs Overriding

These two look similar but behave very differently:

```cpp
class Base {
public:
    virtual void speak() { cout << "Base speaks" << endl; }   // virtual
    void run()           { cout << "Base runs" << endl; }     // NOT virtual
};

class Derived : public Base {
public:
    void speak() override { cout << "Derived speaks" << endl; } // OVERRIDING
    void run()            { cout << "Derived runs" << endl; }   // HIDING (dangerous!)
};

Base* ptr = new Derived();
ptr->speak();    // "Derived speaks"  ✅ virtual dispatch works
ptr->run();      // "Base runs"       ⚠️ hiding! pointer type decides, not object type

Derived* dptr = new Derived();
dptr->run();     // "Derived runs"    — now Derived version runs
```

```
Overriding (virtual):          Hiding (non-virtual):
  Pointer type = Base            Pointer type = Base
  Object type  = Derived         Object type  = Derived
  Result: Derived's method       Result: BASE's method  ⚠️
```

> ⚠️ Always use `virtual` + `override` when you intend polymorphism. Hiding non-virtual methods is almost always a bug waiting to happen.

---

## Key Takeaways

- Inheritance: `class Derived : public Base` — derived class gets all public/protected members
- `protected` members: accessible in derived classes but not from outside
- Base constructor always runs first; use initializer list to call it: `Derived(...) : Base(...)`
- `virtual` functions enable runtime polymorphism — correct version chosen at runtime
- Always use `override` keyword when overriding — helps catch typos
- Pure virtual functions (`= 0`) make a class abstract — can't instantiate it directly
- Abstract classes define interfaces that derived classes must implement
- Always use `virtual` destructor in base class when using polymorphism
- **Multiple inheritance**: allowed in C++, but use carefully — prefer simple hierarchies
- **Diamond problem**: use `virtual` inheritance to ensure only one copy of a shared ancestor
- **Method hiding** (non-virtual): base pointer calls base version even on derived object — usually a bug
