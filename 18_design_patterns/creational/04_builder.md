# Builder Pattern

**Category:** Creational

---

## What Is It?

The **Builder** pattern constructs a complex object **step by step**. The same construction process can produce different representations.

> 🔁 **Analogy:** Building a custom sandwich at Subway. You choose bread → meat → cheese → veggies → sauce — one step at a time. The sandwich shop (Director) follows the same steps, but depending on your choices, the end result is different. You don't get a half-made sandwich handed to you until you say "done".

---

## When to Use It?

- An object has **many optional parameters** (constructor would be a mess)
- You need to build the same type of object in multiple ways
- You want to construct objects step by step and only assemble them at the end

---

## The Problem Without Builder (Constructor Hell)

```cpp
// UGLY: Too many parameters, easy to mix them up
Pizza p("large", "thin", true, false, true, false, "extra", 2, "mozzarella", false);
//       ^size    ^crust  ^cheese ^pepperoni ^mushrooms ...

// What does 'false' mean? Which parameter is which?
```

---

## Structure

```
┌────────────┐         ┌─────────────────┐
│  Director  │ ──uses──►    Builder      │
│            │         │  (interface)    │
│ +construct()│         ├─────────────────┤
└────────────┘         │ +buildPartA()   │
                        │ +buildPartB()   │
                        │ +getResult()    │
                        └─────────────────┘
                                △
                    ┌───────────┴───────────┐
             ConcreteBuilder1         ConcreteBuilder2
                    │                        │
                    ▼                        ▼
               Product1                 Product2
```

---

## C++ Implementation

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ============ Product ============
class Pizza {
public:
    string size;
    string crust;
    string sauce;
    string cheese;
    vector<string> toppings;

    void display() const {
        cout << "=== Pizza ===" << endl;
        cout << "Size:     " << size << endl;
        cout << "Crust:    " << crust << endl;
        cout << "Sauce:    " << sauce << endl;
        cout << "Cheese:   " << cheese << endl;
        cout << "Toppings: ";
        for (const auto& t : toppings) cout << t << " ";
        cout << endl;
    }
};

// ============ Builder Interface ============
class PizzaBuilder {
protected:
    Pizza pizza;

public:
    virtual void setSize()     = 0;
    virtual void setCrust()    = 0;
    virtual void setSauce()    = 0;
    virtual void setCheese()   = 0;
    virtual void addToppings() = 0;

    Pizza getResult() { return pizza; }
    virtual ~PizzaBuilder() {}
};

// ============ Concrete Builders ============
class MargheritaBuilder : public PizzaBuilder {
public:
    void setSize()     override { pizza.size   = "Medium"; }
    void setCrust()    override { pizza.crust  = "Thin";   }
    void setSauce()    override { pizza.sauce  = "Tomato"; }
    void setCheese()   override { pizza.cheese = "Mozzarella"; }
    void addToppings() override { pizza.toppings = {"Basil", "Olive Oil"}; }
};

class BBQChickenBuilder : public PizzaBuilder {
public:
    void setSize()     override { pizza.size   = "Large"; }
    void setCrust()    override { pizza.crust  = "Thick"; }
    void setSauce()    override { pizza.sauce  = "BBQ";   }
    void setCheese()   override { pizza.cheese = "Cheddar + Mozzarella"; }
    void addToppings() override { pizza.toppings = {"Chicken", "Onions", "Peppers"}; }
};

// ============ Director ============
class PizzaShop {
public:
    Pizza makePizza(PizzaBuilder& builder) {
        builder.setSize();
        builder.setCrust();
        builder.setSauce();
        builder.setCheese();
        builder.addToppings();
        return builder.getResult();
    }
};

// ============ Main ============
int main() {
    PizzaShop shop;

    MargheritaBuilder margBuilder;
    Pizza margherita = shop.makePizza(margBuilder);
    margherita.display();

    cout << endl;

    BBQChickenBuilder bbqBuilder;
    Pizza bbq = shop.makePizza(bbqBuilder);
    bbq.display();

    return 0;
}
```

Output:

```
=== Pizza ===
Size:     Medium
Crust:    Thin
Sauce:    Tomato
Cheese:   Mozzarella
Toppings: Basil Olive Oil

=== Pizza ===
Size:     Large
Crust:    Thick
Sauce:    BBQ
Cheese:   Cheddar + Mozzarella
Toppings: Chicken Onions Peppers
```

---

## Fluent Builder (Method Chaining) — Modern Style

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Computer {
public:
    string cpu, ram, storage, gpu, os;
    bool wifi, bluetooth;

    void display() const {
        cout << "CPU: " << cpu << " | RAM: " << ram
             << " | Storage: " << storage << " | GPU: " << gpu
             << " | OS: " << os
             << " | WiFi: " << (wifi ? "Yes" : "No")
             << " | BT: " << (bluetooth ? "Yes" : "No") << endl;
    }
};

class ComputerBuilder {
    Computer computer;

public:
    ComputerBuilder& setCPU(string cpu) {
        computer.cpu = cpu;
        return *this;   // return *this enables chaining
    }
    ComputerBuilder& setRAM(string ram) {
        computer.ram = ram;
        return *this;
    }
    ComputerBuilder& setStorage(string s) {
        computer.storage = s;
        return *this;
    }
    ComputerBuilder& setGPU(string gpu) {
        computer.gpu = gpu;
        return *this;
    }
    ComputerBuilder& setOS(string os) {
        computer.os = os;
        return *this;
    }
    ComputerBuilder& setWifi(bool w) {
        computer.wifi = w;
        return *this;
    }
    ComputerBuilder& setBluetooth(bool b) {
        computer.bluetooth = b;
        return *this;
    }

    Computer build() {
        return computer;
    }
};

int main() {
    // Clean, readable chained calls
    Computer gamingPC = ComputerBuilder()
        .setCPU("Intel i9-13900K")
        .setRAM("64GB DDR5")
        .setStorage("2TB NVMe SSD")
        .setGPU("RTX 4090")
        .setOS("Windows 11")
        .setWifi(true)
        .setBluetooth(true)
        .build();

    Computer officePC = ComputerBuilder()
        .setCPU("Intel i5-12400")
        .setRAM("16GB DDR4")
        .setStorage("512GB SSD")
        .setGPU("Integrated")
        .setOS("Windows 11")
        .setWifi(true)
        .setBluetooth(false)
        .build();

    cout << "Gaming PC: ";  gamingPC.display();
    cout << "Office PC: ";  officePC.display();

    return 0;
}
```

---

## Build Step Flowchart

```
Client
  │
  ▼
Create Builder
  │
  ├── setSize()     ←─ Step 1
  ├── setCrust()    ←─ Step 2
  ├── setSauce()    ←─ Step 3
  ├── setCheese()   ←─ Step 4
  └── addToppings() ←─ Step 5
          │
          ▼
       build() / getResult()
          │
          ▼
       Finished Product ✓
```

---

## Pros and Cons

| ✅ Pros                                 | ❌ Cons                                              |
| --------------------------------------- | ---------------------------------------------------- |
| Readable code — clear what each part is | More classes (Builder interface + concrete builders) |
| Optional parameters handled cleanly     | Overkill for simple objects                          |
| Same build process → different products | Object can be in incomplete state if steps skipped   |
| Fluent API is self-documenting          |                                                      |

---

> 💡 **Fluent builder** (method chaining) is extremely popular in modern C++ and Java. You see it in test frameworks, HTTP clients, query builders, etc.
