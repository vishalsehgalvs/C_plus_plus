// ============================================================
// 10_exception_handling.cpp  —  Basic
// try/catch, throw, custom exceptions, exception hierarchy
// ============================================================

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// ================================================================
// Custom exception classes
// ================================================================
class AppException : public runtime_error
{
    int errorCode;

public:
    AppException(const string &msg, int code)
        : runtime_error(msg), errorCode(code) {}

    int getCode() const { return errorCode; }
};

class InsufficientFundsException : public AppException
{
    double available;
    double requested;

public:
    InsufficientFundsException(double avail, double req)
        : AppException("Insufficient funds", 1001),
          available(avail), requested(req) {}

    void printDetails() const
    {
        cout << "  Available: $" << available
             << " | Requested: $" << requested << endl;
    }
};

// ================================================================
// Functions that throw exceptions
// ================================================================
double divide(double a, double b)
{
    if (b == 0.0)
    {
        throw runtime_error("Division by zero!");
    }
    return a / b;
}

double withdraw(double balance, double amount)
{
    if (amount <= 0)
    {
        throw invalid_argument("Amount must be positive");
    }
    if (amount > balance)
    {
        throw InsufficientFundsException(balance, amount);
    }
    return balance - amount;
}

int parseInt(const string &s)
{
    try
    {
        return stoi(s); // throws if not a valid int
    }
    catch (const invalid_argument &)
    {
        throw invalid_argument("'" + s + "' is not a valid integer");
    }
    catch (const out_of_range &)
    {
        throw out_of_range("'" + s + "' is out of int range");
    }
}

// ================================================================
// MAIN
// ================================================================
int main()
{
    // ---- Basic try/catch ----
    cout << "=== Division ===" << endl;
    try
    {
        cout << divide(10, 2) << endl; // works: 5
        cout << divide(10, 0) << endl; // throws!
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    // ---- Multiple catch blocks ----
    cout << "\n=== Bank Withdraw ===" << endl;
    double balance = 100.0;

    auto tryWithdraw = [&](double amount)
    {
        try
        {
            balance = withdraw(balance, amount);
            cout << "Withdrew $" << amount << ". Balance: $" << balance << endl;
        }
        catch (const InsufficientFundsException &e)
        {
            cout << "Error [" << e.getCode() << "]: " << e.what() << endl;
            e.printDetails();
        }
        catch (const invalid_argument &e)
        {
            cout << "Invalid: " << e.what() << endl;
        }
    };

    tryWithdraw(30.0);  // success
    tryWithdraw(-5.0);  // invalid argument
    tryWithdraw(200.0); // insufficient funds

    // ---- Catch all exception types ----
    cout << "\n=== Parse Int ===" << endl;
    string inputs[] = {"42", "abc", "99999999999"};
    for (const string &s : inputs)
    {
        try
        {
            int val = parseInt(s);
            cout << "Parsed: " << val << endl;
        }
        catch (const invalid_argument &e)
        {
            cout << "Invalid: " << e.what() << endl;
        }
        catch (const out_of_range &e)
        {
            cout << "Out of range: " << e.what() << endl;
        }
    }

    // ---- finally equivalent (RAII) ----
    cout << "\n=== Cleanup (RAII pattern) ===" << endl;
    {
        // In C++, use destructors instead of finally
        // The destructor ALWAYS runs, even on exception
        class Resource
        {
        public:
            Resource() { cout << "[Resource] Acquired" << endl; }
            ~Resource() { cout << "[Resource] Released (always!)" << endl; }
        };

        try
        {
            Resource r; // constructor called
            throw runtime_error("Something went wrong!");
        }
        catch (const exception &e)
        {
            cout << "Caught: " << e.what() << endl;
        }
        // r's destructor still called, even though exception was thrown!
    }

    // ---- Rethrowing ----
    cout << "\n=== Rethrow ===" << endl;
    try
    {
        try
        {
            throw runtime_error("Original error");
        }
        catch (const exception &e)
        {
            cout << "Inner catch: " << e.what() << endl;
            throw; // rethrow the same exception
        }
    }
    catch (const exception &e)
    {
        cout << "Outer catch: " << e.what() << endl;
    }

    // ---- Catch(...) — catch absolutely anything ----
    cout << "\n=== Catch All ===" << endl;
    try
    {
        throw 42; // throwing an int (unusual but valid)
    }
    catch (...)
    {
        cout << "Caught something (don't know what)" << endl;
    }

    return 0;
}
