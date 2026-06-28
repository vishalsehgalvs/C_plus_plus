# C++ Structs and Enums

> Source: https://www.programiz.com/cpp-programming/structure

---

## Structures (`struct`)

A `struct` lets you group **related variables** of different types under one name.

> 🔁 **Analogy:** A struct is like a form with multiple fields. A "Person" form has fields: name, age, height. Instead of three separate variables, you have one grouped `Person` object.

### Without struct — messy:
```cpp
string name1 = "Alice";   int age1 = 30;
string name2 = "Bob";     int age2 = 25;
string name3 = "Charlie"; int age3 = 35;
// Imagine managing 100 people this way...
```

### With struct — clean:
```cpp
struct Person {
    string name;
    int age;
    double height;
};

Person alice = {"Alice", 30, 5.6};
Person bob = {"Bob", 25, 5.9};
```

---

## Defining and Using a Struct

```cpp
#include <iostream>
#include <string>
using namespace std;

// Define the struct (like a blueprint)
struct Student {
    string name;
    int roll;
    double gpa;
};

int main() {
    // Create a struct variable
    Student s1;
    s1.name = "Alice";
    s1.roll = 101;
    s1.gpa  = 3.8;

    // Access members with dot operator (.)
    cout << s1.name << " | Roll: " << s1.roll << " | GPA: " << s1.gpa << endl;

    // Initialize inline
    Student s2 = {"Bob", 102, 3.5};
    cout << s2.name << " | GPA: " << s2.gpa << endl;

    return 0;
}
```

---

## Array of Structs

```cpp
Student classroom[3] = {
    {"Alice", 101, 3.8},
    {"Bob",   102, 3.5},
    {"Carol", 103, 3.9}
};

for (int i = 0; i < 3; i++) {
    cout << classroom[i].name << " - GPA: " << classroom[i].gpa << endl;
}
```

---

## Struct with Functions

```cpp
struct Rectangle {
    double width;
    double height;

    // Method inside struct
    double area() {
        return width * height;
    }

    double perimeter() {
        return 2 * (width + height);
    }
};

Rectangle r = {5.0, 3.0};
cout << "Area: " << r.area() << endl;        // 15
cout << "Perimeter: " << r.perimeter() << endl;  // 16
```

---

## Passing Struct to Functions

```cpp
// Pass by value (copy)
void printStudent(Student s) {
    cout << s.name << " | GPA: " << s.gpa << endl;
}

// Pass by reference (original, efficient for large structs)
void updateGPA(Student &s, double newGPA) {
    s.gpa = newGPA;  // modifies original
}

// Pass by const reference (read-only, no copy)
void displayStudent(const Student &s) {
    cout << s.name << " | Roll: " << s.roll << endl;
}
```

---

## Nested Structs

```cpp
struct Address {
    string city;
    string state;
    string country;
};

struct Employee {
    string name;
    int id;
    Address address;   // nested struct
};

Employee emp;
emp.name = "Alice";
emp.id = 1001;
emp.address.city = "Seattle";
emp.address.state = "WA";
emp.address.country = "USA";

cout << emp.name << " lives in " << emp.address.city << endl;
```

---

## Enumerations (`enum`)

An `enum` defines a variable that can hold one of a **named set of values**.

> 🔁 **Analogy:** An enum is like a dropdown menu — you can only pick from the predefined options. For example, "Direction" can only be NORTH, SOUTH, EAST, or WEST.

```cpp
enum Direction {
    NORTH,   // = 0 by default
    SOUTH,   // = 1
    EAST,    // = 2
    WEST     // = 3
};

Direction d = NORTH;

if (d == NORTH) {
    cout << "Heading North!" << endl;
}
```

### Custom values:

```cpp
enum Month {
    JANUARY = 1,    // start from 1 instead of 0
    FEBRUARY = 2,
    MARCH = 3,
    // ... or shorthand:
};

// Jump values
enum HttpStatus {
    OK = 200,
    NOT_FOUND = 404,
    SERVER_ERROR = 500
};

HttpStatus code = OK;
cout << code;  // 200
```

---

## `enum class` — Scoped Enums (Preferred in C++11+)

Regular enums can clash with other names (their values are in the global scope). `enum class` fixes this:

```cpp
// Without enum class — can clash
enum Color { RED, GREEN, BLUE };
// RED is now a global name

// With enum class — scoped
enum class Color { RED, GREEN, BLUE };
enum class Fruit { RED, GREEN, BLUE };  // No conflict!

Color c = Color::RED;   // must use Color:: prefix
Fruit f = Fruit::RED;   // completely separate

// Comparison
if (c == Color::RED) {
    cout << "Color is red" << endl;
}
```

### Switch with enum:

```cpp
enum class Season { SPRING, SUMMER, FALL, WINTER };

Season s = Season::SUMMER;

switch (s) {
    case Season::SPRING: cout << "It's spring!"; break;
    case Season::SUMMER: cout << "It's summer!"; break;
    case Season::FALL:   cout << "It's fall!";   break;
    case Season::WINTER: cout << "It's winter!"; break;
}
```

---

## struct vs class

In C++, `struct` and `class` are almost identical — the only difference is the default access level:

| | `struct` | `class` |
|--|---------|---------|
| Default access | `public` | `private` |
| Convention | Plain data grouping | OOP with behavior |
| Inheritance | Supported | Supported |

---

## Key Takeaways

- `struct` groups related variables of different types into one unit
- Access struct members with the dot operator `.`
- Pass structs by reference (`&`) or `const &` to avoid copying
- `enum` defines a set of named integer constants — makes code readable
- Prefer `enum class` over `enum` in modern C++ — avoids name clashes, must use `ClassName::VALUE` syntax
- Structs can have methods (and even constructors/destructors — becomes more like a class)
