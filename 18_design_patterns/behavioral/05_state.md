# State Pattern

**Category:** Behavioral

---

## What Is It?

The **State** pattern allows an object to **alter its behavior when its internal state changes**. The object will appear to change its class.

> 🔁 **Analogy:** A traffic light. When it's GREEN, it behaves one way (cars go). When it turns YELLOW, different behavior (slow down). When RED, different again (stop). The light is the same physical object, but its behavior depends entirely on its current state.

---

## When to Use It?

- An object behaves differently depending on its current state
- There are complex conditional statements based on the object's state
- States can transition from one to another

---

## Structure

```
Context
│ -state: State*     ← current state
│ +request()         ← delegates to current state
│ +setState(State*)
│
│ delegates to ──►  State (interface)
                    │ +handle(Context*)
                    △
         ┌──────────┼──────────┐
      StateA      StateB     StateC
      handle()   handle()   handle()
      (may change (may change (may change
       context's   context's   context's
       state)      state)      state)
```

---

## C++ Implementation: Traffic Light

```cpp
#include <iostream>
using namespace std;

// Forward declare
class TrafficLight;

// ============ State Interface ============
class LightState {
public:
    virtual void change(TrafficLight& light) = 0;
    virtual string getColor() = 0;
    virtual string getAction() = 0;
    virtual ~LightState() {}
};

// ============ Concrete States ============
class GreenState : public LightState {
public:
    void change(TrafficLight& light) override;   // defined after TrafficLight
    string getColor()  override { return "GREEN"; }
    string getAction() override { return "Go!"; }
};

class YellowState : public LightState {
public:
    void change(TrafficLight& light) override;
    string getColor()  override { return "YELLOW"; }
    string getAction() override { return "Slow down..."; }
};

class RedState : public LightState {
public:
    void change(TrafficLight& light) override;
    string getColor()  override { return "RED"; }
    string getAction() override { return "Stop!"; }
};

// ============ Context ============
class TrafficLight {
    LightState* state;

public:
    TrafficLight();

    void setState(LightState* s) { state = s; }

    void display() {
        cout << "Light: " << state->getColor()
             << " → " << state->getAction() << endl;
    }

    void change() {
        state->change(*this);
    }

    ~TrafficLight();
};

// State implementations (need TrafficLight fully defined)
static GreenState  greenState;
static YellowState yellowState;
static RedState    redState;

void GreenState::change(TrafficLight& light) {
    cout << "[Transition] Green → Yellow" << endl;
    light.setState(&yellowState);
}

void YellowState::change(TrafficLight& light) {
    cout << "[Transition] Yellow → Red" << endl;
    light.setState(&redState);
}

void RedState::change(TrafficLight& light) {
    cout << "[Transition] Red → Green" << endl;
    light.setState(&greenState);
}

TrafficLight::TrafficLight() : state(&greenState) {}
TrafficLight::~TrafficLight() {}

int main() {
    TrafficLight light;

    for (int i = 0; i < 7; i++) {
        light.display();
        light.change();
    }

    return 0;
}
```

Output:

```
Light: GREEN → Go!
[Transition] Green → Yellow
Light: YELLOW → Slow down...
[Transition] Yellow → Red
Light: RED → Stop!
[Transition] Red → Green
Light: GREEN → Go!
[Transition] Green → Yellow
...
```

---

## Real-World Example: Vending Machine

```cpp
#include <iostream>
#include <string>
using namespace std;

class VendingMachine;

class VMState {
public:
    virtual void insertCoin(VendingMachine& vm) = 0;
    virtual void selectItem(VendingMachine& vm) = 0;
    virtual void dispense(VendingMachine& vm) = 0;
    virtual string getName() = 0;
    virtual ~VMState() {}
};

class IdleState : public VMState {
public:
    void insertCoin(VendingMachine& vm) override;
    void selectItem(VendingMachine& vm) override {
        cout << "Insert coin first!" << endl;
    }
    void dispense(VendingMachine& vm) override {
        cout << "No item selected." << endl;
    }
    string getName() override { return "Idle"; }
};

class HasCoinState : public VMState {
public:
    void insertCoin(VendingMachine& vm) override {
        cout << "Coin already inserted." << endl;
    }
    void selectItem(VendingMachine& vm) override;
    void dispense(VendingMachine& vm) override {
        cout << "Please select an item first." << endl;
    }
    string getName() override { return "Has Coin"; }
};

class DispensingState : public VMState {
public:
    void insertCoin(VendingMachine& vm) override {
        cout << "Wait, dispensing item..." << endl;
    }
    void selectItem(VendingMachine& vm) override {
        cout << "Wait, dispensing item..." << endl;
    }
    void dispense(VendingMachine& vm) override;
    string getName() override { return "Dispensing"; }
};

static IdleState       idleState;
static HasCoinState    hasCoinState;
static DispensingState dispensingState;

class VendingMachine {
    VMState* state;
    int itemCount;

public:
    VendingMachine(int items) : state(&idleState), itemCount(items) {}

    void setState(VMState* s) { state = s; }
    void decrementItem() { itemCount--; }
    int getItemCount() const { return itemCount; }

    void insertCoin()  { cout << "[State: " << state->getName() << "] "; state->insertCoin(*this);  }
    void selectItem()  { cout << "[State: " << state->getName() << "] "; state->selectItem(*this);  }
    void dispense()    { cout << "[State: " << state->getName() << "] "; state->dispense(*this);    }
};

void IdleState::insertCoin(VendingMachine& vm) {
    cout << "Coin inserted. Select an item." << endl;
    vm.setState(&hasCoinState);
}

void HasCoinState::selectItem(VendingMachine& vm) {
    cout << "Item selected. Dispensing..." << endl;
    vm.setState(&dispensingState);
    vm.dispense();
}

void DispensingState::dispense(VendingMachine& vm) {
    cout << "Dispensing your item!" << endl;
    vm.decrementItem();
    if (vm.getItemCount() > 0) {
        vm.setState(&idleState);
    } else {
        cout << "Out of stock!" << endl;
    }
}

int main() {
    VendingMachine machine(2);

    machine.insertCoin();
    machine.selectItem();

    machine.insertCoin();
    machine.selectItem();

    machine.insertCoin();   // out of stock
}
```

---

## State Transition Diagram

```
     insertCoin()          selectItem()
Idle ───────────► HasCoin ───────────► Dispensing
  ▲                                       │
  │                 dispense()            │
  └───────────────────────────────────────┘
  (return to idle unless out of stock)
```

---

## State vs Strategy

```
State:                              Strategy:
─────────────────────────────       ──────────────────────────────
State objects can change the        Strategy objects don't change
context's state (transitions)       the context's strategy (client does)

States are aware of each other      Strategies don't know about each other
(they trigger transitions)

Object appears to change class      Algorithm is swappable
depending on state                  externally
```

---

## Pros and Cons

| ✅ Pros                               | ❌ Cons                                               |
| ------------------------------------- | ----------------------------------------------------- |
| Eliminates large if/switch on state   | Many state classes                                    |
| State behavior localized in one class | State classes are tightly coupled through transitions |
| Adding new states is easy             | Overkill for only 2-3 simple states                   |
| Open/Closed for new states            |                                                       |

---

> 💡 **Used in:** TCP connections (CLOSED, LISTEN, ESTABLISHED), vending machines, game character states (idle, running, jumping, attacking), order processing (pending, confirmed, shipped, delivered).
