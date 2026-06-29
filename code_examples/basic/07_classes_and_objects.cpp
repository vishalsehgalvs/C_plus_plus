// ============================================================
// 07_classes_and_objects.cpp  —  Basic
// Classes, constructors, destructors, encapsulation, this
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ================================================================
// 1. Basic Class
// ================================================================
class BankAccount
{
private:
    string owner;
    double balance;
    int accountNumber;

    static int nextAccountNumber; // shared by all instances

public:
    // Constructor
    BankAccount(string name, double initialBalance)
    {
        owner = name;
        balance = initialBalance;
        accountNumber = ++nextAccountNumber;
        cout << "[Account] Created account #" << accountNumber
             << " for " << owner << endl;
    }

    // Constructor using initializer list (preferred)
    // BankAccount(string name, double bal) : owner(name), balance(bal) {}

    // Destructor
    ~BankAccount()
    {
        cout << "[Account] Closing account #" << accountNumber
             << " for " << owner << endl;
    }

    // Methods
    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Deposited $" << amount << ". Balance: $" << balance << endl;
        }
    }

    bool withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "Withdrew $" << amount << ". Balance: $" << balance << endl;
            return true;
        }
        cout << "Insufficient funds." << endl;
        return false;
    }

    // Getters (read-only access to private data)
    double getBalance() const { return balance; }
    string getOwner() const { return owner; }
    int getAccountNumber() const { return accountNumber; }

    // Display info
    void display() const
    {
        cout << "Account #" << accountNumber
             << " | Owner: " << owner
             << " | Balance: $" << balance << endl;
    }
};

// Initialize static member
int BankAccount::nextAccountNumber = 1000;

// ================================================================
// 2. Class with Copy Constructor
// ================================================================
class Student
{
    string name;
    int *grades; // pointer — needs custom copy
    int count;

public:
    Student(string n, int numGrades) : name(n), count(numGrades)
    {
        grades = new int[count];
        for (int i = 0; i < count; i++)
            grades[i] = 0;
    }

    // Copy constructor (deep copy!)
    Student(const Student &other) : name(other.name), count(other.count)
    {
        grades = new int[count];
        for (int i = 0; i < count; i++)
            grades[i] = other.grades[i];
        cout << "[Copy constructor] " << name << " copied" << endl;
    }

    void setGrade(int index, int value)
    {
        if (index >= 0 && index < count)
            grades[index] = value;
    }

    void display() const
    {
        cout << name << "'s grades: ";
        for (int i = 0; i < count; i++)
            cout << grades[i] << " ";
        cout << endl;
    }

    ~Student() { delete[] grades; }
};

// ================================================================
// 3. 'this' pointer
// ================================================================
class Counter
{
    int count;

public:
    Counter(int start = 0) : count(start) {}

    Counter &increment()
    {
        count++;
        return *this; // return reference to self (enables chaining)
    }

    Counter &add(int n)
    {
        count += n;
        return *this;
    }

    void display() const { cout << "Counter: " << count << endl; }
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    cout << "=== Bank Account ===" << endl;
    {
        BankAccount acc1("Alice", 1000.0);
        BankAccount acc2("Bob", 500.0);

        acc1.display();
        acc2.display();

        acc1.deposit(250.0);
        acc1.withdraw(100.0);
        acc2.withdraw(600.0); // should fail

        cout << "Alice's balance: $" << acc1.getBalance() << endl;
    }
    // Destructors called here when scope ends

    cout << "\n=== Student Copy ===" << endl;
    {
        Student s1("Alice", 3);
        s1.setGrade(0, 90);
        s1.setGrade(1, 85);
        s1.setGrade(2, 92);
        s1.display();

        Student s2 = s1;    // calls copy constructor (deep copy)
        s2.setGrade(0, 70); // only changes s2, not s1
        s2.display();
        s1.display(); // s1 unchanged
    }

    cout << "\n=== Method Chaining ===" << endl;
    Counter c(0);
    c.increment().increment().increment().add(10).display();
    // Output: Counter: 13

    return 0;
}
