# C++ Pointers and References

> Source: https://www.programiz.com/cpp-programming/pointers

---

## Memory and Addresses

Every variable in your program lives in memory. Each memory location has an **address** — a unique number identifying where it is.

> 🔁 **Analogy:** Think of RAM as a giant apartment building. Each byte is a room with a room number (address). A variable is like a tenant in a room. A pointer is a piece of paper that has the room number written on it.

```
Variable:   int age = 25;

Memory:
Address: 0x1000  0x1001  0x1002  0x1003
         ┌──────┬──────┬──────┬──────┐
         │  25  │  ?   │  ?   │  ?   │
         └──────┴──────┴──────┴──────┘
              ↑
              age is stored here at address 0x1000
```

---

## Address-of Operator (`&`)

Gets the memory address of a variable:

```cpp
int age = 25;

cout << age;    // 25           (the value)
cout << &age;   // 0x7fff5678   (the address — actual number varies)
```

---

## Pointers

A **pointer** is a variable that **stores a memory address**.

```cpp
int age = 25;
int *ptr = &age;   // ptr stores the ADDRESS of age

// Read as: "int pointer ptr points to age"
```

```
age:  ┌──────┐     ptr: ┌──────────┐
      │  25  │◄─────────│ 0x1000   │
      └──────┘           └──────────┘
      0x1000             some other address
```

### Declare a pointer:

```cpp
int *p;      // pointer to int
double *dp;  // pointer to double
char *cp;    // pointer to char

// These all mean the same:
int* p;   // style 1
int *p;   // style 2 (common)
int * p;  // style 3
```

---

## Dereference Operator (`*`)

The `*` in front of a pointer means "go to that address and get/set the value":

```cpp
int age = 25;
int *ptr = &age;

cout << ptr;   // address: 0x1000 (the pointer value)
cout << *ptr;  // 25  (the value AT that address — dereference)

// Modify via pointer
*ptr = 30;
cout << age;   // 30 — changed the original!
cout << *ptr;  // 30
```

> 💡 Remember the `*` dual meaning:
>
> - In declaration: `int *ptr` → declaring a pointer variable
> - In expression: `*ptr` → dereferencing (getting the value)

---

## Null Pointer

A pointer that doesn't point to anything:

```cpp
int *ptr = nullptr;  // modern C++ (use this)
int *ptr2 = NULL;    // old C style
int *ptr3 = 0;       // also valid but unclear

// Always check before using!
if (ptr != nullptr) {
    cout << *ptr;  // safe
} else {
    cout << "Pointer is null";
}
```

> ⚠️ **Never dereference a null or uninitialized pointer!** This causes a crash (segmentation fault).

---

## Pointers and Arrays

Arrays and pointers are closely related in C++. The array name is a pointer to the first element:

```cpp
int arr[] = {10, 20, 30, 40, 50};
int *p = arr;   // p points to arr[0]

cout << *p;       // 10 (arr[0])
cout << *(p+1);   // 20 (arr[1])
cout << *(p+2);   // 30 (arr[2])

// Pointer arithmetic
p++;           // move to next element
cout << *p;    // 20

// These are equivalent:
arr[2]   == *(arr + 2)   // both give 30
&arr[2]  == arr + 2      // both give address of 3rd element
```

---

## References (`&`)

A reference is an **alias** for an existing variable. Once assigned, it always refers to the same variable.

> 🔁 **Analogy:** A reference is a nickname. If your name is "Robert" and people call you "Bob", both names refer to the same person.

```cpp
int age = 25;
int &ref = age;   // ref is a reference to age

cout << ref;  // 25 (same as age)
ref = 30;     // changes age!
cout << age;  // 30

// Cannot rebind a reference:
int x = 10, y = 20;
int &r = x;
r = y;   // this does NOT rebind r to y — it sets x = 20
```

---

## Pointer vs Reference

|                    | Pointer                          | Reference                    |
| ------------------ | -------------------------------- | ---------------------------- |
| Syntax             | `int *p = &x`                    | `int &r = x`                 |
| Can be null        | Yes (`nullptr`)                  | No — must refer to something |
| Can be reassigned  | Yes (point to different vars)    | No — always same var         |
| Must initialize?   | No (but should)                  | Yes — always                 |
| Dereference syntax | `*p`                             | Just use `r` directly        |
| Usage              | Dynamic memory, arrays, optional | Function params, aliases     |

```cpp
// Both achieve "pass by reference" to a function:

// Pointer way
void doubleWithPtr(int *p) {
    *p *= 2;   // must dereference
}
doubleWithPtr(&x);  // must pass address

// Reference way (cleaner)
void doubleWithRef(int &r) {
    r *= 2;    // no dereference needed
}
doubleWithRef(x);   // just pass variable
```

---

## Dynamic Memory (`new` / `delete`)

Allocate memory on the **heap** at runtime:

