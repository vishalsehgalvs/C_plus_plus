// ============================================================
// 03_control_flow.cpp  —  Basic
// if/else, switch, while, for, do-while, break, continue
// ============================================================

#include <iostream>
using namespace std;

int main()
{
    // ================================================================
    // 1. if / else if / else
    // ================================================================
    int score = 75;

    if (score >= 90)
    {
        cout << "Grade: A" << endl;
    }
    else if (score >= 80)
    {
        cout << "Grade: B" << endl;
    }
    else if (score >= 70)
    {
        cout << "Grade: C" << endl;
    }
    else if (score >= 60)
    {
        cout << "Grade: D" << endl;
    }
    else
    {
        cout << "Grade: F" << endl;
    }
    // Output: Grade: C

    // Shorthand (ternary operator)
    string result = (score >= 60) ? "Pass" : "Fail";
    cout << "Result: " << result << endl;

    // ================================================================
    // 2. switch
    // ================================================================
    int day = 3; // 1=Mon, 2=Tue, etc.

    switch (day)
    {
    case 1:
        cout << "Monday" << endl;
        break;
    case 2:
        cout << "Tuesday" << endl;
        break;
    case 3:
        cout << "Wednesday" << endl;
        break;
    case 4:
        cout << "Thursday" << endl;
        break;
    case 5:
        cout << "Friday" << endl;
        break;
    case 6:
    case 7:
        cout << "Weekend!" << endl;
        break;
    default:
        cout << "Invalid day" << endl;
    }
    // Output: Wednesday

    // ================================================================
    // 3. for loop
    // ================================================================
    cout << "\nfor loop: ";
    for (int i = 0; i < 5; i++)
    {
        cout << i << " ";
    }
    cout << endl;
    // Output: 0 1 2 3 4

    // Range-based for loop (C++11)
    int numbers[] = {10, 20, 30, 40, 50};
    cout << "range-based for: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;

    // ================================================================
    // 4. while loop
    // ================================================================
    cout << "\nwhile loop: ";
    int count = 1;
    while (count <= 5)
    {
        cout << count << " ";
        count++;
    }
    cout << endl;
    // Output: 1 2 3 4 5

    // ================================================================
    // 5. do-while loop (runs at least once!)
    // ================================================================
    cout << "do-while: ";
    int x = 1;
    do
    {
        cout << x << " ";
        x++;
    } while (x <= 5);
    cout << endl;

    // do-while always runs body first, then checks condition
    int y = 100;
    do
    {
        cout << "This prints even though y=" << y << " > 5" << endl;
    } while (y <= 5);
    // Output: "This prints even though y=100 > 5"

    // ================================================================
    // 6. break and continue
    // ================================================================
    cout << "\nbreak example (stop at 5): ";
    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
            break; // exit the loop
        cout << i << " ";
    }
    cout << endl;
    // Output: 0 1 2 3 4

    cout << "continue example (skip even): ";
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
            continue; // skip even numbers
        cout << i << " ";
    }
    cout << endl;
    // Output: 1 3 5 7 9

    // ================================================================
    // 7. Nested loops
    // ================================================================
    cout << "\nMultiplication table (3x3):" << endl;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            cout << i * j << "\t";
        }
        cout << endl;
    }

    // ================================================================
    // 8. Infinite loop with break
    // ================================================================
    int attempts = 0;
    while (true)
    {
        attempts++;
        if (attempts >= 3)
        {
            cout << "\nMax attempts reached." << endl;
            break;
        }
    }

    return 0;
}
