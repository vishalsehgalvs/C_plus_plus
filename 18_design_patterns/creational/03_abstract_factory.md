# Abstract Factory Pattern

**Category:** Creational

---

## What Is It?

**Abstract Factory** is a factory of factories. It provides an interface for creating **families of related objects** without specifying their concrete classes.

> 🔁 **Analogy:** IKEA has different furniture families — "KALLAX" style and "HEMNES" style. Within each family, you get a matching Chair, Table, and Sofa. An Abstract Factory is like a "furniture family selector" — you pick the family once, and you get all matching pieces from that family.

---

## When to Use It?

- Your system must work with multiple families of related products (e.g., Windows UI vs Mac UI)
- You want to enforce that products from the same family are used together
- You need to switch the whole family easily (toggle between themes/platforms)

---

## Structure

```
┌─────────────────┐           ┌──────────────┐
│ AbstractFactory │           │ AbstractBtn  │
├─────────────────┤           ├──────────────┤
│+createButton()  │ ──creates►│ +render()    │
│+createCheckbox()│           └──────────────┘
└─────────────────┘                 △
        △                    ┌──────┴──────┐
   ┌────┴────┐            WinBtn         MacBtn
   │         │
WinFactory  MacFactory    ┌──────────────┐
                          │AbstractChkbx │
WinFactory creates:       ├──────────────┤
  WinButton + WinCheckbox │ +check()     │
                          └──────────────┘
MacFactory creates:              △
  MacButton + MacCheckbox  ┌─────┴──────┐
                         WinChk       MacChk
```

---

## C++ Implementation

```cpp
#include <iostream>
using namespace std;

// ============ Abstract Products ============
class Button {
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

class Checkbox {
public:
    virtual void check() = 0;
    virtual ~Checkbox() {}
};

// ============ Windows Products ============
class WinButton : public Button {
public:
    void render() override {
        cout << "[ Windows Button ]" << endl;
    }
};

class WinCheckbox : public Checkbox {
public:
    void check() override {
        cout << "[x] Windows Checkbox checked" << endl;
    }
};

// ============ Mac Products ============
class MacButton : public Button {
public:
    void render() override {
        cout << "( Mac Button )" << endl;
    }
};

class MacCheckbox : public Checkbox {
public:
    void check() override {
        cout << "(✓) Mac Checkbox checked" << endl;
    }
};

// ============ Abstract Factory ============
class GUIFactory {
public:
    virtual Button*   createButton()   = 0;
    virtual Checkbox* createCheckbox() = 0;
    virtual ~GUIFactory() {}
};

// ============ Concrete Factories ============
class WindowsFactory : public GUIFactory {
public:
    Button*   createButton()   override { return new WinButton();   }
    Checkbox* createCheckbox() override { return new WinCheckbox(); }
};

class MacFactory : public GUIFactory {
public:
    Button*   createButton()   override { return new MacButton();   }
    Checkbox* createCheckbox() override { return new MacCheckbox(); }
};

// ============ Client ============
class Application {
    Button*   btn;
    Checkbox* chk;

public:
    Application(GUIFactory* factory) {
        btn = factory->createButton();
        chk = factory->createCheckbox();
    }

    void renderUI() {
        cout << "--- Rendering UI ---" << endl;
        btn->render();
        chk->check();
    }

    ~Application() {
        delete btn;
        delete chk;
    }
};

// ============ Main ============
int main() {
    string os = "mac";   // could come from config/env

    GUIFactory* factory;
    if (os == "windows") {
        factory = new WindowsFactory();
    } else {
        factory = new MacFactory();
    }

    Application app(factory);
    app.renderUI();

    delete factory;
    return 0;
}
```

Output (when `os = "mac"`):

```
--- Rendering UI ---
( Mac Button )
(✓) Mac Checkbox checked
```

---

## Real-World Example: Dark/Light Theme

```cpp
#include <iostream>
#include <string>
using namespace std;

// Abstract products
class Background {
public:
    virtual string getColor() = 0;
    virtual ~Background() {}
};

class TextColor {
public:
    virtual string getColor() = 0;
    virtual ~TextColor() {}
};

// Light theme products
class LightBackground : public Background {
public:
    string getColor() override { return "#FFFFFF (white)"; }
};

class LightText : public TextColor {
public:
    string getColor() override { return "#000000 (black)"; }
};

// Dark theme products
class DarkBackground : public Background {
public:
    string getColor() override { return "#1E1E1E (dark gray)"; }
};

class DarkText : public TextColor {
public:
    string getColor() override { return "#D4D4D4 (light gray)"; }
};

// Abstract factory
class ThemeFactory {
public:
    virtual Background* createBackground() = 0;
    virtual TextColor*  createTextColor()  = 0;
    virtual ~ThemeFactory() {}
};

// Concrete factories
class LightThemeFactory : public ThemeFactory {
public:
    Background* createBackground() override { return new LightBackground(); }
    TextColor*  createTextColor()  override { return new LightText(); }
};

class DarkThemeFactory : public ThemeFactory {
public:
    Background* createBackground() override { return new DarkBackground(); }
    TextColor*  createTextColor()  override { return new DarkText(); }
};

void applyTheme(ThemeFactory* factory) {
    Background* bg  = factory->createBackground();
    TextColor*  txt = factory->createTextColor();

    cout << "Background: " << bg->getColor() << endl;
    cout << "Text:       " << txt->getColor() << endl;

    delete bg;
    delete txt;
}

int main() {
    cout << "=== Light Theme ===" << endl;
    LightThemeFactory light;
    applyTheme(&light);

    cout << "\n=== Dark Theme ===" << endl;
    DarkThemeFactory dark;
    applyTheme(&dark);

    return 0;
}
```

---

## Comparison: Factory vs Abstract Factory

```
Factory Method:                    Abstract Factory:
─────────────────────────────      ─────────────────────────────────
Creates ONE type of product        Creates FAMILIES of related products

createAnimal("dog") → Dog          factory->createButton()  → WinButton
                                   factory->createCheckbox()→ WinCheckbox

If you need: one product           If you need: products that belong
             with variants           together (must all be Windows or Mac)
```

---

## Pros and Cons

| ✅ Pros                                               | ❌ Cons                                                  |
| ----------------------------------------------------- | -------------------------------------------------------- |
| Products from the same family always match            | Adding new product types requires changing every factory |
| Easy to swap whole family (change one factory)        | Many classes — can feel verbose                          |
| Client code decoupled from concrete classes           |                                                          |
| Open/Closed for new families (just add a new factory) |                                                          |

---

> 💡 **Key insight:** Abstract Factory = multiple Factory Methods grouped together under one roof. Choose it when you need to ensure an entire set of products is consistent.