```cpp
// Allocate single variable
int *ptr = new int;    // allocate space for one int
*ptr = 42;
cout << *ptr;          // 42

delete ptr;            // free the memory
ptr = nullptr;         // good practice after delete

// Allocate and initialize
int *p = new int(100);  // value = 100
delete p;

// Allocate array
int *arr = new int[5];   // array of 5 ints
arr[0] = 1;
arr[1] = 2;
// ...
delete[] arr;            // must use delete[] for arrays!
arr = nullptr;
```

```
Stack:     ptr  ──────────────────► Heap: [ 42 ]
           (local var)              (new'd memory)
```

> ⚠️ **Memory leak:** If you `new` without `delete`, the memory is never freed:

```cpp
int *p = new int(5);
// ... forgot to delete p
// memory is wasted until program ends
```

> 💡 In modern C++, prefer **smart pointers** (`unique_ptr`, `shared_ptr`) which automatically free memory. Covered in the Modern C++ section.

---

## Arrow Operator (`->`) for Struct Pointers

When you have a pointer to a struct, use `->` instead of `.`:

```cpp
struct Person {
    string name;
    int age;
};

Person alice = {"Alice", 30};
Person *ptr = &alice;

cout << ptr->name;   // "Alice"  (same as (*ptr).name)
cout << ptr->age;    // 30

ptr->age = 31;       // modify via pointer
```

> `ptr->member` is just shorthand for `(*ptr).member`

---

## `const` and Pointers — The Tricky Part

The position of `const` relative to `*` completely changes the meaning:

```
Read the declaration right-to-left:

  const int* p     →  p is a pointer to a const int    (can't change the value)
  int* const p     →  p is a const pointer to an int   (can't change the address)
  const int* const p  →  const pointer to const int    (can't change either)
```

```cpp
int x = 10, y = 20;

// Pointer to const — data is read-only, pointer can be redirected
const int* p1 = &x;
// *p1 = 99;   // ❌ ERROR: can't modify x through p1
p1 = &y;       // ✅ OK: can point to y instead

// Const pointer — address is fixed, data can be changed
int* const p2 = &x;
*p2 = 99;      // ✅ OK: can modify x's value
// p2 = &y;   // ❌ ERROR: can't redirect p2 to y

// Const pointer to const — nothing can change
const int* const p3 = &x;
// *p3 = 99;  // ❌ ERROR
// p3 = &y;   // ❌ ERROR
cout << *p3;   // ✅ can only read
```

> 💡 **Practical rule:** Pass `const Type*` or `const Type&` to functions when you don't need to modify the data. It documents intent and lets the compiler catch mistakes.

---

## Function Pointers

Functions live in memory too — you can store a pointer to them and call them later:

```cpp
// A function
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

// Declare a function pointer: return_type (*name)(param_types)
int (*operation)(int, int);   // pointer to a function taking two ints, returning int

operation = add;
cout << operation(3, 4);   // 7

operation = sub;
cout << operation(3, 4);   // -1

// Useful: pass behavior as a parameter
void applyAndPrint(int a, int b, int (*func)(int, int)) {
    cout << func(a, b) << endl;
}

applyAndPrint(10, 5, add);   // 15
applyAndPrint(10, 5, sub);   // 5

// Array of function pointers — like a menu
int multiply(int a, int b) { return a * b; }
int (*ops[])(int, int) = { add, sub, multiply };

for (auto op : ops) cout << op(6, 3) << " ";  // 9 3 18
```

> 💡 **Modern alternative:** `std::function<int(int,int)>` and lambdas are more readable for most use cases. Function pointers are mainly used in C APIs and callbacks.

---

## `void*` — Generic Pointer

A `void*` can hold **any** pointer type but you must cast it back before use:

```cpp
int    n = 42;
double d = 3.14;
char   c = 'Z';

void* ptr;

ptr = &n;   // any type works
cout << *(int*)ptr    << endl;    // 42   (must cast!)

ptr = &d;
cout << *(double*)ptr << endl;    // 3.14

ptr = &c;
cout << *(char*)ptr   << endl;    // Z

// Common in C APIs (like memcpy, malloc)
memcpy(dest, src, size);   // both params are void*
```

> ⚠️ **Avoid `void*` in modern C++.** Use templates, `std::any`, or proper inheritance. `void*` throws away type safety — a wrong cast is undefined behavior with no error message.

---

## Key Takeaways

- `&x` gets the **address** of variable `x`
- `int *p` declares a pointer; `*p` dereferences it (gets the value at the address)
- Always initialize pointers — use `nullptr` if not yet set
- References (`int &r = x`) are aliases — they always refer to the same original
- Pointers can be null and reassigned; references cannot
- `new` allocates on heap; always `delete` (or `delete[]` for arrays) to free memory
- Use `->` to access struct/class members through a pointer (same as `(*ptr).member`)
- `const int* p` — pointer to const (data read-only); `int* const p` — const pointer (address fixed)
- Function pointers store addresses of functions; useful for callbacks and dispatch tables
- `void*` is a generic pointer — avoid in modern C++, use templates or `std::function` instead
