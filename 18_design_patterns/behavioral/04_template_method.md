# Template Method Pattern

**Category:** Behavioral

---

## What Is It?

The **Template Method** pattern defines the **skeleton of an algorithm** in a base class method, but lets subclasses override specific steps without changing the overall structure.

> 🔁 **Analogy:** Making tea vs coffee. The process is: boil water → brew → pour → add condiments. Both follow this same skeleton, but "brew" means steep tea leaves vs drip coffee, and "add condiments" means lemon for tea vs milk and sugar for coffee. The structure (template) is the same; the details differ.

---

## When to Use It?

- Multiple classes share the same algorithm structure but differ in some steps
- You want to control which parts of an algorithm subclasses can change
- You're building a framework where users fill in the blanks

---

## Structure

```
AbstractClass
│ +templateMethod()    ← fixed order, calls primitiveOps
│   step1()            ← concrete (fixed)
│   primitiveOp1()     ← abstract (subclasses override)
│   step2()            ← concrete (fixed)
│   primitiveOp2()     ← abstract (subclasses override)
│   hook()             ← optional hook (default: do nothing)
│
└──── ConcreteClassA     ConcreteClassB
      overrides:         overrides:
      primitiveOp1()     primitiveOp1()
      primitiveOp2()     primitiveOp2()
```

---

## C++ Implementation: Hot Beverages

```cpp
#include <iostream>
using namespace std;

// ============ Abstract Class with Template Method ============
class HotBeverage {
public:
    // Template method — defines the algorithm skeleton (final — don't override this)
    void prepare() {
        boilWater();
        brew();              // abstract — subclass fills in
        pourInCup();
        if (customerWantsCondiments()) {   // hook — optional
            addCondiments();   // abstract — subclass fills in
        }
        cout << "Enjoy your " << getBeverageName() << "!" << endl;
    }

protected:
    // Fixed steps — same for all beverages
    void boilWater()  { cout << "Boiling water..." << endl; }
    void pourInCup()  { cout << "Pouring into cup..." << endl; }

    // Abstract steps — MUST be implemented by subclasses
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
    virtual string getBeverageName() = 0;

    // Hook — optional override, default returns true
    virtual bool customerWantsCondiments() { return true; }

    virtual ~HotBeverage() {}
};

// ============ Concrete Classes ============
class Tea : public HotBeverage {
protected:
    void brew()            override { cout << "Steeping the tea..." << endl; }
    void addCondiments()   override { cout << "Adding lemon..." << endl; }
    string getBeverageName() override { return "tea"; }
};

class Coffee : public HotBeverage {
    bool withCondiments;
public:
    Coffee(bool withCond = true) : withCondiments(withCond) {}
protected:
    void brew()            override { cout << "Dripping coffee through filter..." << endl; }
    void addCondiments()   override { cout << "Adding milk and sugar..." << endl; }
    string getBeverageName() override { return "coffee"; }
    bool customerWantsCondiments() override { return withCondiments; }  // hook override
};

class HotChocolate : public HotBeverage {
protected:
    void brew()            override { cout << "Mixing cocoa powder with hot water..." << endl; }
    void addCondiments()   override { cout << "Adding whipped cream..." << endl; }
    string getBeverageName() override { return "hot chocolate"; }
};

int main() {
    cout << "=== Making Tea ===" << endl;
    Tea tea;
    tea.prepare();

    cout << "\n=== Making Coffee (with milk) ===" << endl;
    Coffee coffeeWithMilk(true);
    coffeeWithMilk.prepare();

    cout << "\n=== Making Black Coffee (no condiments) ===" << endl;
    Coffee blackCoffee(false);
    blackCoffee.prepare();

    cout << "\n=== Making Hot Chocolate ===" << endl;
    HotChocolate choc;
    choc.prepare();

    return 0;
}
```

Output:

```
=== Making Tea ===
Boiling water...
Steeping the tea...
Pouring into cup...
Adding lemon...
Enjoy your tea!

=== Making Coffee (with milk) ===
Boiling water...
Dripping coffee through filter...
Pouring into cup...
Adding milk and sugar...
Enjoy your coffee!

=== Making Black Coffee (no condiments) ===
Boiling water...
Dripping coffee through filter...
Pouring into cup...
Enjoy your coffee!

=== Making Hot Chocolate ===
Boiling water...
Mixing cocoa powder with hot water...
Pouring into cup...
Adding whipped cream...
Enjoy your hot chocolate!
```

---

## Real-World Example: Data Parser

```cpp
class DataParser {
public:
    // Template method — same steps for all parsers
    void parseFile(const string& filename) {
        openFile(filename);
        while (!isEndOfFile()) {
            string line = readLine();
            processLine(line);   // subclass decides how to process
        }
        closeFile();
        onParsed();   // hook
    }

protected:
    virtual void openFile(const string& f) { cout << "Opening: " << f << endl; }
    virtual bool isEndOfFile()             { return true; }  // simplified
    virtual string readLine()              { return ""; }
    virtual void processLine(const string& line) = 0;  // abstract
    virtual void closeFile()               { cout << "Closing file." << endl; }
    virtual void onParsed()                {}  // optional hook

    virtual ~DataParser() {}
};

class CSVParser : public DataParser {
protected:
    void processLine(const string& line) override {
        cout << "[CSV] Parsing row: " << line << endl;
        // split by comma...
    }
};

class JSONParser : public DataParser {
protected:
    void processLine(const string& line) override {
        cout << "[JSON] Parsing: " << line << endl;
        // parse JSON token...
    }
    void onParsed() override {
        cout << "[JSON] Post-processing: validating schema" << endl;
    }
};
```

---

## Template Method vs Strategy

```
Template Method:                Strategy:
────────────────────────        ──────────────────────────────
Algorithm skeleton in base      Algorithm fully encapsulated in
class, subclasses fill in       separate strategy object
specific steps
                                Algorithm swapped at runtime
Uses inheritance                Uses composition

Steps fixed, behavior varies    Whole algorithm is interchangeable
in specific steps
```

---

## Pros and Cons

| ✅ Pros                                                       | ❌ Cons                                                |
| ------------------------------------------------------------- | ------------------------------------------------------ |
| Reuse the common algorithm structure                          | Client must subclass — can't just plug in an object    |
| Subclasses override only what they need                       | Hard to maintain if template method gets complex       |
| Hooks give optional extension points                          | Violates Liskov if subclasses change behavior too much |
| Follows Hollywood Principle ("don't call us, we'll call you") |                                                        |

---

> 💡 **Used in:** Java's `HttpServlet` (override `doGet`/`doPost`), `Collections.sort()`, game AI step patterns, test framework setup/teardown (`setUp`, `tearDown`).
