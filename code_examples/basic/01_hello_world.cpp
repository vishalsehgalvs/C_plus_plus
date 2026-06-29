// ============================================================
// 01_hello_world.cpp  —  Basic
// Your very first C++ program
// ============================================================

#include <iostream>  // includes the standard input/output library
using namespace std; // so we can write cout instead of std::cout

int main()
{
    // cout = "character output" — prints to the screen
    // endl = end line (move to next line)
    cout << "Hello, World!" << endl;

    // You can chain multiple << operators
    cout << "My name is " << "C++" << " and I am " << 33 << " years old." << endl;

    // \n also goes to the next line (slightly faster than endl)
    cout << "Line 1\n";
    cout << "Line 2\n";

    // Multiple lines at once
    cout << "One\nTwo\nThree\n";

    // return 0 means "program finished successfully"
    return 0;
}

/*
Expected Output:
Hello, World!
My name is C++ and I am 33 years old.
Line 1
Line 2
One
Two
Three
*/
