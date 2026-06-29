// ============================================================
// 03_smart_pointers.cpp  —  Advanced
// unique_ptr, shared_ptr, weak_ptr — modern memory management
// ============================================================

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// ================================================================
// Helper classes for demonstration
// ================================================================
class Resource
{
    string name;

public:
    Resource(string n) : name(n)
    {
        cout << "[+] Resource '" << name << "' created" << endl;
    }
    ~Resource()
    {
        cout << "[-] Resource '" << name << "' destroyed" << endl;
    }
    void use() const
    {
        cout << "    Using '" << name << "'" << endl;
    }
    string getName() const { return name; }
};

// ================================================================
// 1. unique_ptr — sole ownership, auto-deleted on scope exit
// ================================================================
void demonstrateUniquePtr()
{
    cout << "\n=== unique_ptr ===" << endl;

    {
        unique_ptr<Resource> r = make_unique<Resource>("UniqueOne");
        r->use();

        // Transfer ownership with move
        unique_ptr<Resource> r2 = move(r); // r is now null
        if (!r)
            cout << "    r is now empty (moved away)" << endl;
        r2->use();
    } // r2 goes out of scope → Resource destroyed automatically

    // unique_ptr in a function return
    auto makeResource = []() -> unique_ptr<Resource>
    {
        return make_unique<Resource>("Returned");
    };

    auto res = makeResource();
    res->use();

    // Array of unique_ptrs
    vector<unique_ptr<Resource>> resources;
    resources.push_back(make_unique<Resource>("A"));
    resources.push_back(make_unique<Resource>("B"));
    resources.push_back(make_unique<Resource>("C"));

    for (auto &r : resources)
        r->use();
} // vector destroyed → all Resources destroyed

// ================================================================
// 2. shared_ptr — shared ownership, reference counting
// ================================================================
void demonstrateSharedPtr()
{
    cout << "\n=== shared_ptr ===" << endl;

    shared_ptr<Resource> sp1;

    {
        shared_ptr<Resource> sp2 = make_shared<Resource>("Shared");
        sp1 = sp2; // both sp1 and sp2 now own the resource

        cout << "ref count: " << sp2.use_count() << endl; // 2

        {
            shared_ptr<Resource> sp3 = sp1;
            cout << "ref count: " << sp1.use_count() << endl; // 3
            sp3->use();
        } // sp3 goes away → ref count = 2

        cout << "ref count: " << sp1.use_count() << endl; // 2
    } // sp2 goes away → ref count = 1

    cout << "ref count: " << sp1.use_count() << endl; // 1
    sp1->use();

    sp1.reset(); // manually release
    cout << "sp1 after reset: " << (sp1 ? "valid" : "null") << endl;
    // Resource destroyed here (ref count hits 0)
}

// ================================================================
// 3. weak_ptr — observe shared_ptr without owning
// ================================================================
struct Node
{
    string name;
    shared_ptr<Node> next; // strong ref — owns next node
    weak_ptr<Node> parent; // weak ref — doesn't own parent

    Node(string n) : name(n)
    {
        cout << "[+] Node '" << name << "'" << endl;
    }
    ~Node()
    {
        cout << "[-] Node '" << name << "'" << endl;
    }
};

void demonstrateWeakPtr()
{
    cout << "\n=== weak_ptr (breaking cycles) ===" << endl;

    shared_ptr<Node> parent = make_shared<Node>("parent");
    shared_ptr<Node> child = make_shared<Node>("child");

    parent->next = child;   // parent owns child (shared_ptr)
    child->parent = parent; // child OBSERVES parent (weak_ptr — no cycle!)

    // Access through weak_ptr (lock() to get shared_ptr)
    if (auto p = child->parent.lock())
    {
        cout << "Child's parent: " << p->name << endl;
    }

    cout << "parent ref count: " << parent.use_count() << endl; // 1 (only 'parent' owns it)
    cout << "child ref count:  " << child.use_count() << endl;  // 2 (parent->next and 'child')
} // parent and child destroyed cleanly (no cycle)

// ================================================================
// 4. Custom deleter
// ================================================================
void demonstrateCustomDeleter()
{
    cout << "\n=== Custom Deleter ===" << endl;

    auto deleter = [](Resource *r)
    {
        cout << "Custom cleanup for: " << r->getName() << endl;
        delete r;
    };

    unique_ptr<Resource, decltype(deleter)> r(new Resource("CustomDel"), deleter);
    r->use();
}

// ================================================================
// MAIN
// ================================================================
int main()
{
    demonstrateUniquePtr();
    demonstrateSharedPtr();
    demonstrateWeakPtr();
    demonstrateCustomDeleter();

    cout << "\n=== Smart Pointer Quick Summary ===" << endl;
    cout << "unique_ptr: sole owner, zero overhead, use by default" << endl;
    cout << "shared_ptr: shared ownership, ref-counted, slight overhead" << endl;
    cout << "weak_ptr:   observe shared_ptr without owning, breaks cycles" << endl;

    return 0;
}
