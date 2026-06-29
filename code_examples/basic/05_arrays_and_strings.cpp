// ============================================================
// 05_arrays_and_strings.cpp  —  Basic
// Arrays, multidimensional arrays, std::string operations
// ============================================================

#include <iostream>
#include <string>
#include <algorithm> // for sort, reverse
using namespace std;

int main()
{
    // ================================================================
    // 1. Arrays
    // ================================================================
    int numbers[5] = {10, 20, 30, 40, 50};

    // Access elements (0-indexed)
    cout << "First:  " << numbers[0] << endl;
    cout << "Last:   " << numbers[4] << endl;

    // Iterate with for loop
    cout << "Array:  ";
    for (int i = 0; i < 5; i++)
    {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Range-based for
    cout << "Range:  ";
    for (int n : numbers)
        cout << n << " ";
    cout << endl;

    // Partial init (rest = 0)
    int arr[5] = {1, 2};                   // {1, 2, 0, 0, 0}
    cout << "arr[4] = " << arr[4] << endl; // 0

    // Zero-initialize entire array
    int zeros[5] = {};
    cout << "zeros[0] = " << zeros[0] << endl; // 0

    // Size of array
    int size = sizeof(numbers) / sizeof(numbers[0]);
    cout << "Size:   " << size << endl; // 5

    // ================================================================
    // 2. Sorting an array
    // ================================================================
    int data[] = {64, 25, 12, 22, 11};
    sort(data, data + 5); // uses std::sort
    cout << "\nSorted: ";
    for (int x : data)
        cout << x << " ";
    cout << endl;

    // ================================================================
    // 3. Multidimensional Array
    // ================================================================
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    cout << "\nMatrix:" << endl;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            cout << matrix[row][col] << " ";
        }
        cout << endl;
    }

    // ================================================================
    // 4. std::string — the right way to handle strings in C++
    // ================================================================
    string name = "Alice";
    string greeting = "Hello";

    // Concatenation
    string message = greeting + ", " + name + "!";
    cout << "\nmessage: " << message << endl;

    // Length
    cout << "Length: " << name.length() << endl;
    cout << "Size:   " << name.size() << endl; // same as length()

    // Access characters
    cout << "First char: " << name[0] << endl;               // 'A'
    cout << "Last char:  " << name[name.size() - 1] << endl; // 'e'

    // Substring
    string s = "Hello, World!";
    cout << "substr(7, 5): " << s.substr(7, 5) << endl; // "World"

    // Find
    size_t pos = s.find("World");
    if (pos != string::npos)
    {
        cout << "'World' found at index: " << pos << endl; // 7
    }

    // Replace
    string str = "I love cats";
    str.replace(7, 4, "dogs");
    cout << "After replace: " << str << endl; // "I love dogs"

    // Comparison (lexicographic)
    string a = "apple", b = "banana";
    if (a < b)
        cout << a << " comes before " << b << endl;
    if (a == "apple")
        cout << "Equal!" << endl;

    // Convert to uppercase / lowercase
    string word = "Hello World";
    for (char &c : word)
        c = toupper(c);
    cout << "Uppercase: " << word << endl; // HELLO WORLD

    for (char &c : word)
        c = tolower(c);
    cout << "Lowercase: " << word << endl; // hello world

    // Erase and insert
    string t = "Hello World";
    t.erase(5, 6);                         // remove " World"
    cout << "After erase:  " << t << endl; // "Hello"
    t.insert(5, " Everyone");
    cout << "After insert: " << t << endl; // "Hello Everyone"

    // Check empty
    string empty = "";
    cout << "\nIs empty? " << (empty.empty() ? "yes" : "no") << endl;

    // Convert number to string
    int num = 42;
    string numStr = to_string(num);
    cout << "to_string(42) = " << numStr << endl;

    // Convert string to number
    string digits = "123";
    int converted = stoi(digits); // string to int
    cout << "stoi(\"123\") = " << converted << endl;

    return 0;
}
