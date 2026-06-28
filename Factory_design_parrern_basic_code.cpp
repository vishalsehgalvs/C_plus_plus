#include <iostream>
#include <string>

using namespace std;

// ======================================================
// 1. Abstract base class (cannot be instantiated)
// ======================================================
class Pizza
{
public:
    // Pure virtual function → every derived class MUST implement this
    virtual string getType() = 0;

    // Virtual destructor (good practice)
    virtual ~Pizza() {}
};

// ======================================================
// 2. Concrete classes (actual pizza types)
// ======================================================
class Margherita : public Pizza
{
public:
    string getType() override
    {
        return "Margherita";
    }
};

class Pepperoni : public Pizza
{
public:
    string getType() override
    {
        return "Pepperoni";
    }
};

// ======================================================
// 3. Factory class → decides which object to create
// ======================================================
class PizzaFactory
{
public:
    static Pizza *createPizza(string type)
    {
        if (type == "Margherita")
        {
            return new Margherita();
        }
        else if (type == "Pepperoni")
        {
            return new Pepperoni();
        }
        else
        {
            return NULL; // invalid type
        }
    }
};

// ======================================================
// 4. Builder class → manages creation process
// ======================================================
class PizzaBuilder
{
private:
    Pizza *pizza; // pointer to store created pizza

public:
    // Constructor → initialize pointer to NULL
    PizzaBuilder()
    {
        pizza = NULL;
    }

    // Create pizza using factory
    void createPizza(string type)
    {
        pizza = PizzaFactory::createPizza(type);
    }

    // Return the created pizza
    Pizza *getPizza()
    {
        return pizza;
    }
};

// ======================================================
// 5. Singleton class → only one instance
// ======================================================
class PizzaSingleton
{
private:
    static PizzaSingleton *instance;

    // Private constructor → cannot create object directly
    PizzaSingleton() {}

public:
    static PizzaSingleton *getInstance()
    {
        if (instance == NULL)
        {
            instance = new PizzaSingleton();
        }
        return instance;
    }
};

// Initialize static variable
PizzaSingleton *PizzaSingleton::instance = NULL;

// ======================================================
// 6. Main function
// ======================================================
int main()
{
    // Create builder object
    PizzaBuilder builder;

    // Ask builder to create pizza
    builder.createPizza("Margherita");

    // Get pizza
    Pizza *pizza = builder.getPizza();

    // Check if pizza is valid
    if (pizza != NULL)
    {
        cout << "Pizza Type: " << pizza->getType() << endl;
    }
    else
    {
        cout << "Invalid Pizza Type" << endl;
    }

    // Use singleton
    PizzaSingleton *singleton = PizzaSingleton::getInstance();

    // Clean up memory (VERY IMPORTANT when using raw pointers)
    delete pizza;

    return 0;
}