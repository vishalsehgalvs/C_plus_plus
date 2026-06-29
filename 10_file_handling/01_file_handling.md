# C++ File Handling

> Source: https://www.programiz.com/cpp-programming/file-handling

---

## Why File Handling?

Program data lives in RAM — it's gone when the program ends. Files let you **persist data** to disk (save scores, logs, configuration, etc.).

> 🔁 **Analogy:** File handling is like taking notes in a notebook vs just thinking. Thinking (RAM) disappears when you stop; the notebook (file) stays.

---

## File Stream Classes

C++ uses stream-based file I/O from `<fstream>`:

```
#include <fstream>

ofstream  — Output file stream (write to file)
ifstream  — Input file stream (read from file)
fstream   — Both input and output
```

---

## Writing to a File (`ofstream`)

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Open file for writing (creates if not exists, overwrites if exists)
    ofstream outFile("output.txt");

    if (!outFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    // Write to file (same as cout but goes to file)
    outFile << "Hello, File World!" << endl;
    outFile << "Line 2 of the file" << endl;
    outFile << 42 << endl;
    outFile << 3.14 << endl;

    // Close the file
    outFile.close();
    cout << "File written successfully!" << endl;

    return 0;
}
// Creates "output.txt" with the content
```

---

## Reading from a File (`ifstream`)

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream inFile("output.txt");

    if (!inFile.is_open()) {
        cout << "File not found!" << endl;
        return 1;
    }

    // Read word by word
    string word;
    while (inFile >> word) {
        cout << word << " ";
    }
    cout << endl;

    inFile.close();
    return 0;
}
```

### Read line by line (recommended):

```cpp
ifstream inFile("output.txt");
string line;

while (getline(inFile, line)) {
    cout << line << endl;
}
inFile.close();
```

---

## Append Mode

Add to a file without overwriting:

```cpp
ofstream outFile("log.txt", ios::app);  // ios::app = append mode
outFile << "New log entry" << endl;
outFile.close();
```

---

## File Open Modes

```cpp
ios::in     // open for reading
ios::out    // open for writing (default for ofstream)
ios::app    // append — don't overwrite, add at end
ios::trunc  // truncate — overwrite existing content (default with ios::out)
ios::binary // binary mode
ios::ate    // move to end of file on open

// Combine with |
fstream f("data.txt", ios::in | ios::out);   // read and write
ofstream f("data.txt", ios::out | ios::app); // write, append
```

---

## Using `fstream` (Read + Write)

```cpp
#include <fstream>

fstream file("data.txt", ios::in | ios::out | ios::trunc);

// Write
file << "Alice 90" << endl;
file << "Bob 85" << endl;
file << "Carol 95" << endl;

// Move back to beginning
file.seekg(0);  // seekg = seek for reading

// Read
string name;
int score;
while (file >> name >> score) {
    cout << name << ": " << score << endl;
}

file.close();
```

---

## Check if File Exists

```cpp
ifstream f("myfile.txt");
if (f.good()) {
    cout << "File exists";
} else {
    cout << "File not found";
}
f.close();
```

---

## Real Example: Save and Load Scores

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void saveScores(string names[], int scores[], int n) {
    ofstream f("scores.txt");
    for (int i = 0; i < n; i++) {
        f << names[i] << " " << scores[i] << "\n";
    }
    f.close();
    cout << "Scores saved!" << endl;
}

void loadScores() {
    ifstream f("scores.txt");
    if (!f.is_open()) {
        cout << "No saved scores." << endl;
        return;
    }
    string name;
    int score;
    cout << "=== Saved Scores ===" << endl;
    while (f >> name >> score) {
        cout << name << ": " << score << endl;
    }
    f.close();
}

int main() {
    string names[] = {"Alice", "Bob", "Carol"};
    int scores[]   = {95, 87, 92};

    saveScores(names, scores, 3);
    loadScores();
    return 0;
}
```

---

## Binary File I/O

Write raw data (struct, integers as bytes) — smaller and faster for non-text data:

```cpp
struct Student {
    char name[50];
    int roll;
    float gpa;
};

