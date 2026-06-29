// ============================================================
// 09_file_handling.cpp  —  Basic
// Reading and writing files with fstream
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    // ================================================================
    // 1. Write to a file
    // ================================================================
    {
        ofstream outFile("students.txt"); // creates/overwrites the file

        if (!outFile.is_open())
        {
            cerr << "Error: Could not open file for writing." << endl;
            return 1;
        }

        outFile << "Alice,90,85,92" << endl;
        outFile << "Bob,75,80,78" << endl;
        outFile << "Charlie,88,91,95" << endl;
        outFile << "Diana,60,70,65" << endl;

        outFile.close();
        cout << "File written successfully." << endl;
    }

    // ================================================================
    // 2. Read from a file — line by line
    // ================================================================
    {
        ifstream inFile("students.txt");

        if (!inFile.is_open())
        {
            cerr << "Error: Could not open file for reading." << endl;
            return 1;
        }

        cout << "\n=== Reading students.txt ===" << endl;
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }

        inFile.close();
    }

    // ================================================================
    // 3. Parse CSV data while reading
    // ================================================================
    {
        ifstream inFile("students.txt");
        string line;

        cout << "\n=== Parsed Data ===" << endl;
        cout << "Name     | Math | Science | English | Avg" << endl;
        cout << "---------+------+---------+---------+-----" << endl;

        while (getline(inFile, line))
        {
            stringstream ss(line);
            string name, m, s, e;

            getline(ss, name, ',');
            getline(ss, m, ',');
            getline(ss, s, ',');
            getline(ss, e, ',');

            double avg = (stoi(m) + stoi(s) + stoi(e)) / 3.0;

            cout << name << " | " << m << " | " << s << " | " << e
                 << "   | " << avg << endl;
        }

        inFile.close();
    }

    // ================================================================
    // 4. Append to a file
    // ================================================================
    {
        ofstream appendFile("students.txt", ios::app); // ios::app = append mode
        appendFile << "Eve,95,98,99" << endl;
        appendFile.close();
        cout << "\nAdded Eve to the file." << endl;
    }

    // ================================================================
    // 5. Binary file write and read
    // ================================================================
    {
        struct Record
        {
            char name[20];
            int score;
        };

        // Write binary
        ofstream binOut("records.bin", ios::binary);
        Record r1 = {"Alice", 95};
        Record r2 = {"Bob", 80};
        binOut.write(reinterpret_cast<char *>(&r1), sizeof(Record));
        binOut.write(reinterpret_cast<char *>(&r2), sizeof(Record));
        binOut.close();

        // Read binary
        ifstream binIn("records.bin", ios::binary);
        cout << "\n=== Binary Records ===" << endl;
        Record r;
        while (binIn.read(reinterpret_cast<char *>(&r), sizeof(Record)))
        {
            cout << r.name << ": " << r.score << endl;
        }
        binIn.close();
    }

    // ================================================================
    // 6. Check if file exists
    // ================================================================
    {
        ifstream checkFile("students.txt");
        if (checkFile.good())
        {
            cout << "\nstudents.txt exists!" << endl;
        }
        else
        {
            cout << "\nFile does not exist." << endl;
        }
        checkFile.close();
    }

    // ================================================================
    // 7. fstream — both read and write in same object
    // ================================================================
    {
        fstream rw("notes.txt", ios::in | ios::out | ios::trunc);
        rw << "Line 1: Hello" << endl;
        rw << "Line 2: World" << endl;
        rw.seekg(0); // rewind to beginning

        cout << "\n=== Read-Write File ===" << endl;
        string line;
        while (getline(rw, line))
            cout << line << endl;
        rw.close();
    }

    return 0;
}
