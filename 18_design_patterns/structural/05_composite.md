# Composite Pattern

**Category:** Structural

---

## What Is It?

The **Composite** pattern lets you compose objects into **tree structures** and treat individual objects and groups of objects **uniformly**.

> 🔁 **Analogy:** A file system. A folder can contain files and other folders. Whether you "delete" a single file or a whole folder (which has sub-folders and files), the operation is the same from your perspective. You don't care if it's a leaf (file) or a branch (folder).

---

## When to Use It?

- You need to represent part-whole hierarchies (trees)
- You want clients to ignore the difference between single objects and groups
- Examples: file systems, UI component trees, org charts, XML/JSON parsers

---

## Structure

```
Client
  │
  └──► Component (interface)
            △
      ┌─────┴──────┐
      │             │
   Leaf          Composite
   (no children)  (has children[])
                   │ +add(Component*)
                   │ +remove(Component*)
                   │ +operation() → calls each child's operation()
```

---

## C++ Implementation: File System

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ============ Component Interface ============
class FileSystemItem {
protected:
    string name;
    int depth;    // for indentation in display

public:
    FileSystemItem(const string& n, int d = 0) : name(n), depth(d) {}
    virtual void display() = 0;
    virtual long getSize() = 0;
    virtual ~FileSystemItem() {}
};

// ============ Leaf ============
class File : public FileSystemItem {
    long size;

public:
    File(const string& name, long size, int depth = 0)
        : FileSystemItem(name, depth), size(size) {}

    void display() override {
        cout << string(depth * 2, ' ') << "📄 " << name
             << " (" << size << " KB)" << endl;
    }

    long getSize() override { return size; }
};

// ============ Composite ============
class Folder : public FileSystemItem {
    vector<FileSystemItem*> children;

public:
    Folder(const string& name, int depth = 0)
        : FileSystemItem(name, depth) {}

    void add(FileSystemItem* item) {
        children.push_back(item);
    }

    void display() override {
        cout << string(depth * 2, ' ') << "📁 " << name
             << " (" << getSize() << " KB total)" << endl;
        for (auto* child : children) {
            child->display();
        }
    }

    long getSize() override {
        long total = 0;
        for (auto* child : children) {
            total += child->getSize();
        }
        return total;
    }

    ~Folder() {
        for (auto* child : children) delete child;
    }
};

int main() {
    // Build a file tree
    Folder* root = new Folder("C:/", 0);

    Folder* documents = new Folder("Documents", 1);
    documents->add(new File("resume.pdf", 150, 2));
    documents->add(new File("notes.txt", 10, 2));

    Folder* photos = new Folder("Photos", 1);
    photos->add(new File("vacation.jpg", 3500, 2));
    photos->add(new File("birthday.jpg", 2800, 2));

    Folder* work = new Folder("Work", 2);
    work->add(new File("project.cpp", 45, 3));
    work->add(new File("main.h", 12, 3));
    documents->add(work);

    root->add(documents);
    root->add(photos);
    root->add(new File("README.txt", 5, 1));

    // Display — same call for file or folder!
    root->display();
    cout << "\nTotal size: " << root->getSize() << " KB" << endl;

    delete root;
    return 0;
}
```

Output:

```
📁 C:/ (6522 KB total)
  📁 Documents (217 KB total)
    📄 resume.pdf (150 KB)
    📄 notes.txt (10 KB)
    📁 Work (57 KB total)
      📄 project.cpp (45 KB)
      📄 main.h (12 KB)
  📁 Photos (6300 KB total)
    📄 vacation.jpg (3500 KB)
    📄 birthday.jpg (2800 KB)
  📄 README.txt (5 KB)

Total size: 6522 KB
```

---

## Real-World Example: UI Component Tree

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class UIComponent {
protected:
    string id;
public:
    UIComponent(string id) : id(id) {}
    virtual void render(int indent = 0) = 0;
    virtual ~UIComponent() {}
};

// Leaf components
class Button : public UIComponent {
    string label;
public:
    Button(string id, string label) : UIComponent(id), label(label) {}
    void render(int indent = 0) override {
        cout << string(indent, ' ') << "[Button: " << label << "]" << endl;
    }
};

class TextBox : public UIComponent {
    string placeholder;
public:
    TextBox(string id, string ph) : UIComponent(id), placeholder(ph) {}
    void render(int indent = 0) override {
        cout << string(indent, ' ') << "[Input: " << placeholder << "]" << endl;
    }
};

// Composite component
class Panel : public UIComponent {
    vector<UIComponent*> children;
    string title;
public:
    Panel(string id, string title) : UIComponent(id), title(title) {}

    void add(UIComponent* c) { children.push_back(c); }

    void render(int indent = 0) override {
        cout << string(indent, ' ') << "┌─ Panel: " << title << endl;
        for (auto* child : children) child->render(indent + 2);
        cout << string(indent, ' ') << "└─────────" << endl;
    }

    ~Panel() { for (auto* c : children) delete c; }
};

int main() {
    Panel* form = new Panel("form", "Login Form");
    form->add(new TextBox("user", "Enter username"));
    form->add(new TextBox("pass", "Enter password"));

    Panel* buttons = new Panel("btns", "Actions");
    buttons->add(new Button("login", "Login"));
    buttons->add(new Button("cancel", "Cancel"));

    form->add(buttons);
    form->render();

    delete form;
}
```

Output:

```
┌─ Panel: Login Form
  [Input: Enter username]
  [Input: Enter password]
  ┌─ Panel: Actions
    [Button: Login]
    [Button: Cancel]
  └─────────
└─────────
```

---

## Pros and Cons

| ✅ Pros                                      | ❌ Cons                                                 |
| -------------------------------------------- | ------------------------------------------------------- |
| Client treats leaves and composites the same | Can be hard to restrict what can be added to composites |
| Easy to add new component types              | Design can be overly general                            |
| Natural for recursive/tree structures        |                                                         |

---

> 💡 **Used in:** File systems, HTML/DOM trees, GUI frameworks, org charts, expression trees (math parsers), scene graphs (3D engines).
