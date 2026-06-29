# Prototype Pattern

**Category:** Creational

---

## What Is It?

The **Prototype** pattern creates new objects by **cloning (copying) an existing object** rather than creating from scratch.

> 🔁 **Analogy:** Photocopying a document. Instead of writing a new document from scratch, you copy an existing one and then edit the copy. The original stays unchanged.

---

## When to Use It?

- Object creation is expensive (database call, file read, heavy computation)
- You want to create many similar objects with slight variations
- You need to copy objects whose types you don't know at compile time

---

## Structure

```
┌──────────────────────┐
│    Prototype         │  ← interface with clone()
├──────────────────────┤
│ +clone(): Prototype* │
└──────────────────────┘
           △
    ┌──────┴───────┐
    │              │
ConcreteA      ConcreteB
│+clone()       │+clone()
│  return new   │  return new
│  ConcreteA(*this) ConcreteB(*this)
│              │
└──────────────┘
Client calls clone() on existing object → gets a copy
```

---

## C++ Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// ============ Prototype Interface ============
class Shape {
public:
    string color;
    int    x, y;

    Shape(string c, int x, int y) : color(c), x(x), y(y) {}
    virtual Shape* clone() = 0;         // the key method
    virtual void draw() = 0;
    virtual ~Shape() {}
};

// ============ Concrete Prototypes ============
class Circle : public Shape {
public:
    double radius;

    Circle(string color, int x, int y, double r)
        : Shape(color, x, y), radius(r) {}

    // Clone using copy constructor
    Shape* clone() override {
        return new Circle(*this);   // copy this object
    }

    void draw() override {
        cout << "Circle [" << color << "] at (" << x << "," << y
             << ") r=" << radius << endl;
    }
};

class Rectangle : public Shape {
public:
    double width, height;

    Rectangle(string color, int x, int y, double w, double h)
        : Shape(color, x, y), width(w), height(h) {}

    Shape* clone() override {
        return new Rectangle(*this);
    }

    void draw() override {
        cout << "Rect [" << color << "] at (" << x << "," << y
             << ") " << width << "x" << height << endl;
    }
};

int main() {
    // Original objects
    Circle* originalCircle = new Circle("red", 0, 0, 5.0);
    Rectangle* originalRect = new Rectangle("blue", 10, 10, 8.0, 4.0);

    // Clone them — no need to know the exact type!
    Shape* clonedCircle = originalCircle->clone();
    Shape* clonedRect   = originalRect->clone();

    // Modify clones
    clonedCircle->color = "green";
    clonedCircle->x     = 50;

    // Draw all
    cout << "Originals:" << endl;
    originalCircle->draw();
    originalRect->draw();

    cout << "\nClones (modified):" << endl;
    clonedCircle->draw();   // green, x=50
    clonedRect->draw();     // unchanged copy

    delete originalCircle;
    delete originalRect;
    delete clonedCircle;
    delete clonedRect;

    return 0;
}
```

Output:

```
Originals:
Circle [red] at (0,0) r=5
Rect [blue] at (10,10) 8x4

Clones (modified):
Circle [green] at (50,0) r=5
Rect [blue] at (10,10) 8x4
```

---

## Prototype Registry (Object Cache)

A **prototype registry** stores ready-to-clone objects:

```cpp
#include <iostream>
#include <map>
#include <string>
#include <memory>
using namespace std;

class Document {
public:
    string title, content, template_name;
    int pageCount;

    Document(string t, string c, string tmpl, int pages)
        : title(t), content(c), template_name(tmpl), pageCount(pages) {}

    // Deep copy via clone
    Document* clone() const {
        return new Document(*this);
    }

    void display() const {
        cout << "Title: " << title << " | Template: " << template_name
             << " | Pages: " << pageCount << endl;
    }
};

// Registry of template documents
class DocumentRegistry {
    map<string, Document*> prototypes;

public:
    void registerTemplate(const string& name, Document* doc) {
        prototypes[name] = doc;
    }

    Document* createFromTemplate(const string& name) {
        if (prototypes.count(name)) {
            return prototypes[name]->clone();   // clone the template
        }
        return nullptr;
    }

    ~DocumentRegistry() {
        for (auto& [name, doc] : prototypes) delete doc;
    }
};

int main() {
    DocumentRegistry registry;

    // Register templates (expensive to create normally)
    registry.registerTemplate("invoice",
        new Document("Invoice Template", "[items go here]", "Invoice", 2));
    registry.registerTemplate("report",
        new Document("Report Template", "[data goes here]", "Report", 10));

    // Create copies from templates — fast!
    Document* inv1 = registry.createFromTemplate("invoice");
    Document* inv2 = registry.createFromTemplate("invoice");

    // Customize each copy
    inv1->title = "Invoice #001";
    inv2->title = "Invoice #002";

    inv1->display();
    inv2->display();

    delete inv1;
    delete inv2;

    return 0;
}
```

---

## Shallow Copy vs Deep Copy

> ⚠️ This is the most important detail with Prototype!

```
SHALLOW COPY (default copy constructor):
Original ─► [name="Alice"] [data*──────►[1,2,3,4,5]]
Clone    ─► [name="Alice"] [data*──────►[1,2,3,4,5]]
                                              ↑
                                    SAME memory! Dangerous!
                                    Changing one changes both.

DEEP COPY (custom clone):
Original ─► [name="Alice"] [data*──────►[1,2,3,4,5]]
Clone    ─► [name="Alice"] [data*──────►[1,2,3,4,5]]
                                              ↑
                                    DIFFERENT memory (copied)
                                    Safe to modify independently.
```

```cpp
class Config {
public:
    string name;
    vector<int>* values;   // pointer — needs deep copy!

    Config(string n, vector<int> v)
        : name(n), values(new vector<int>(v)) {}

    // DEEP clone — new vector, not pointer copy
    Config* clone() const {
        Config* c = new Config(name, *values);   // copies vector contents
        return c;
    }

    ~Config() { delete values; }
};
```

---

## Flowchart

```
Client needs a new object
        │
        ▼
  Do I have a prototype available?
        │
   YES ─┘── NO → create normally (expensive)
        │
        ▼
  prototype->clone()
        │
        ▼
  Shallow or deep copy?
        │
   ┌────┴────┐
shallow   deep
   │         │
   ▼         ▼
Quick but  Safe for
risky with  objects with
pointers   pointer members
        │
        ▼
  Return new cloned object
  (customize if needed)
```

---

## Pros and Cons

| ✅ Pros                                    | ❌ Cons                                       |
| ------------------------------------------ | --------------------------------------------- |
| Avoids expensive re-initialization         | Clone can be complex with circular references |
| Creates objects without knowing their type | Deep copy vs shallow copy confusion           |
| Easy to create many similar objects        | Not all objects are easily cloneable          |
| Alternative to subclassing for variation   |                                               |

---

> 💡 **Common uses:** Game entities (spawn many enemies from one template), document templates, unit tests (clone test fixtures).
