// ============================================================
// 04_move_semantics.cpp  —  Advanced
// Move constructor, rvalue references, perfect forwarding,
// std::move, return value optimization
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <utility> // std::move, std::forward
using namespace std;

// ================================================================
// 1. Understanding lvalues and rvalues
// ================================================================
// lvalue  = has a name, lives in memory, can be on left of =
// rvalue  = temporary, no name, can only be on right of =
//
//   int x = 5;
//   ^lvalue    ^rvalue (literal)
//
//   string s = string("hello");
//   ^lvalue    ^rvalue (temporary)
//
//   int& ref = x;         // lvalue reference
//   int&& rref = 42;      // rvalue reference (binds to temp)

// ================================================================
// 2. A class that demonstrates copy vs move
// ================================================================
class BigData
{
    string name;
    int *data;
    size_t size;

public:
    // Constructor
    BigData(string n, size_t sz) : name(n), size(sz)
    {
        data = new int[size];
        for (size_t i = 0; i < size; i++)
            data[i] = i * 2;
        cout << "  [CONSTRUCT] " << name << " (size=" << size << ")" << endl;
    }

    // Copy constructor — deep copy (expensive for large data!)
    BigData(const BigData &other) : name(other.name + "_copy"), size(other.size)
    {
        data = new int[size];
        copy(other.data, other.data + size, data);
        cout << "  [COPY]      " << name << " ← deep copied from " << other.name << endl;
    }

    // Move constructor — steal the resources (cheap!)
    BigData(BigData &&other) noexcept
        : name(move(other.name)), size(other.size), data(other.data)
    {
        other.data = nullptr; // leave other in valid but empty state
        other.size = 0;
        cout << "  [MOVE]      " << name << " ← moved (no copy)" << endl;
    }

    // Copy assignment
    BigData &operator=(const BigData &other)
    {
        if (this != &other)
        {
            delete[] data;
            size = other.size;
            name = other.name + "_assigned";
            data = new int[size];
            copy(other.data, other.data + size, data);
            cout << "  [COPY=]     " << name << endl;
        }
        return *this;
    }

    // Move assignment
    BigData &operator=(BigData &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            name = move(other.name);
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
            cout << "  [MOVE=]     " << name << endl;
        }
        return *this;
    }

    ~BigData()
    {
        cout << "  [DESTROY]   " << name << endl;
        delete[] data;
    }

    size_t getSize() const { return size; }
    string getName() const { return name; }
};

// ================================================================
// 3. Function that benefits from move semantics
// ================================================================
void processData(BigData data)
{ // takes by value — allows move
    cout << "  Processing: " << data.getName() << " (size=" << data.getSize() << ")" << endl;
}

// ================================================================
// 4. Perfect Forwarding — pass arguments through without copying
// ================================================================
template <typename T, typename... Args>
T make(Args &&...args)
{
    return T(forward<Args>(args)...); // forward preserves lvalue/rvalue nature
}

// ================================================================
// 5. Return Value Optimization (RVO)
// ================================================================
BigData createData(string name, int size)
{
    return BigData(name, size); // RVO: compiler may skip the copy entirely
}

// ================================================================
// MAIN
// ================================================================
int main()
{
    cout << "=== Copy vs Move ===" << endl;
    {
        BigData original("original", 5);

        cout << "\n-- Copy --" << endl;
        BigData copied = original; // copy constructor

        cout << "\n-- Move --" << endl;
        BigData moved = move(original);                                     // move constructor — no deep copy!
        cout << "original size after move: " << original.getSize() << endl; // 0
    }

    cout << "\n=== Passing to Function ===" << endl;
    {
        BigData d("data1", 3);

        cout << "\n-- Pass lvalue (copy) --" << endl;
        processData(d); // copies d

        cout << "\n-- Pass rvalue (move) --" << endl;
        processData(move(d)); // moves d — d is now empty

        cout << "\n-- Pass temporary (move) --" << endl;
        processData(BigData("temp", 3)); // temporary → move
    }

    cout << "\n=== RVO: Return Value Optimization ===" << endl;
    {
        BigData result = createData("result", 4); // often NO copy at all
        cout << "Got: " << result.getName() << endl;
    }

    cout << "\n=== Vector of BigData ===" << endl;
    {
        vector<BigData> vec;
        vec.reserve(3); // reserve to avoid reallocation (avoids extra moves)

        vec.emplace_back("item1", 2); // emplace_back constructs in-place (no copy/move)
        vec.emplace_back("item2", 2);

        BigData item3("item3", 2);
        vec.push_back(move(item3)); // move into vector
    }

    return 0;
}
