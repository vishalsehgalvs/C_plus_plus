// ============================================================
// 01_templates.cpp  —  Advanced
// Function templates, class templates, template specialization,
// SFINAE, concepts (C++20)
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// ================================================================
// 1. Function Templates
// ================================================================
template <typename T>
T maxOf(T a, T b)
{
    return (a > b) ? a : b;
}

// Multiple type parameters
template <typename T, typename U>
auto addMixed(T a, U b) -> decltype(a + b)
{
    return a + b;
}

// ================================================================
// 2. Template Specialization — different behavior for specific types
// ================================================================
template <typename T>
string describe(T val)
{
    return "Value: " + to_string(val);
}

// Full specialization for string
template <>
string describe<string>(string val)
{
    return "String: \"" + val + "\" (len=" + to_string(val.size()) + ")";
}

// Full specialization for bool
template <>
string describe<bool>(bool val)
{
    return string("Bool: ") + (val ? "true" : "false");
}

// ================================================================
// 3. Class Template — Stack
// ================================================================
template <typename T, int MaxSize = 100>
class Stack
{
    T data[MaxSize];
    int topIndex = -1;

public:
    void push(const T &val)
    {
        if (topIndex >= MaxSize - 1)
            throw overflow_error("Stack is full");
        data[++topIndex] = val;
    }

    T pop()
    {
        if (topIndex < 0)
            throw underflow_error("Stack is empty");
        return data[topIndex--];
    }

    T &top()
    {
        if (topIndex < 0)
            throw underflow_error("Stack is empty");
        return data[topIndex];
    }

    bool empty() const { return topIndex < 0; }
    int size() const { return topIndex + 1; }
};

// ================================================================
// 4. Template with type constraints (C++20 Concepts)
// ================================================================
// Without concepts (C++17 way using enable_if):
template <typename T>
typename enable_if<is_arithmetic<T>::value, T>::type
sumArray(T *arr, int n)
{
    T total = 0;
    for (int i = 0; i < n; i++)
        total += arr[i];
    return total;
}

// ================================================================
// 5. Variadic Templates (arbitrary number of arguments)
// ================================================================
// Base case
void print()
{
    cout << endl;
}

// Recursive variadic template
template <typename First, typename... Rest>
void print(First first, Rest... rest)
{
    cout << first;
    if (sizeof...(rest) > 0)
        cout << ", ";
    print(rest...);
}

// Variadic sum
template <typename T>
T sum(T t) { return t; }

template <typename T, typename... Args>
T sum(T first, Args... args)
{
    return first + sum(args...);
}

// ================================================================
// 6. Template Metaprogramming — Fibonacci at compile time
// ================================================================
template <int N>
struct Fibonacci
{
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
struct Fibonacci<0>
{
    static constexpr int value = 0;
};

template <>
struct Fibonacci<1>
{
    static constexpr int value = 1;
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Function templates
    cout << "=== Function Templates ===" << endl;
    cout << maxOf(10, 20) << endl;                       // int version
    cout << maxOf(3.14, 2.71) << endl;                   // double version
    cout << maxOf(string("abc"), string("xyz")) << endl; // string version

    cout << addMixed(10, 3.14) << endl; // int + double = double

    // Template specialization
    cout << "\n=== Specializations ===" << endl;
    cout << describe(42) << endl;
    cout << describe(3.14) << endl;
    cout << describe(string("Hi")) << endl;
    cout << describe(true) << endl;

    // Class template: Stack
    cout << "\n=== Stack<int> ===" << endl;
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    cout << "Size: " << intStack.size() << endl;
    while (!intStack.empty())
    {
        cout << intStack.pop() << " ";
    }
    cout << endl;

    Stack<string> strStack;
    strStack.push("hello");
    strStack.push("world");
    cout << "Top: " << strStack.top() << endl;

    // sumArray
    cout << "\n=== sumArray ===" << endl;
    int nums[] = {1, 2, 3, 4, 5};
    cout << "Sum: " << sumArray(nums, 5) << endl; // 15

    double dNums[] = {1.1, 2.2, 3.3};
    cout << "Sum: " << sumArray(dNums, 3) << endl; // 6.6

    // Variadic templates
    cout << "\n=== Variadic ===" << endl;
    print(1, "hello", 3.14, true);
    cout << "sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << endl;

    // Compile-time Fibonacci
    cout << "\n=== Compile-time Fibonacci ===" << endl;
    cout << "Fib(0)  = " << Fibonacci<0>::value << endl;
    cout << "Fib(10) = " << Fibonacci<10>::value << endl;
    cout << "Fib(15) = " << Fibonacci<15>::value << endl;
    // These are computed at compile time — zero runtime cost!

    return 0;
}