// Write binary
ofstream binOut("students.bin", ios::binary);
Student s = {"Alice", 101, 3.8f};
binOut.write(reinterpret_cast<char*>(&s), sizeof(s));
binOut.close();

// Read binary
ifstream binIn("students.bin", ios::binary);
Student loaded;
binIn.read(reinterpret_cast<char*>(&loaded), sizeof(loaded));
cout << loaded.name << " | " << loaded.roll << " | " << loaded.gpa << endl;
binIn.close();
```

---

## `<filesystem>` Library (C++17)

Work with files, directories, and paths in a cross-platform way — no more platform-specific hacks:

```cpp
#include <filesystem>
namespace fs = filesystem;   // short alias

// ---- Path operations ----
fs::path p = "C:/Users/Alice/Documents/report.txt";

cout << p.filename();    // report.txt
cout << p.stem();        // report
cout << p.extension();   // .txt
cout << p.parent_path(); // C:/Users/Alice/Documents

// Build paths portably (uses / on Linux, \ on Windows)
fs::path dir  = "C:/Users/Alice";
fs::path file = dir / "Documents" / "report.txt";  // combines correctly

// ---- Checking existence ----
if (fs::exists("myfile.txt"))   cout << "file exists" << endl;
if (fs::is_directory("mydir"))  cout << "it's a folder" << endl;
if (fs::is_regular_file("f.txt")) cout << "it's a file" << endl;

// ---- File info ----
cout << fs::file_size("myfile.txt") << " bytes" << endl;

auto lastWrite = fs::last_write_time("myfile.txt");
// (convert to time_t for display)

// ---- Directory operations ----
fs::create_directory("newdir");        // create one folder
fs::create_directories("a/b/c");       // create nested folders (like mkdir -p)
fs::remove("oldfile.txt");             // delete file
fs::remove_all("olddir");              // delete directory recursively
fs::copy("src.txt", "dst.txt");        // copy file
fs::rename("old.txt", "new.txt");      // rename/move file

// ---- Listing directory contents ----
for (const auto& entry : fs::directory_iterator(".")) {
    cout << entry.path() << " ";
    if (entry.is_regular_file()) cout << "(" << entry.file_size() << " bytes)";
    cout << endl;
}

// Recursive listing (all files in all subdirectories)
for (const auto& entry : fs::recursive_directory_iterator(".")) {
    if (entry.is_regular_file()) {
        cout << entry.path() << endl;
    }
}
```

> ⚠️ Compile flag: `g++ -std=c++17` (and on some Linux distros add `-lstdc++fs`).

---

## Seeking in Files (Random Access)

You don't have to read a file from start to finish. Use `seekg`/`seekp` to jump anywhere:

```cpp
ifstream file("data.txt");

// seekg = seek for reading (get pointer)
file.seekg(0, ios::end);          // jump to end
long size = file.tellg();         // get position = file size
cout << "File size: " << size << " bytes" << endl;

file.seekg(0, ios::beg);          // jump back to start
file.seekg(10);                   // jump to byte 10
file.seekg(5, ios::cur);          // move 5 bytes forward from current position
file.seekg(-5, ios::end);         // 5 bytes before end

// tellg = tell current read position
long pos = file.tellg();

// seekp = seek for writing (put pointer, for fstream/ofstream)
fstream rw("data.bin", ios::in | ios::out | ios::binary);
rw.seekp(4);                      // go to byte 4 and overwrite
rw.write(reinterpret_cast<const char*>(&newValue), sizeof(int));
```

---

## Key Takeaways

- `ofstream` = write; `ifstream` = read; `fstream` = both
- Always check `is_open()` before reading/writing
- Always `close()` files when done (or use RAII — scoped `ifstream` closes automatically)
- Use `ios::app` to append; default is to overwrite
- `getline(file, line)` reads an entire line including spaces
- Binary mode (`ios::binary`) for reading/writing raw data (structs, numbers as bytes)
- `seekg(0)` moves read position back to beginning of file
- **`<filesystem>`** (C++17) — cross-platform path handling, directory listing, file info, create/delete dirs
- Use `fs::exists()` instead of trying to open and checking failure
- `seekg`/`seekp` + `tellg`/`tellp` for random access — jump to any position in a file
