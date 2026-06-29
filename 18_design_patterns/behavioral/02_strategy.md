# Strategy Pattern

**Category:** Behavioral

---

## What Is It?

The **Strategy** pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable. The strategy lets the algorithm vary independently from clients that use it.

> 🔁 **Analogy:** GPS navigation. You set a destination and choose a strategy: "fastest route", "shortest route", or "avoid highways". The navigation app doesn't change — only the routing strategy swaps. You can switch strategies any time.

---

## When to Use It?

- You have multiple ways to do the same thing (sort, compress, route, pay)
- You want to switch algorithms at runtime
- You want to eliminate large if/switch blocks that select behavior

---

## Structure

```
Context
│ -strategy: Strategy*
│ +setStrategy(Strategy*)
│ +executeStrategy()
│
└── delegates work to ──► Strategy (interface)
                              △
                     ┌────────┼────────┐
                  StrategyA  StrategyB  StrategyC
                  +execute() +execute() +execute()
```

---

## C++ Implementation: Sorting Strategies

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============ Strategy Interface ============
class SortStrategy {
public:
    virtual void sort(vector<int>& data) = 0;
    virtual string name() = 0;
    virtual ~SortStrategy() {}
};

// ============ Concrete Strategies ============
class BubbleSort : public SortStrategy {
public:
    void sort(vector<int>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - i - 1; j++)
                if (data[j] > data[j + 1])
                    swap(data[j], data[j + 1]);
    }
    string name() override { return "Bubble Sort"; }
};

class QuickSort : public SortStrategy {
    void quickSort(vector<int>& data, int low, int high) {
        if (low < high) {
            int pivot = data[high];
            int i = low - 1;
            for (int j = low; j < high; j++)
                if (data[j] <= pivot) swap(data[++i], data[j]);
            swap(data[i + 1], data[high]);
            int pi = i + 1;
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }
public:
    void sort(vector<int>& data) override {
        quickSort(data, 0, data.size() - 1);
    }
    string name() override { return "Quick Sort"; }
};

class StdSort : public SortStrategy {
public:
    void sort(vector<int>& data) override {
        std::sort(data.begin(), data.end());
    }
    string name() override { return "std::sort"; }
};

// ============ Context ============
class Sorter {
    SortStrategy* strategy;

public:
    Sorter(SortStrategy* s) : strategy(s) {}

    void setStrategy(SortStrategy* s) { strategy = s; }

    void sort(vector<int> data) {   // pass by value to not modify original
        cout << "Using: " << strategy->name() << endl;
        strategy->sort(data);
        cout << "Result: ";
        for (int x : data) cout << x << " ";
        cout << endl;
    }
};

int main() {
    vector<int> data = {64, 25, 12, 22, 11};

    BubbleSort bubble;
    QuickSort  quick;
    StdSort    stdSort;

    Sorter sorter(&bubble);
    sorter.sort(data);

    sorter.setStrategy(&quick);    // switch strategy at runtime!
    sorter.sort(data);

    sorter.setStrategy(&stdSort);
    sorter.sort(data);

    return 0;
}
```

Output:

```
Using: Bubble Sort
Result: 11 12 22 25 64
Using: Quick Sort
Result: 11 12 22 25 64
Using: std::sort
Result: 11 12 22 25 64
```

---

## Real-World Example: Payment Processing

```cpp
#include <iostream>
#include <string>
using namespace std;

// Strategy
class PaymentStrategy {
public:
    virtual bool pay(double amount) = 0;
    virtual ~PaymentStrategy() {}
};

// Concrete strategies
class CreditCard : public PaymentStrategy {
    string cardNumber, name;
public:
    CreditCard(string card, string n) : cardNumber(card), name(n) {}
    bool pay(double amount) override {
        cout << "[Credit Card] Charging $" << amount << " to " << name
             << " (card: ****" << cardNumber.substr(cardNumber.size()-4) << ")" << endl;
        return true;
    }
};

class PayPal : public PaymentStrategy {
    string email;
public:
    PayPal(string e) : email(e) {}
    bool pay(double amount) override {
        cout << "[PayPal] Sending $" << amount << " from " << email << endl;
        return true;
    }
};

class Crypto : public PaymentStrategy {
    string wallet;
public:
    Crypto(string w) : wallet(w) {}
    bool pay(double amount) override {
        cout << "[Crypto] Transferring $" << amount
             << " from wallet " << wallet << endl;
        return true;
    }
};

class ShoppingCart {
    PaymentStrategy* payStrategy = nullptr;
    double total = 0;

public:
    void addItem(double price) { total += price; }
    void setPaymentMethod(PaymentStrategy* strategy) { payStrategy = strategy; }

    void checkout() {
        if (!payStrategy) {
            cout << "No payment method set!" << endl;
            return;
        }
        cout << "Total: $" << total << endl;
        bool success = payStrategy->pay(total);
        if (success) cout << "Payment successful!" << endl;
    }
};

int main() {
    ShoppingCart cart;
    cart.addItem(29.99);
    cart.addItem(49.99);
    cart.addItem(9.99);

    CreditCard cc("4111111111111234", "Alice Smith");
    PayPal     pp("alice@email.com");

    cout << "=== Paying with Credit Card ===" << endl;
    cart.setPaymentMethod(&cc);
    cart.checkout();

    cout << "\n=== Switching to PayPal ===" << endl;
    cart.setPaymentMethod(&pp);
    cart.checkout();

    return 0;
}
```

---

## Strategy vs if/switch

```
Without Strategy (messy if/switch):         With Strategy (clean):
─────────────────────────────────────       ──────────────────────────
void sort(vector<int>& v, string type) {    sorter.setStrategy(&quick);
  if (type == "bubble") {                   sorter.sort(data);
    // bubble sort...
  } else if (type == "quick") {
    // quick sort...
  } else if (type == "merge") {
    // merge sort...
  }
  // adding new sort = edit this function
}                                           // adding new sort = new class only
```

---

## Pros and Cons

| ✅ Pros                                                | ❌ Cons                                      |
| ------------------------------------------------------ | -------------------------------------------- |
| Swap algorithms at runtime                             | More classes (one per strategy)              |
| Eliminates if/switch chains                            | Client must be aware of different strategies |
| Each strategy is independently testable                | Overkill for only 2 algorithms               |
| Open/Closed — add strategies without modifying context |                                              |

---

> 💡 **Used in:** `std::sort` (comparator as strategy), compression algorithms, routing engines, A/B testing, pricing rules, validation strategies.
