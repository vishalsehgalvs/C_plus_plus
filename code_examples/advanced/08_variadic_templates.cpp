// ============================================================
// 08_variadic_templates.cpp  —  Advanced
// Variadic templates, fold expressions (C++17), tuple tricks
// ============================================================

#include <iostream>
#include <string>
#include <tuple>
#include <sstream>
using namespace std;

// ================================================================
// 1. Variadic function template
// ================================================================
// Base case (0 args)
void printAll() { cout << endl; }

// Recursive variadic
template <typename First, typename... Rest>
void printAll(First first, Rest... rest)
{
    cout << first;
    if constexpr (sizeof...(rest) > 0)
        cout << ", ";
    printAll(rest...);
}

// ================================================================
// 2. Fold expressions (C++17) — cleaner than recursion
// ================================================================
// Unary right fold: (args op ...)
// Unary left fold:  (... op args)
// Binary fold:      (init op ... op args)

template <typename... Args>
auto sum(Args... args)
{
    return (args + ...); // fold expression — no recursion needed!
}

template <typename... Args>
auto product(Args... args)
{
    return (args * ...);
}

template <typename... Args>
bool allTrue(Args... args)
{
    return (args && ...);
}

template <typename... Args>
bool anyTrue(Args... args)
{
    return (args || ...);
}

// Print with separator using fold
template <typename... Args>
void printSep(const string &sep, Args... args)
{
    bool first = true;
    ([&](auto &arg)
     {
        if (!first) cout << sep;
        cout << arg;
        first = false; }(args), ...); // comma fold expression (C++17)
    cout << endl;
}

// ================================================================
// 3. Variadic class template
// ================================================================
// Build a type-safe tuple-like store
template <typename... Types>
class TypeList
{
public:
    static constexpr size_t size = sizeof...(Types);

    // Apply a function to a std::tuple of the types
    static void describe()
    {
        cout << "TypeList with " << size << " types:" << endl;
        // Print each type name (simplified)
        ([]
         { cout << "  - " << typeid(Types).name() << endl; }(), ...);
    }
};

// ================================================================
// 4. Perfect forwarding with variadic args
// ================================================================
template <typename T, typename... Args>
T *createObject(Args &&...args)
{
    return new T(forward<Args>(args)...);
}

struct Point
{
    double x, y, z;
    Point(double x, double y, double z = 0) : x(x), y(y), z(z)
    {
        cout << "Point(" << x << "," << y << "," << z << ")" << endl;
    }
};

// ================================================================
// 5. String joining with variadic
// ================================================================
template <typename... Args>
string joinStrings(const string &sep, Args... args)
{
    ostringstream oss;
    bool first = true;
    ([&](const auto &arg)
     {
        if (!first) oss << sep;
        oss << arg;
        first = false; }(args), ...);
    return oss.str();
}

// ================================================================
// 6. Counting and applying predicates
// ================================================================
template <typename Pred, typename... Args>
int countIf(Pred pred, Args... args)
{
    return (0 + ... + (pred(args) ? 1 : 0));
}

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Variadic print
    cout << "=== printAll ===" << endl;
    printAll(1, "hello", 3.14, true);

    // Fold expressions
    cout << "\n=== Fold Expressions ===" << endl;
    cout << "sum(1,2,3,4,5)      = " << sum(1, 2, 3, 4, 5) << endl;
    cout << "product(1,2,3,4,5)  = " << product(1, 2, 3, 4, 5) << endl;
    cout << "allTrue(true,true)  = " << allTrue(true, true, true) << endl;
    cout << "allTrue(true,false) = " << allTrue(true, false, true) << endl;
    cout << "anyTrue(false,true) = " << anyTrue(false, true, false) << endl;

    cout << "\n=== Print with Separator ===" << endl;
    printSep(" | ", "Alice", 25, "Canada");
    printSep(", ", 1, 2, 3, 4, 5);

    // TypeList
    cout << "\n=== TypeList ===" << endl;
    TypeList<int, double, string, bool>::describe();

    // Perfect forwarding factory
    cout << "\n=== createObject ===" << endl;
    Point *p1 = createObject<Point>(1.0, 2.0);
    Point *p2 = createObject<Point>(3.0, 4.0, 5.0);
    delete p1;
    delete p2;

    // joinStrings
    cout << "\n=== joinStrings ===" << endl;
    cout << joinStrings(", ", "one", "two", "three") << endl;
    cout << joinStrings(" - ", 10, 20, 30) << endl;

    // countIf
    cout << "\n=== countIf ===" << endl;
    auto isEven = [](int x)
    { return x % 2 == 0; };
    cout << "Even count in (1,2,3,4,5,6): "
         << countIf(isEven, 1, 2, 3, 4, 5, 6) << endl; // 3

    return 0;
}
