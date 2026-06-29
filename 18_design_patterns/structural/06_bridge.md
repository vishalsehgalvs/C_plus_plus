# Bridge Pattern

**Category:** Structural

---

## What Is It?

The **Bridge** pattern separates an abstraction from its implementation so the two can vary independently — avoiding a cartesian product explosion of subclasses.

> 🔁 **Analogy:** A TV remote (abstraction) and the TV itself (implementation). The remote works with any TV brand — Samsung, Sony, LG. The remote doesn't care which TV it controls, and the TV doesn't care which remote is used. They're bridged through a common interface.

---

## When to Use It?

- You want to avoid a large number of classes from combining two dimensions
- Both the abstraction and implementation should be extensible independently
- You need to switch implementations at runtime

---

## The Problem Without Bridge (Class Explosion)

```
Without Bridge (combining Shape × Color):
Shape
├── RedCircle
├── BlueCircle
├── GreenCircle
├── RedSquare
├── BlueSquare
└── GreenSquare    ← 6 classes for 2 shapes × 3 colors

With n shapes and m colors → n×m classes needed
With Bridge → n + m classes needed
```

---

## Structure

```
Abstraction                Implementation
────────────               ──────────────
Shape                      Renderer (interface)
│ -renderer: Renderer*     │ +renderCircle()
│ +draw()                  │ +renderSquare()
│                          └──────┬──────┘
└──────┬──────┐                   │
       │      │            ┌──────┴───────┐
    Circle  Square      OpenGL          Vulkan
    │ draw()            │ renderCircle()  │ renderCircle()
    │   → renderer      │ renderSquare()  │ renderSquare()
    │     ->renderCircle()
```

---

## C++ Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// ============ Implementation Interface ============
class Renderer {
public:
    virtual void renderCircle(float x, float y, float radius) = 0;
    virtual void renderSquare(float x, float y, float side) = 0;
    virtual ~Renderer() {}
};

// ============ Concrete Implementations ============
class OpenGLRenderer : public Renderer {
public:
    void renderCircle(float x, float y, float r) override {
        cout << "[OpenGL] Drawing circle at (" << x << "," << y
             << ") radius=" << r << endl;
    }
    void renderSquare(float x, float y, float s) override {
        cout << "[OpenGL] Drawing square at (" << x << "," << y
             << ") side=" << s << endl;
    }
};

class VulkanRenderer : public Renderer {
public:
    void renderCircle(float x, float y, float r) override {
        cout << "[Vulkan] Rendering circle at (" << x << "," << y
             << ") r=" << r << " [GPU accelerated]" << endl;
    }
    void renderSquare(float x, float y, float s) override {
        cout << "[Vulkan] Rendering square at (" << x << "," << y
             << ") s=" << s << " [GPU accelerated]" << endl;
    }
};

class SVGRenderer : public Renderer {
public:
    void renderCircle(float x, float y, float r) override {
        cout << "<circle cx='" << x << "' cy='" << y
             << "' r='" << r << "'/>" << endl;
    }
    void renderSquare(float x, float y, float s) override {
        cout << "<rect x='" << x << "' y='" << y
             << "' width='" << s << "' height='" << s << "'/>" << endl;
    }
};

// ============ Abstraction ============
class Shape {
protected:
    Renderer* renderer;   // THE BRIDGE

public:
    Shape(Renderer* r) : renderer(r) {}
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
    virtual ~Shape() {}
};

// ============ Refined Abstractions ============
class Circle : public Shape {
    float x, y, radius;

public:
    Circle(float x, float y, float r, Renderer* renderer)
        : Shape(renderer), x(x), y(y), radius(r) {}

    void draw() override {
        renderer->renderCircle(x, y, radius);
    }

    void resize(float factor) override {
        radius *= factor;
    }
};

class Square : public Shape {
    float x, y, side;

public:
    Square(float x, float y, float s, Renderer* renderer)
        : Shape(renderer), x(x), y(y), side(s) {}

    void draw() override {
        renderer->renderSquare(x, y, side);
    }

    void resize(float factor) override {
        side *= factor;
    }
};

int main() {
    // Same shapes, different renderers
    OpenGLRenderer opengl;
    VulkanRenderer vulkan;
    SVGRenderer    svg;

    cout << "=== OpenGL ===" << endl;
    Circle c1(5, 5, 10, &opengl);
    Square s1(0, 0, 20, &opengl);
    c1.draw();
    s1.draw();

    cout << "\n=== Vulkan ===" << endl;
    Circle c2(5, 5, 10, &vulkan);
    c2.draw();
    c2.resize(2.0f);   // resize the circle
    c2.draw();

    cout << "\n=== SVG output ===" << endl;
    Circle c3(50, 50, 30, &svg);
    Square s3(10, 10, 40, &svg);
    c3.draw();
    s3.draw();

    return 0;
}
```

Output:

```
=== OpenGL ===
[OpenGL] Drawing circle at (5,5) radius=10
[OpenGL] Drawing square at (0,0) side=20

=== Vulkan ===
[Vulkan] Rendering circle at (5,5) r=10 [GPU accelerated]
[Vulkan] Rendering circle at (5,5) r=20 [GPU accelerated]

=== SVG output ===
<circle cx='50' cy='50' r='30'/>
<rect x='10' y='10' width='40' height='40'/>
```

---

## Bridge vs Adapter

```
Bridge (designed upfront):      Adapter (retrofitting):
────────────────────────────    ────────────────────────────
Separates abstraction from      Makes incompatible interfaces
implementation before code is   work after the fact
written
                                Adapts an existing class
Allows both sides to            to a new interface
evolve independently
                                Usually one-to-one
Both sides have their own
class hierarchy
```

---

## Pros and Cons

| ✅ Pros                                                      | ❌ Cons                                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------- |
| Avoids class explosion (n + m vs n × m)                      | Makes code more complex upfront                               |
| Both abstraction and implementation extensible independently | Correct identification of "two dimensions" can be non-obvious |
| Can switch implementations at runtime                        | Overkill for simple cases                                     |
| Follows Open/Closed Principle                                |                                                               |

---

> 💡 **Common uses:** Graphics engines (abstraction = shape, implementation = rendering API), device drivers, database abstraction layers (ORM + multiple DB backends).
