// ============================================================
// 04_functions.cpp  —  Basic
// Functions: definition, parameters, return values,
// default arguments, overloading, recursion
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ================================================================
// 1. Basic function — no return value
// ================================================================
void greet(string name)
{
    cout << "Hello, " << name << "!" << endl;
}

// ================================================================
// 2. Function with return value
// ================================================================
int add(int a, int b)
{
    return a + b;
}

double circleArea(double radius)
{
    const double PI = 3.14159;
    return PI * radius * radius;
}

// ================================================================
// 3. Default arguments (must be at the END)
// ================================================================
void printInfo(string name, int age = 18, string country = "India")
{
    cout << name << " | Age: " << age << " | From: " << country << endl;
}

// ================================================================
// 4. Function Overloading — same name, different parameters
// ================================================================
int multiply(int a, int b) { return a * b; }
double multiply(double a, double b) { return a * b; }
int multiply(int a, int b, int c) { return a * b * c; }

// ================================================================
// 5. Pass by value vs pass by reference
// ================================================================
void modifyValue(int x)
{
    x = 999; // only modifies local copy
}

void modifyRef(int &x)
{
    x = 999; // modifies the original!
}

// ================================================================
// 6. Recursion — function calling itself
// ================================================================
int factorial(int n)
{
    if (n <= 1)
        return 1;                // base case
    return n * factorial(n - 1); // recursive case
}

int fibonacci(int n)
{
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// ================================================================
// 7. Inline function — hint to expand at call site
// ================================================================
inline int square(int x)
{
    return x * x;
}

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Basic function calls
    greet("Alice");
    greet("Bob");

    cout << "\nadd(3, 4) = " << add(3, 4) << endl;
    cout << "circleArea(5) = " << circleArea(5.0) << endl;

    // Default arguments
    cout << "\n--- Default Args ---" << endl;
    printInfo("Alice", 25, "Canada");
    printInfo("Bob", 30); // uses default country = "India"
    printInfo("Charlie"); // uses both defaults

    // Overloading
    cout << "\n--- Overloading ---" << endl;
    cout << multiply(3, 4) << endl;     // int version
    cout << multiply(2.5, 3.0) << endl; // double version
    cout << multiply(2, 3, 4) << endl;  // 3-arg version

    // Pass by value vs reference
    cout << "\n--- Pass by Value/Reference ---" << endl;
    int val = 10;
    modifyValue(val);
    cout << "After modifyValue: " << val << endl; // still 10

    modifyRef(val);
    cout << "After modifyRef:   " << val << endl; // now 999

    // Recursion
    cout << "\n--- Recursion ---" << endl;
    cout << "5! = " << factorial(5) << endl;       // 120
    cout << "fib(10) = " << fibonacci(10) << endl; // 55

    // Inline
    cout << "\nsquare(7) = " << square(7) << endl; // 49

    return 0;
}

/*
Expected Output:
Hello, Alice!
Hello, Bob!

add(3, 4) = 7
circleArea(5) = 78.5397

--- Default Args ---
Alice | Age: 25 | From: Canada
Bob | Age: 30 | From: India
Charlie | Age: 18 | From: India

--- Overloading ---
12
7.5
24

--- Pass by Value/Reference ---
After modifyValue: 10
After modifyRef:   999

--- Recursion ---
5! = 120
fib(10) = 55

square(7) = 49
*/
