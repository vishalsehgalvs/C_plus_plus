# Command Pattern

**Category:** Behavioral

---

## What Is It?

The **Command** pattern encapsulates a request as an object. This lets you parameterize clients with different requests, queue operations, log them, and support undo/redo.

> 🔁 **Analogy:** A restaurant order. You (the waiter) write down the customer's order on a ticket (command object) and hand it to the kitchen (receiver). The order can be queued, cancelled before cooking, or used to track what was served (history for undo).

---

## When to Use It?

- You need **undo/redo** functionality
- You want to **queue** operations for later execution
- You want to **log** every operation for auditing
- You want to implement **macro commands** (execute a sequence)

---

## Structure

```
Client ──creates──► Command (interface)
                        │+execute()
                        │+undo()
                    Concrete
                    Command
                    │ -receiver: Receiver*
                    │ execute() → receiver->action()
                    │ undo()    → receiver->reverseAction()
                        │
                    Receiver
                    (actual work)
                        │
                    Invoker ──stores──► command history (undo stack)
```

---

## C++ Implementation: Text Editor with Undo

```cpp
#include <iostream>
#include <string>
#include <stack>
#include <memory>
using namespace std;

// ============ Receiver ============
class TextDocument {
    string content;

public:
    void insertText(const string& text, int pos) {
        content.insert(pos, text);
        cout << "[Doc] Insert at " << pos << ": '" << text << "'" << endl;
    }

    void deleteText(int pos, int length) {
        content.erase(pos, length);
        cout << "[Doc] Delete " << length << " chars at " << pos << endl;
    }

    string getText(int pos, int length) const {
        return content.substr(pos, length);
    }

    void display() const {
        cout << "Content: [" << content << "]" << endl;
    }
};

// ============ Command Interface ============
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// ============ Concrete Commands ============
class InsertCommand : public Command {
    TextDocument& doc;
    string text;
    int position;

public:
    InsertCommand(TextDocument& d, const string& t, int pos)
        : doc(d), text(t), position(pos) {}

    void execute() override {
        doc.insertText(text, position);
    }

    void undo() override {
        doc.deleteText(position, text.size());
    }
};

class DeleteCommand : public Command {
    TextDocument& doc;
    int position, length;
    string deletedText;   // save for undo

public:
    DeleteCommand(TextDocument& d, int pos, int len)
        : doc(d), position(pos), length(len) {}

    void execute() override {
        deletedText = doc.getText(position, length);   // save first
        doc.deleteText(position, length);
    }

    void undo() override {
        doc.insertText(deletedText, position);   // restore
    }
};

// ============ Invoker (with undo stack) ============
class Editor {
    stack<unique_ptr<Command>> history;

public:
    void execute(unique_ptr<Command> cmd) {
        cmd->execute();
        history.push(move(cmd));
    }

    void undo() {
        if (history.empty()) {
            cout << "[Editor] Nothing to undo." << endl;
            return;
        }
        cout << "[Editor] Undoing last command..." << endl;
        history.top()->undo();
        history.pop();
    }
};

int main() {
    TextDocument doc;
    Editor editor;

    doc.display();

    editor.execute(make_unique<InsertCommand>(doc, "Hello", 0));
    doc.display();

    editor.execute(make_unique<InsertCommand>(doc, " World", 5));
    doc.display();

    editor.execute(make_unique<DeleteCommand>(doc, 5, 6));   // delete " World"
    doc.display();

    cout << "\n--- Undo 1 ---" << endl;
    editor.undo();
    doc.display();

    cout << "\n--- Undo 2 ---" << endl;
    editor.undo();
    doc.display();

    cout << "\n--- Undo 3 ---" << endl;
    editor.undo();
    doc.display();

    return 0;
}
```

Output:

```
Content: []
[Doc] Insert at 0: 'Hello'
Content: [Hello]
[Doc] Insert at 5: ' World'
Content: [Hello World]
[Doc] Delete 6 chars at 5
Content: [Hello]

--- Undo 1 ---
[Editor] Undoing last command...
[Doc] Insert at 5: ' World'
Content: [Hello World]

--- Undo 2 ---
[Editor] Undoing last command...
[Doc] Delete 6 chars at 5
Content: [Hello]

--- Undo 3 ---
[Editor] Undoing last command...
[Doc] Delete 5 chars at 0
Content: []
```

---

## Macro Command (Execute Multiple Commands as One)

```cpp
class MacroCommand : public Command {
    vector<unique_ptr<Command>> commands;

public:
    void add(unique_ptr<Command> cmd) {
        commands.push_back(move(cmd));
    }

    void execute() override {
        for (auto& cmd : commands) cmd->execute();
    }

    void undo() override {
        // Undo in reverse order
        for (int i = commands.size() - 1; i >= 0; i--) {
            commands[i]->undo();
        }
    }
};
```

---

## Command Queue (Deferred Execution)

```cpp
#include <queue>

class CommandQueue {
    queue<unique_ptr<Command>> pending;

public:
    void enqueue(unique_ptr<Command> cmd) {
        pending.push(move(cmd));
    }

    void processAll() {
        while (!pending.empty()) {
            pending.front()->execute();
            pending.pop();
        }
    }
};
```

---

## Pros and Cons

| ✅ Pros                                    | ❌ Cons                                     |
| ------------------------------------------ | ------------------------------------------- |
| Decouples sender from receiver             | Many small command classes                  |
| Easy undo/redo with command history        | Can be overkill for simple actions          |
| Commands can be queued and executed later  | Saved state for undo can use lots of memory |
| Supports macro commands (batch operations) |                                             |

---

> 💡 **Used in:** Text editors (Ctrl+Z), game engines (replay systems), transaction systems, GUI buttons, task queues, job schedulers.
