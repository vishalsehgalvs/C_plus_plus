# Decorator Pattern

**Category:** Structural

---

## What Is It?

The **Decorator** pattern attaches additional responsibilities to an object **dynamically** at runtime — without modifying the original class or using subclassing.

> 🔁 **Analogy:** A plain coffee. You start with a black coffee and then add extras: + milk, + sugar, + vanilla syrup. Each "add" is a decorator that wraps the coffee and adds to it. You can layer them in any order, and each combination is valid.

---

## When to Use It?

- You want to add features to individual objects, not to the whole class
- You need combinations of features at runtime (not fixed at compile-time)
- Subclassing would lead to an explosion of classes for every combination

---

## The Problem Without Decorator

```
Without Decorator (subclass explosion):
Coffee
├── MilkCoffee
├── SugarCoffee
├── VanillaCoffee
├── MilkSugarCoffee
├── MilkVanillaCoffee
├── SugarVanillaCoffee
└── MilkSugarVanillaCoffee   ← 7 classes for 3 additions!
With n toppings → 2^n classes needed  (scales terribly!)
```

---

## Structure

```
┌────────────────┐
│   Component    │  ← base interface
│ +operation()   │
└────────────────┘
        △
   ┌────┴─────┐
   │          │
Concrete    Decorator (wraps a Component)
Component   ├── has a Component* inside
            └── +operation() → calls wrapped->operation() + adds something

            ConcreteDecoratorA extends Decorator
            ConcreteDecoratorB extends Decorator
```

---

## C++ Implementation: Coffee Shop

```cpp
#include <iostream>
#include <string>
using namespace std;

// ============ Component Interface ============
class Coffee {
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;
    virtual ~Coffee() {}
};

// ============ Concrete Component ============
class SimpleCoffee : public Coffee {
public:
    string getDescription() override { return "Simple coffee"; }
    double getCost() override { return 1.00; }
};

// ============ Decorator Base ============
class CoffeeDecorator : public Coffee {
protected:
    Coffee* wrappedCoffee;   // the coffee we're decorating

public:
    CoffeeDecorator(Coffee* c) : wrappedCoffee(c) {}
    virtual ~CoffeeDecorator() {}
};

// ============ Concrete Decorators ============
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(Coffee* c) : CoffeeDecorator(c) {}

    string getDescription() override {
        return wrappedCoffee->getDescription() + ", Milk";
    }
    double getCost() override {
        return wrappedCoffee->getCost() + 0.25;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(Coffee* c) : CoffeeDecorator(c) {}

    string getDescription() override {
        return wrappedCoffee->getDescription() + ", Sugar";
    }
    double getCost() override {
        return wrappedCoffee->getCost() + 0.10;
    }
};

class VanillaDecorator : public CoffeeDecorator {
public:
    VanillaDecorator(Coffee* c) : CoffeeDecorator(c) {}

    string getDescription() override {
        return wrappedCoffee->getDescription() + ", Vanilla";
    }
    double getCost() override {
        return wrappedCoffee->getCost() + 0.50;
    }
};

// ============ Main ============
int main() {
    // Plain coffee
    Coffee* coffee = new SimpleCoffee();
    cout << coffee->getDescription() << " → $" << coffee->getCost() << endl;

    // Add milk
    coffee = new MilkDecorator(coffee);
    cout << coffee->getDescription() << " → $" << coffee->getCost() << endl;

    // Add sugar on top
    coffee = new SugarDecorator(coffee);
    cout << coffee->getDescription() << " → $" << coffee->getCost() << endl;

    // Add vanilla on top of that
    coffee = new VanillaDecorator(coffee);
    cout << coffee->getDescription() << " → $" << coffee->getCost() << endl;

    delete coffee;   // Note: need careful deletion for nested decorators
    return 0;
}
```

Output:

```
Simple coffee → $1
Simple coffee, Milk → $1.25
Simple coffee, Milk, Sugar → $1.35
Simple coffee, Milk, Sugar, Vanilla → $1.85
```

---

## How Wrapping Works (Onion Layers)

```
getDescription() call travels INWARD, then the result travels OUTWARD:

VanillaDecorator
  └──► SugarDecorator
         └──► MilkDecorator
                └──► SimpleCoffee
                       └── "Simple coffee"
                MilkDecorator adds ", Milk"  → "Simple coffee, Milk"
         SugarDecorator adds ", Sugar"       → "Simple coffee, Milk, Sugar"
VanillaDecorator adds ", Vanilla"            → "Simple coffee, Milk, Sugar, Vanilla"
```

---

## Real-World Example: Text Formatter

```cpp
#include <iostream>
#include <string>
using namespace std;

class TextComponent {
public:
    virtual string render(const string& text) = 0;
    virtual ~TextComponent() {}
};

class PlainText : public TextComponent {
public:
    string render(const string& text) override { return text; }
};

class BoldDecorator : public TextComponent {
    TextComponent* component;
public:
    BoldDecorator(TextComponent* c) : component(c) {}
    string render(const string& text) override {
        return "<b>" + component->render(text) + "</b>";
    }
};

class ItalicDecorator : public TextComponent {
    TextComponent* component;
public:
    ItalicDecorator(TextComponent* c) : component(c) {}
    string render(const string& text) override {
        return "<i>" + component->render(text) + "</i>";
    }
};

class UnderlineDecorator : public TextComponent {
    TextComponent* component;
public:
    UnderlineDecorator(TextComponent* c) : component(c) {}
    string render(const string& text) override {
        return "<u>" + component->render(text) + "</u>";
    }
};

int main() {
    TextComponent* t = new PlainText();
    t = new BoldDecorator(t);
    t = new ItalicDecorator(t);
    t = new UnderlineDecorator(t);

    cout << t->render("Hello World") << endl;
    // Output: <u><i><b>Hello World</b></i></u>

    delete t;
}
```

---

## Pros and Cons

| ✅ Pros                          | ❌ Cons                                 |
| -------------------------------- | --------------------------------------- |
| Add responsibilities dynamically | Many small wrapper objects              |
| More flexible than subclassing   | Order of decoration matters             |
| Follows Open/Closed Principle    | Debugging through many layers is tricky |
| Combine features in any order    |                                         |

---

> 💡 **Used heavily in:** Java I/O streams (`BufferedReader(new FileReader(...))`), Python decorators (`@login_required`), C++ logging wrappers.
