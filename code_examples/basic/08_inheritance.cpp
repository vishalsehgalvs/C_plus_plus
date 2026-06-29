// ============================================================
// 08_inheritance.cpp  —  Basic
// Inheritance, virtual functions, polymorphism, override
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// ================================================================
// Base class
// ================================================================
class Animal
{
protected:
    string name;
    int age;

public:
    Animal(string name, int age) : name(name), age(age) {}

    // Virtual function — can be overridden by derived classes
    virtual void speak()
    {
        cout << name << " makes a generic animal sound." << endl;
    }

    // Pure virtual — MUST be overridden (makes Animal abstract)
    virtual void describe() = 0;

    // Non-virtual — inherited as-is
    void eat()
    {
        cout << name << " is eating." << endl;
    }

    string getName() const { return name; }

    virtual ~Animal() {} // always virtual destructor in base!
};

// ================================================================
// Derived classes
// ================================================================
class Dog : public Animal
{
    string breed;

public:
    Dog(string name, int age, string breed)
        : Animal(name, age), breed(breed) {}

    void speak() override
    { // 'override' keyword catches typos!
        cout << name << " barks: Woof! Woof!" << endl;
    }

    void describe() override
    {
        cout << "Dog: " << name << " | Age: " << age
             << " | Breed: " << breed << endl;
    }

    void fetch()
    {
        cout << name << " fetches the ball!" << endl;
    }
};

class Cat : public Animal
{
    bool isIndoor;

public:
    Cat(string name, int age, bool indoor)
        : Animal(name, age), isIndoor(indoor) {}

    void speak() override
    {
        cout << name << " meows: Meow~" << endl;
    }

    void describe() override
    {
        cout << "Cat: " << name << " | Age: " << age
             << " | " << (isIndoor ? "Indoor" : "Outdoor") << endl;
    }
};

class Bird : public Animal
{
    bool canFly;

public:
    Bird(string name, int age, bool flies)
        : Animal(name, age), canFly(flies) {}

    void speak() override
    {
        cout << name << " chirps: Tweet!" << endl;
    }

    void describe() override
    {
        cout << "Bird: " << name << " | Age: " << age
             << " | " << (canFly ? "Can fly" : "Cannot fly") << endl;
    }
};

// ================================================================
// Multilevel Inheritance
// ================================================================
class Vehicle
{
public:
    virtual void start()
    {
        cout << "Vehicle starting..." << endl;
    }
    virtual ~Vehicle() {}
};

class Car : public Vehicle
{
public:
    void start() override
    {
        cout << "Car starting with key..." << endl;
    }
};

class ElectricCar : public Car
{
public:
    void start() override
    {
        cout << "Electric car starting silently..." << endl;
    }

    void charge()
    {
        cout << "Electric car charging..." << endl;
    }
};

// ================================================================
// MAIN — Polymorphism in action
// ================================================================
int main()
{
    // Polymorphism: base class pointer can hold any derived type
    cout << "=== Animal Polymorphism ===" << endl;

    vector<unique_ptr<Animal>> zoo;
    zoo.push_back(make_unique<Dog>("Rex", 3, "German Shepherd"));
    zoo.push_back(make_unique<Cat>("Luna", 2, true));
    zoo.push_back(make_unique<Bird>("Tweety", 1, true));
    zoo.push_back(make_unique<Dog>("Buddy", 5, "Labrador"));

    // Same code works for all animal types!
    for (auto &animal : zoo)
    {
        animal->describe(); // correct describe() called per type
        animal->speak();    // correct speak() called per type
        animal->eat();      // inherited from Animal — same for all
        cout << endl;
    }

    // Access derived-class-specific method (need downcast)
    cout << "=== Downcasting ===" << endl;
    Animal *a = new Dog("Max", 2, "Poodle");

    // dynamic_cast — safe
    Dog *d = dynamic_cast<Dog *>(a);
    if (d)
    {
        d->fetch(); // Dog-specific method
    }

    delete a;

    // Multilevel inheritance
    cout << "\n=== Multilevel Inheritance ===" << endl;
    Vehicle *v1 = new Car();
    Vehicle *v2 = new ElectricCar();

    v1->start(); // Car's start()
    v2->start(); // ElectricCar's start()

    // Can access ElectricCar methods after downcast
    ElectricCar *ec = dynamic_cast<ElectricCar *>(v2);
    if (ec)
        ec->charge();

    delete v1;
    delete v2;

    return 0;
}
