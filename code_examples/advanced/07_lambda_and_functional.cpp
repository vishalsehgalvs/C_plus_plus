// ============================================================
// 07_lambda_and_functional.cpp  —  Advanced
// Lambdas, std::function, std::bind, higher-order functions
// ============================================================

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

// ================================================================
// 1. Lambda basics
// ================================================================
//   [capture](params) -> return_type { body }
//   [=]  capture all by value
//   [&]  capture all by reference
//   [x]  capture x by value
//   [&x] capture x by reference
//   []   capture nothing

// ================================================================
// 2. std::function — store any callable
// ================================================================
int applyOperation(int a, int b, function<int(int, int)> op)
{
    return op(a, b);
}

// ================================================================
// 3. Higher-order functions using lambdas
// ================================================================
template <typename T, typename Pred>
vector<T> filter(const vector<T> &v, Pred pred)
{
    vector<T> result;
    copy_if(v.begin(), v.end(), back_inserter(result), pred);
    return result;
}

template <typename T, typename F>
vector<T> mapVec(const vector<T> &v, F func)
{
    vector<T> result;
    transform(v.begin(), v.end(), back_inserter(result), func);
    return result;
}

template <typename T, typename Acc, typename F>
Acc reduce(const vector<T> &v, Acc init, F func)
{
    return accumulate(v.begin(), v.end(), init, func);
}

// ================================================================
// 4. Closure — lambda that captures local state
// ================================================================
function<int()> makeCounter(int start = 0)
{
    int count = start;         // captured by value
    return [count]() mutable { // mutable: allows modifying captured copy
        return count++;
    };
}

function<int(int)> makeMultiplier(int factor)
{
    return [factor](int x)
    { return x * factor; };
}

// ================================================================
// 5. Composing functions
// ================================================================
function<int(int)> compose(function<int(int)> f, function<int(int)> g)
{
    return [f, g](int x)
    { return f(g(x)); }; // f(g(x))
}

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Basic lambdas
    cout << "=== Basic Lambdas ===" << endl;

    auto add = [](int a, int b)
    { return a + b; };
    auto greet = [](string name)
    { cout << "Hello, " << name << "!" << endl; };

    cout << add(3, 4) << endl;
    greet("World");

    // Capture
    int multiplier = 3;
    auto times3 = [multiplier](int x)
    { return x * multiplier; }; // capture by value
    auto times3ref = [&multiplier](int x)
    { return x * multiplier; }; // capture by ref

    cout << times3(5) << endl; // 15
    multiplier = 10;
    cout << times3(5) << endl;    // still 15 (captured by VALUE before change)
    cout << times3ref(5) << endl; // 50 (captured by REFERENCE — sees new value)

    // Mutable lambda
    auto counter = [count = 0]() mutable
    { return ++count; };
    cout << counter() << counter() << counter() << endl; // 1 2 3

    // std::function
    cout << "\n=== std::function ===" << endl;
    cout << applyOperation(10, 3, add) << endl; // 13
    cout << applyOperation(10, 3, [](int a, int b)
                           { return a - b; })
         << endl; // 7
    cout << applyOperation(10, 3, [](int a, int b)
                           { return a * b; })
         << endl; // 30

    // std::bind — bind arguments to a function
    auto addTen = bind(add, placeholders::_1, 10); // first arg is placeholder, second is 10
    cout << addTen(5) << endl;                     // 15
    cout << addTen(20) << endl;                    // 30

    // Higher-order functions
    cout << "\n=== Filter / Map / Reduce ===" << endl;
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto evens = filter(nums, [](int x)
                        { return x % 2 == 0; });
    auto doubled = mapVec(nums, [](int x)
                          { return x * 2; });
    auto total = reduce(nums, 0, [](int acc, int x)
                        { return acc + x; });

    cout << "Evens:   ";
    for (int x : evens)
        cout << x << " ";
    cout << endl;
    cout << "Doubled: ";
    for (int x : doubled)
        cout << x << " ";
    cout << endl;
    cout << "Total:   " << total << endl;

    // Closures
    cout << "\n=== Closures ===" << endl;
    auto c1 = makeCounter(0);
    auto c2 = makeCounter(100); // independent counter

    cout << c1() << " " << c1() << " " << c1() << endl; // 0 1 2
    cout << c2() << " " << c2() << endl;                // 100 101
    cout << c1() << endl;                               // 3 (independent)

    auto triple = makeMultiplier(3);
    auto quadruple = makeMultiplier(4);
    cout << triple(5) << " " << quadruple(5) << endl; // 15 20

    // Function composition
    cout << "\n=== Composition ===" << endl;
    auto squareThenDouble = compose([](int x)
                                    { return x * 2; },
                                    [](int x)
                                    { return x * x; });
    cout << squareThenDouble(3) << endl; // (3*3)*2 = 18
    cout << squareThenDouble(5) << endl; // (5*5)*2 = 50

    // Lambda in STL algorithms
    cout << "\n=== Lambdas in STL ===" << endl;
    vector<string> words = {"banana", "apple", "cherry", "date"};
    sort(words.begin(), words.end(), [](const string &a, const string &b)
         {
             return a.length() < b.length(); // sort by length
         });
    for (const string &w : words)
        cout << w << " ";
    cout << endl;

    return 0;
}
