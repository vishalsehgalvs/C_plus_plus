
#include <iostream>
#include <memory>   // for unique_ptr
#include <string>

using namespace std;

// ======================================================
// 1. Product Interface (Abstract class)
// ======================================================
class Pizza {
public:
    virtual string getType() const = 0; // must be implemented by derived classes
    virtual ~Pizza() = default;         // virtual destructor (important for safety)
};

// ======================================================
// 2. Concrete Products
// ======================================================
class Margherita : public Pizza {
public:
    string getType() const override {
        return "Margherita";
    }
};

class Pepperoni : public Pizza {
public:
    string getType() const override {
        return "Pepperoni";
    }
};

// ======================================================
// 3. Enum for safer pizza selection (instead of strings)
// ======================================================
enum class PizzaType {
    Margherita,
    Pepperoni
};

// ======================================================
// 4. Factory (responsible for object creation)
// ======================================================
class PizzaFactory {
public:
    static unique_ptr<Pizza> createPizza(PizzaType type) {
        switch (type) {
            case PizzaType::Margherita:
                return make_unique<Margherita>();

            case PizzaType::Pepperoni:
                return make_unique<Pepperoni>();

            default:
                return nullptr;
        }
    }
};

// ======================================================
// 5. Builder (manages creation process)
// ======================================================
class PizzaBuilder {
private:
    unique_ptr<Pizza> pizza;   // smart pointer (automatic memory management)

public:
    // Create pizza using factory
    void createPizza(PizzaType type) {
        pizza = PizzaFactory::createPizza(type);
    }

    // Return ownership of the pizza
    unique_ptr<Pizza> getPizza() {
        return move(pizza);  // transfer ownership
    }
};

// ======================================================
// 6. Singleton (only one instance exists)
// ======================================================
class PizzaSingleton {
public:
    static PizzaSingleton& getInstance() {
        // local static variable ensures thread-safe initialization (C++11+)
        static PizzaSingleton instance;
        return instance;
    }

    // delete copy to enforce single instance
    PizzaSingleton(const PizzaSingleton&) = delete;
    PizzaSingleton& operator=(const PizzaSingleton&) = delete;

private:
    PizzaSingleton() = default; // private constructor
};

// ======================================================
// 7. Main function
// ======================================================
int main() {
    PizzaBuilder builder;

    // Create pizza
    builder.createPizza(PizzaType::Margherita);

    // Get pizza (ownership transferred)
    auto pizza = builder.getPizza();

    if (pizza) {
        cout << "Pizza Type: " << pizza->getType() << endl;
    } else {
        cout << "Invalid Pizza Type" << endl;
    }

    // Singleton usage
    PizzaSingleton& singleton = PizzaSingleton::getInstance();

    return 0;
}
