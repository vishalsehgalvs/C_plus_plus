// ============================================================
// 06_pointers.cpp  —  Basic
// Pointers, references, pointer arithmetic, dynamic memory
// ============================================================

#include <iostream>
using namespace std;

int main()
{
    // ================================================================
    // 1. Basic Pointers
    // ================================================================
    int x = 42;
    int *ptr = &x; // ptr stores the ADDRESS of x

    cout << "Value of x:       " << x << endl;     // 42
    cout << "Address of x (&x):" << &x << endl;    // some address like 0x7fff...
    cout << "ptr (address):    " << ptr << endl;   // same address
    cout << "*ptr (dereference):" << *ptr << endl; // 42 — the VALUE at that address

    // Modify x through the pointer
    *ptr = 100;
    cout << "x after *ptr=100: " << x << endl; // 100

    // ================================================================
    // 2. Pointer to Pointer
    // ================================================================
    int **pptr = &ptr;                       // pointer to pointer to int
    cout << "\n**pptr = " << **pptr << endl; // 100

    // ================================================================
    // 3. References (aliases for variables)
    // ================================================================
    int num = 10;
    int &ref = num; // ref is another name for num

    ref = 50;
    cout << "\nnum after ref=50: " << num << endl; // 50

    // Pointer vs Reference:
    // - Reference: always valid, can't be null, can't change what it refers to
    // - Pointer: can be null, can point to different things

    // ================================================================
    // 4. Null Pointer
    // ================================================================
    int *nullPtr = nullptr; // C++11 — preferred
    // int* oldNull = NULL;   // old C style

    if (nullPtr == nullptr)
    {
        cout << "\nnullPtr is null — safe check!" << endl;
    }
    // NEVER dereference a null pointer — it crashes!
    // cout << *nullPtr;  // CRASH: segfault!

    // ================================================================
    // 5. Pointer Arithmetic
    // ================================================================
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr; // p points to first element

    cout << "\nPointer arithmetic:" << endl;
    cout << "*p     = " << *p << endl;       // 10
    cout << "*(p+1) = " << *(p + 1) << endl; // 20
    cout << "*(p+2) = " << *(p + 2) << endl; // 30

    p++;                                     // move to next element
    cout << "*p after p++ = " << *p << endl; // 20

    // ================================================================
    // 6. Dynamic Memory — new and delete
    // ================================================================
    // Allocate a single int on the heap
    int *heapInt = new int(99);
    cout << "\nHeap int: " << *heapInt << endl; // 99
    delete heapInt;                             // MUST free memory!
    heapInt = nullptr;                          // good practice

    // Allocate an array on the heap
    int size = 5;
    int *heapArr = new int[size];
    for (int i = 0; i < size; i++)
    {
        heapArr[i] = (i + 1) * 10;
    }
    cout << "Heap array: ";
    for (int i = 0; i < size; i++)
    {
        cout << heapArr[i] << " ";
    }
    cout << endl;
    delete[] heapArr; // MUST use delete[] for arrays!
    heapArr = nullptr;

    // ================================================================
    // 7. const with Pointers
    // ================================================================
    int val = 42;
    int other = 99;

    // Pointer to const: can't change the value through the pointer
    const int *pConst = &val;
    // *pConst = 50;  // ERROR
    pConst = &other; // OK: can change what the pointer points to

    // Const pointer: can't change what it points to
    int *const constPtr = &val;
    *constPtr = 50; // OK: can change the value
    // constPtr = &other;  // ERROR: can't change the pointer itself

    // Const pointer to const: can't change either
    const int *const bothConst = &val;
    // *bothConst = 50;    // ERROR
    // bothConst = &other; // ERROR

    cout << "\nAfter *constPtr=50, val = " << val << endl; // 50

    // ================================================================
    // 8. Passing Pointers to Functions
    // ================================================================
    auto swap = [](int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    };

    int m = 10, n = 20;
    cout << "\nBefore swap: m=" << m << " n=" << n << endl;
    swap(&m, &n);
    cout << "After swap:  m=" << m << " n=" << n << endl;

    return 0;
}
