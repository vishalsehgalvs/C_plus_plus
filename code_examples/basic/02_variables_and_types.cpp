// ============================================================
// 02_variables_and_types.cpp  —  Basic
// Variables, data types, constants, and type conversions
// ============================================================

#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main()
{
    // ---- Integer Types ----
    int age = 25;
    short s = 100;
    long l = 1000000L;
    long long ll = 9000000000LL;

    cout << "int:       " << age << endl;
    cout << "short:     " << s << endl;
    cout << "long:      " << l << endl;
    cout << "long long: " << ll << endl;

    // ---- Floating Point ----
    float pi_f = 3.14f;          // 32-bit, ~7 decimal places
    double pi_d = 3.14159265358; // 64-bit, ~15 decimal places

    cout << "\nfloat:  " << pi_f << endl;
    cout << "double: " << pi_d << endl;

    // ---- Characters and Booleans ----
    char letter = 'A';
    bool isReady = true;

    cout << "\nchar: " << letter << " (ASCII: " << (int)letter << ")" << endl;
    cout << "bool: " << isReady << " (1=true, 0=false)" << endl;

    // ---- Strings ----
    string name = "Alice";
    string greeting = "Hello, " + name + "!"; // string concatenation

    cout << "\nstring: " << name << endl;
    cout << "concat: " << greeting << endl;
    cout << "length: " << name.length() << " characters" << endl;

    // ---- Constants ----
    const double GRAVITY = 9.81; // can't change after assignment
    // GRAVITY = 10.0;             // ERROR: assignment to const

    constexpr int MAX = 100; // evaluated at compile time (C++11)
    cout << "\nGRAVITY = " << GRAVITY << endl;
    cout << "MAX     = " << MAX << endl;

    // ---- Auto (type deduction) ----
    auto x = 42;                 // int
    auto y = 3.14;               // double
    auto flag = false;           // bool
    auto word = string("hello"); // string

    cout << "\nauto x    = " << x << endl;
    cout << "auto y    = " << y << endl;
    cout << "auto flag = " << flag << endl;
    cout << "auto word = " << word << endl;

    // ---- Type Limits ----
    cout << "\nMax int:    " << numeric_limits<int>::max() << endl;
    cout << "Min int:    " << numeric_limits<int>::min() << endl;
    cout << "Max double: " << numeric_limits<double>::max() << endl;

    // ---- Type Conversion ----
    int intVal = 10;
    double doubleVal = intVal;           // implicit: int → double (safe)
    int truncated = (int)3.99;           // explicit: double → int (loses .99)
    int modern = static_cast<int>(3.99); // modern C++ cast

    cout << "\nImplicit int→double: " << doubleVal << endl;
    cout << "C-style truncation:  " << truncated << " (was 3.99)" << endl;
    cout << "static_cast:         " << modern << " (was 3.99)" << endl;

    // ---- Multiple Assignments ----
    int a, b, c;
    a = b = c = 5; // chained assignment
    cout << "\na=" << a << " b=" << b << " c=" << c << endl;

    return 0;
}
