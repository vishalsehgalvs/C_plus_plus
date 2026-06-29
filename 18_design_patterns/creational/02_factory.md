# Factory Method Pattern

**Category:** Creational

---

## What Is It?

The **Factory Method** pattern defines an interface for creating an object, but lets **subclasses decide which class to instantiate**. The factory method defers object creation to subclasses.

> 🔁 **Analogy:** A bakery (the factory) makes bread. But _which_ bread — sourdough, whole wheat, rye — depends on which branch you're at. Each branch (subclass) decides what to bake. You just say "give me bread" without specifying how it's made.

---

## When to Use It?

- You want to create objects without knowing the exact class at compile time
- You want subclasses to control the object creation process
- You have a family of objects and you want to add new types without changing existing code

---

## Structure

```
┌─────────────────┐         ┌──────────────────┐
│    Creator      │         │    Product       │
│ (abstract)      │         │  (interface)     │
├─────────────────┤         ├──────────────────┤
│ +factoryMethod()│         │ +operation()     │
│   : Product*    │         └──────────────────┘
│ +someWork()     │                  △
└─────────────────┘                  │
        △                   ┌────────┴────────┐
        │                   │                 │
┌───────┴───────┐   creates  │ConcreteProductA│
│ConcreteCreatorA├──────────►│                │
└───────────────┘            └────────────────┘
┌───────────────┐
│ConcreteCreatorB├──────────►ConcreteProductB
└───────────────┘
```

---

## Basic Implementation

```cpp
#include <iostream>
#include <memory>
using namespace std;

// ---------- Product Interface ----------
class Animal {
public:
    virtual void speak() = 0;
    virtual string getName() = 0;
    virtual ~Animal() {}
};

// ---------- Concrete Products ----------
class Dog : public Animal {
public:
    void speak() override { cout << "Woof!" << endl; }
    string getName() override { return "Dog"; }
};

class Cat : public Animal {
public:
    void speak() override { cout << "Meow!" << endl; }
    string getName() override { return "Cat"; }
};

class Cow : public Animal {
public:
    void speak() override { cout << "Moo!" << endl; }
    string getName() override { return "Cow"; }
};

// ---------- Creator (Factory) ----------
class AnimalFactory {
public:
    // The factory method — returns a pointer to the right type
    static Animal* createAnimal(const string& type) {
        if (type == "dog") return new Dog();
        if (type == "cat") return new Cat();
        if (type == "cow") return new Cow();
        return nullptr;
    }
};

int main() {
    string types[] = {"dog", "cat", "cow"};

    for (const string& t : types) {
        Animal* a = AnimalFactory::createAnimal(t);
        if (a) {
            cout << a->getName() << " says: ";
            a->speak();
            delete a;
        }
    }

    return 0;
}
```

Output:

```
Dog says: Woof!
Cat says: Meow!
Cow says: Moo!
```

---

## Modern Version with `unique_ptr`

```cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Product interface
class Shape {
public:
    virtual void draw() = 0;
    virtual double area() = 0;
    virtual ~Shape() {}
};

// Concrete products
class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    void draw() override { cout << "Drawing circle (r=" << radius << ")" << endl; }
    double area() override { return 3.14159 * radius * radius; }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    void draw() override { cout << "Drawing rectangle (" << w << "x" << h << ")" << endl; }
    double area() override { return w * h; }
};

class Triangle : public Shape {
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    void draw() override { cout << "Drawing triangle" << endl; }
    double area() override { return 0.5 * base * height; }
};

// Factory — returns smart pointer (no manual delete needed)
unique_ptr<Shape> createShape(const string& type, double a, double b = 0) {
    if (type == "circle")    return make_unique<Circle>(a);
    if (type == "rectangle") return make_unique<Rectangle>(a, b);
    if (type == "triangle")  return make_unique<Triangle>(a, b);
    throw invalid_argument("Unknown shape: " + type);
}

int main() {
    auto c = createShape("circle", 5.0);
    auto r = createShape("rectangle", 4.0, 6.0);
    auto t = createShape("triangle", 3.0, 8.0);

    for (auto* shape : {c.get(), r.get(), t.get()}) {
        shape->draw();
        cout << "  Area: " << shape->area() << endl;
    }

    return 0;
}
```

---

## Real-World Example: UI Button Factory

```cpp
#include <iostream>
using namespace std;

// Product
class Button {
public:
    virtual void render() = 0;
    virtual void onClick() = 0;
    virtual ~Button() {}
};

// Concrete products
class WindowsButton : public Button {
public:
    void render() override { cout << "[ Windows Button ]" << endl; }
    void onClick() override { cout << "Windows click event" << endl; }
};

class MacButton : public Button {
public:
    void render() override { cout << "( Mac Button )" << endl; }
    void onClick() override { cout << "Mac click event" << endl; }
};

class LinuxButton : public Button {
public:
    void render() override { cout << "< Linux Button >" << endl; }
    void onClick() override { cout << "Linux click event" << endl; }
};

// Factory
class UIFactory {
public:
    static Button* createButton(const string& platform) {
        if (platform == "windows") return new WindowsButton();
        if (platform == "mac")     return new MacButton();
        if (platform == "linux")   return new LinuxButton();
        return nullptr;
    }
};

int main() {
    // In a real app, platform comes from runtime config
    string platform = "mac";

    Button* btn = UIFactory::createButton(platform);
    if (btn) {
        btn->render();
        btn->onClick();
        delete btn;
    }

    return 0;
}
```

---

## Factory Method Flowchart

```
Client calls createAnimal("dog")
            │
            ▼
    Factory Method
    (if/switch on type)
            │
    ┌───────┼───────┐
   "dog"  "cat"   "cow"
    │       │       │
    ▼       ▼       ▼
  new Dog  new Cat  new Cow
    │       │       │
    └───────┼───────┘
            │
            ▼
    Return Animal* pointer
    (client doesn't know which!)
```

---

## Pros and Cons

| ✅ Pros                                                              | ❌ Cons                                                       |
| -------------------------------------------------------------------- | ------------------------------------------------------------- |
| Open/Closed Principle — add new types without changing factory logic | Can result in a large if/switch (use registry pattern to fix) |
| Client is decoupled from concrete classes                            | More classes to manage                                        |
| Easy to swap implementations                                         | Slightly indirect code path                                   |

---

> 💡 **Next step:** If you have multiple related factories (e.g., Button AND Checkbox AND TextBox all for Windows/Mac), look at [Abstract Factory](03_abstract_factory.md).
