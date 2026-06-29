# Memento Pattern

**Category:** Behavioral

---

## What Is It?

The **Memento** pattern captures and externalizes an object's internal state so it can be **restored later**, without violating encapsulation.

> 🔁 **Analogy:** Ctrl+Z in any app. You type text, and the app saves snapshots of the document. When you press Ctrl+Z, it restores the previous snapshot. The document (Originator) creates snapshots (Mementos), and the history (Caretaker) keeps them.

---

## When to Use It?

- You need undo/redo functionality
- You want to take snapshots of an object's state
- The object's state is complex and you need to save/restore it without exposing internals

---

## Structure

```
Originator               Memento
│ -state                 │ -savedState (private)
│ +save() → Memento*     │ +getState() (only Originator calls this)
│ +restore(Memento*)     │
│                        │
│         Caretaker
│         │ -mementos: stack<Memento*>
│         │ +backup()   → calls originator.save()
│         │ +undo()     → calls originator.restore()
```

---

## C++ Implementation: Text Editor Undo

```cpp
#include <iostream>
#include <string>
#include <stack>
using namespace std;

// ============ Memento ============
class EditorMemento {
    string content;
    int cursorPosition;

    // Only Editor can access internals
    friend class TextEditor;

    EditorMemento(const string& c, int pos) : content(c), cursorPosition(pos) {}

public:
    // Optional: description for debugging
    string describe() const {
        return "Content: '" + content + "' Cursor: " + to_string(cursorPosition);
    }
};

// ============ Originator ============
class TextEditor {
    string content;
    int cursorPos;

public:
    TextEditor() : content(""), cursorPos(0) {}

    void type(const string& text) {
        content.insert(cursorPos, text);
        cursorPos += text.size();
    }

    void deleteChar() {
        if (cursorPos > 0) {
            content.erase(cursorPos - 1, 1);
            cursorPos--;
        }
    }

    // Save state → returns a Memento
    EditorMemento* save() const {
        return new EditorMemento(content, cursorPos);
    }

    // Restore state from Memento
    void restore(const EditorMemento* memento) {
        content   = memento->content;
        cursorPos = memento->cursorPosition;
    }

    void display() const {
        cout << "Text: [" << content << "] | Cursor: " << cursorPos << endl;
    }
};

// ============ Caretaker ============
class History {
    stack<EditorMemento*> history;

public:
    void push(EditorMemento* m) {
        history.push(m);
    }

    EditorMemento* pop() {
        if (history.empty()) return nullptr;
        EditorMemento* top = history.top();
        history.pop();
        return top;
    }

    bool isEmpty() const { return history.empty(); }

    ~History() {
        while (!history.empty()) {
            delete history.top();
            history.pop();
        }
    }
};

int main() {
    TextEditor editor;
    History history;

    // Save initial state
    history.push(editor.save());

    editor.type("Hello");
    editor.display();
    history.push(editor.save());

    editor.type(" World");
    editor.display();
    history.push(editor.save());

    editor.type("!!!");
    editor.display();
    history.push(editor.save());

    cout << "\n--- Undoing ---" << endl;

    EditorMemento* prev = history.pop();   // discard current
    delete prev;

    prev = history.pop();
    if (prev) {
        editor.restore(prev);
        delete prev;
        editor.display();
    }

    prev = history.pop();
    if (prev) {
        editor.restore(prev);
        delete prev;
        editor.display();
    }

    prev = history.pop();
    if (prev) {
        editor.restore(prev);
        delete prev;
        editor.display();
    }

    return 0;
}
```

Output:

```
Text: [Hello] | Cursor: 5
Text: [Hello World] | Cursor: 11
Text: [Hello World!!!] | Cursor: 14

--- Undoing ---
Text: [Hello World] | Cursor: 11
Text: [Hello] | Cursor: 5
Text: [] | Cursor: 0
```

---

## Game Save System Example

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct GameState {
    int level, health, score;
    string location;
};

class GameMemento {
    GameState state;
    friend class Game;
    GameMemento(GameState s) : state(s) {}
};

class Game {
    GameState current;

public:
    Game() : current({1, 100, 0, "Start"}) {}

    void play(int newLevel, int newHealth, int score, string loc) {
        current = {newLevel, newHealth, score, loc};
        cout << "Playing: Level " << current.level
             << " HP:" << current.health
             << " Score:" << current.score
             << " @ " << current.location << endl;
    }

    GameMemento* save() {
        cout << "[Save point created]" << endl;
        return new GameMemento(current);
    }

    void load(GameMemento* m) {
        current = m->state;
        cout << "[Loaded] Level " << current.level
             << " HP:" << current.health
             << " Score:" << current.score
             << " @ " << current.location << endl;
    }
};

int main() {
    Game game;
    game.play(1, 100, 0, "Village");

    GameMemento* save1 = game.save();   // save point 1

    game.play(2, 85, 500, "Forest");
    game.play(3, 60, 1200, "Castle");

    GameMemento* save2 = game.save();   // save point 2

    game.play(4, 10, 1800, "Final Boss");
    cout << "You died!" << endl;

    cout << "\nLoading last save:" << endl;
    game.load(save2);

    cout << "\nLoading earlier save:" << endl;
    game.load(save1);

    delete save1;
    delete save2;
}
```

---

## Pros and Cons

| ✅ Pros                                    | ❌ Cons                                         |
| ------------------------------------------ | ----------------------------------------------- |
| Clean undo/redo without exposing internals | Memory can grow if many mementos are stored     |
| Originator's encapsulation is preserved    | Caretaker doesn't know the cost of saving state |
| Simple to implement for shallow state      | Complex state (deep objects) requires deep copy |

---

> 💡 **Used in:** Text editors (Ctrl+Z), game save systems, database transactions (rollback), form wizards (go back), configuration snapshots.
