# Flyweight Pattern

**Category:** Structural

---

## What Is It?

The **Flyweight** pattern minimizes memory usage by **sharing common data** among many fine-grained objects instead of storing it separately in each instance.

> 🔁 **Analogy:** A book store has millions of books, but if 10,000 people buy the same edition of Harry Potter, the store doesn't store 10,000 unique descriptions of the book — they all share the same ISBN, title, author, and cover image. Only the individual copy's location (shelf number) is unique per copy.

---

## When to Use It?

- You need a very large number of similar objects (thousands or millions)
- Most object state is identical between instances (intrinsic state)
- Memory usage is a problem
- Examples: characters in a text editor, particles in a game, tree leaves in a forest renderer

---

## Intrinsic vs Extrinsic State

```
Intrinsic State:               Extrinsic State:
─────────────────              ─────────────────
Shared, immutable              Unique per object
Stored in Flyweight            Passed in by client

Font type, size, style         x, y position of each character
Tree model (mesh, texture)     x, y, z world position of each tree
Bullet sprite/color            x, y velocity of each bullet
```

---

## C++ Implementation: Forest of Trees

```cpp
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// ============ Flyweight (shared state) ============
class TreeType {
    string name;
    string color;
    string texture;   // shared mesh/image

public:
    TreeType(string n, string c, string tex)
        : name(n), color(c), texture(tex) {}

    void draw(int x, int y) const {
        cout << "Drawing [" << name << "|" << color << "] tree at ("
             << x << "," << y << ")" << endl;
    }
};

// ============ Flyweight Factory ============
class TreeTypeFactory {
    map<string, TreeType*> treeTypes;

public:
    TreeType* getTreeType(const string& name, const string& color, const string& tex) {
        string key = name + "_" + color;
        if (treeTypes.find(key) == treeTypes.end()) {
            cout << "[Factory] Creating new TreeType: " << key << endl;
            treeTypes[key] = new TreeType(name, color, tex);
        }
        return treeTypes[key];    // return existing or newly created
    }

    int getCount() const { return treeTypes.size(); }

    ~TreeTypeFactory() {
        for (auto& [k, v] : treeTypes) delete v;
    }
};

// ============ Context (unique per tree) ============
struct Tree {
    int x, y;             // extrinsic — unique position
    TreeType* type;       // intrinsic — shared

    Tree(int x, int y, TreeType* t) : x(x), y(y), type(t) {}

    void draw() const { type->draw(x, y); }
};

// ============ Forest (client) ============
class Forest {
    vector<Tree> trees;
    TreeTypeFactory factory;

public:
    void plantTree(int x, int y, const string& name, const string& color, const string& tex) {
        TreeType* type = factory.getTreeType(name, color, tex);
        trees.emplace_back(x, y, type);
    }

    void render() const {
        for (const auto& tree : trees) tree.draw();
    }

    void printStats() const {
        cout << "\nTotal trees: " << trees.size()
             << " | Unique types: " << factory.getCount() << endl;
    }
};

int main() {
    Forest forest;

    // Plant many trees — only 3 unique types created
    forest.plantTree(10, 20, "Pine", "dark green", "pine_tex.png");
    forest.plantTree(50, 80, "Oak",  "brown",      "oak_tex.png");
    forest.plantTree(30, 40, "Pine", "dark green", "pine_tex.png");  // reuses Pine!
    forest.plantTree(70, 10, "Birch","white",      "birch_tex.png");
    forest.plantTree(90, 60, "Oak",  "brown",      "oak_tex.png");   // reuses Oak!
    forest.plantTree(15, 75, "Pine", "dark green", "pine_tex.png");  // reuses Pine!

    forest.render();
    forest.printStats();

    return 0;
}
```

Output:

```
[Factory] Creating new TreeType: Pine_dark green
[Factory] Creating new TreeType: Oak_brown
[Factory] Creating new TreeType: Birch_white
Drawing [Pine|dark green] tree at (10,20)
Drawing [Oak|brown] tree at (50,80)
Drawing [Pine|dark green] tree at (30,40)
Drawing [Birch|white] tree at (70,10)
Drawing [Oak|brown] tree at (90,60)
Drawing [Pine|dark green] tree at (15,75)

Total trees: 6 | Unique types: 3
```

---

## Memory Savings Diagram

```
WITHOUT Flyweight (1 million trees × 100 bytes each):
[Tree1: Pine, dark green, texture_data(80B), x=10, y=20]  ← 100 bytes
[Tree2: Pine, dark green, texture_data(80B), x=30, y=40]  ← 100 bytes
[Tree3: Pine, dark green, texture_data(80B), x=50, y=60]  ← 100 bytes
...
Total: 1,000,000 × 100 = ~100 MB

WITH Flyweight:
Shared: [Pine: texture_data(80B), "dark green"]  ← 100 bytes ONCE
[Tree1: type*, x=10, y=20]  ← 12 bytes
[Tree2: type*, x=30, y=40]  ← 12 bytes
[Tree3: type*, x=50, y=60]  ← 12 bytes
...
Total: 100 bytes + 1,000,000 × 12 = ~12 MB
Savings: 88 MB!
```

---

## Real-World Example: Text Editor Characters

```cpp
// In a text editor, each character has font, size, color (shared)
// but position and the actual char value is unique

class CharacterStyle {   // Flyweight — shared
    string font;
    int    size;
    string color;
public:
    CharacterStyle(string f, int s, string c) : font(f), size(s), color(c) {}
    void render(char c, int x, int y) const {
        cout << "Char '" << c << "' at (" << x << "," << y
             << ") [" << font << " " << size << "pt " << color << "]" << endl;
    }
};

struct Character {    // Context — unique per character
    char c;
    int  x, y;
    CharacterStyle* style;   // shared
};
```

---

## Pros and Cons

| ✅ Pros                                           | ❌ Cons                                                     |
| ------------------------------------------------- | ----------------------------------------------------------- |
| Dramatic memory savings when many similar objects | More complexity — must split state into intrinsic/extrinsic |
| Reduces object count significantly                | Extrinsic state must be computed or passed in               |
| Works well with immutable shared data             | Can make code harder to read                                |

---

> 💡 **Used in:** Game engines (particles, trees, enemies), text editors (character objects), web browsers (CSS style sharing), Java `String.intern()` and `Integer` caching (-128 to 127).
