# Visitor Pattern

**Category:** Behavioral

---

## What Is It?

The **Visitor** pattern lets you add new operations to objects **without changing their classes**. You define a new operation in a separate visitor object that "visits" each element.

> 🔁 **Analogy:** A tax inspector visiting different types of property (house, car, boat). Each property knows how to "receive" the inspector. The inspector knows how to calculate tax for each type. If new tax rules appear, you update the inspector — not the properties.

---

## When to Use It?

- You need to perform many distinct, unrelated operations on an object structure
- You don't want to "pollute" element classes with these operations
- The object structure changes rarely, but you frequently add new operations

---

## Structure

```
  Visitor (interface)           Element (interface)
  │ +visitA(ConcreteA*)         │ +accept(Visitor*)
  │ +visitB(ConcreteB*)         └───────┬──────────
  └──────────────┐               ConcreteA  ConcreteB
                 │               accept(v)  accept(v)
           ConcreteVisitor        │           │
           +visitA(A*)            └──────┬────┘
           +visitB(B*)                   │
                 ▲                       │
                 └───── v->visit(this) ──┘
                        (double dispatch)
```

---

## C++ Implementation: Shape Area and Perimeter

```cpp
#include <iostream>
#include <cmath>
using namespace std;

// Forward declarations
class Circle;
class Rectangle;
class Triangle;

// ============ Visitor Interface ============
class ShapeVisitor {
public:
    virtual void visit(Circle& c) = 0;
    virtual void visit(Rectangle& r) = 0;
    virtual void visit(Triangle& t) = 0;
    virtual ~ShapeVisitor() {}
};

// ============ Element Interface ============
class Shape {
public:
    virtual void accept(ShapeVisitor& visitor) = 0;
    virtual ~Shape() {}
};

// ============ Concrete Elements ============
class Circle : public Shape {
public:
    double radius;
    Circle(double r) : radius(r) {}
    void accept(ShapeVisitor& visitor) override { visitor.visit(*this); }
};

class Rectangle : public Shape {
public:
    double width, height;
    Rectangle(double w, double h) : width(w), height(h) {}
    void accept(ShapeVisitor& visitor) override { visitor.visit(*this); }
};

class Triangle : public Shape {
public:
    double a, b, c;   // sides
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}
    void accept(ShapeVisitor& visitor) override { visitor.visit(*this); }
};

// ============ Concrete Visitor 1: Area Calculator ============
class AreaCalculator : public ShapeVisitor {
public:
    void visit(Circle& c) override {
        double area = M_PI * c.radius * c.radius;
        cout << "Circle area: " << area << endl;
    }
    void visit(Rectangle& r) override {
        double area = r.width * r.height;
        cout << "Rectangle area: " << area << endl;
    }
    void visit(Triangle& t) override {
        double s = (t.a + t.b + t.c) / 2;
        double area = sqrt(s * (s-t.a) * (s-t.b) * (s-t.c));
        cout << "Triangle area: " << area << endl;
    }
};

// ============ Concrete Visitor 2: Perimeter Calculator ============
class PerimeterCalculator : public ShapeVisitor {
public:
    void visit(Circle& c) override {
        cout << "Circle perimeter: " << 2 * M_PI * c.radius << endl;
    }
    void visit(Rectangle& r) override {
        cout << "Rectangle perimeter: " << 2 * (r.width + r.height) << endl;
    }
    void visit(Triangle& t) override {
        cout << "Triangle perimeter: " << t.a + t.b + t.c << endl;
    }
};

// ============ Concrete Visitor 3: XML Exporter (new operation — no shape changes!) ============
class XMLExporter : public ShapeVisitor {
public:
    void visit(Circle& c) override {
        cout << "<circle radius='" << c.radius << "'/>" << endl;
    }
    void visit(Rectangle& r) override {
        cout << "<rect width='" << r.width << "' height='" << r.height << "'/>" << endl;
    }
    void visit(Triangle& t) override {
        cout << "<triangle a='" << t.a << "' b='" << t.b << "' c='" << t.c << "'/>" << endl;
    }
};

int main() {
    Circle    c(5.0);
    Rectangle r(4.0, 6.0);
    Triangle  t(3.0, 4.0, 5.0);

    vector<Shape*> shapes = {&c, &r, &t};

    AreaCalculator      areaCalc;
    PerimeterCalculator perimCalc;
    XMLExporter         xmlExport;

    cout << "=== Areas ===" << endl;
    for (auto* s : shapes) s->accept(areaCalc);

    cout << "\n=== Perimeters ===" << endl;
    for (auto* s : shapes) s->accept(perimCalc);

    cout << "\n=== XML Export ===" << endl;
    for (auto* s : shapes) s->accept(xmlExport);

    return 0;
}
```

Output:

```
=== Areas ===
Circle area: 78.5398
Rectangle area: 24
Triangle area: 6

=== Perimeters ===
Circle perimeter: 31.4159
Rectangle perimeter: 20
Triangle perimeter: 12

=== XML Export ===
<circle radius='5'/>
<rect width='4' height='6'/>
<triangle a='3' b='4' c='5'/>
```

---

## How Double Dispatch Works

```
shape->accept(visitor)
    │
    │  Shape's accept() calls:
    │  visitor.visit(*this)
    │
    ▼
visitor.visit(Circle&)    ← actual runtime type of shape is Circle
    OR
visitor.visit(Rectangle&) ← actual runtime type is Rectangle

The correct overload is selected based on BOTH:
1. The type of the visitor  (which visit() implementation)
2. The type of the element  (which overload of visit())
This is called "double dispatch".
```

---

## Pros and Cons

| ✅ Pros                                             | ❌ Cons                                                  |
| --------------------------------------------------- | -------------------------------------------------------- |
| Add new operations without changing element classes | Adding new element types requires changing every visitor |
| Operations are grouped in one visitor class         | Breaks encapsulation if visitor needs private state      |
| Easy to accumulate state across elements            | Can be complex to understand at first                    |

---

> 💡 **Used in:** Compilers (AST traversal — type checking visitor, code generation visitor), DOM traversal, report generators, tax calculation systems.
