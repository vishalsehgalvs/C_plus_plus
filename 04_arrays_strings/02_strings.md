# C++ Strings

> Source: https://www.programiz.com/cpp-programming/string

---

## Two Types of Strings in C++

C++ has two ways to handle strings:

| Type                      | Header      | Style      | Recommended? |
| ------------------------- | ----------- | ---------- | ------------ |
| C-style string (`char[]`) | `<cstring>` | Old C way  | ❌ Avoid     |
| `std::string`             | `<string>`  | Modern C++ | ✅ Use this  |

> 🔁 **Analogy:** C-style strings are like manually managing individual letters in boxes. `std::string` is like a smart notepad that manages itself — grows, shrinks, and has built-in tools.

---

## `std::string` Basics

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Create strings
    string name = "Alice";
    string greeting = "Hello, " + name + "!";  // concatenation with +

    cout << greeting << endl;       // Hello, Alice!
    cout << name.length() << endl;  // 5
    cout << name.size() << endl;    // 5 (same as length)

    return 0;
}
```

---

## String Input

```cpp
string word;
cin >> word;           // reads ONE word (stops at space)

string sentence;
getline(cin, sentence); // reads FULL line including spaces
```

---

## Common String Operations

### Access individual characters

```cpp
string s = "Hello";

cout << s[0];      // H
cout << s[4];      // o
cout << s.at(2);   // l (with bounds checking)
cout << s.front(); // H (first)
cout << s.back();  // o (last)

// Modify a character
s[0] = 'J';
cout << s;  // Jello
```

### Concatenation

```cpp
string first = "Hello";
string second = " World";

string full = first + second;   // "Hello World"
first += "!";                   // "Hello!"

// Cannot concatenate two string literals directly:
// string s = "Hello" + " World";  // ❌ won't compile
string s = string("Hello") + " World";  // ✅
```

### Size and empty check

```cpp
string s = "Hello";
cout << s.length();    // 5
cout << s.size();      // 5
cout << s.empty();     // 0 (false)

string empty = "";
cout << empty.empty(); // 1 (true)
```

### Substrings

```cpp
string s = "Hello World";

// substr(start_pos, length)
cout << s.substr(0, 5);   // "Hello"
cout << s.substr(6);      // "World" (from index 6 to end)
cout << s.substr(6, 3);   // "Wor"
```

### Find / Search

```cpp
string s = "Hello World";

// find returns position, or string::npos if not found
size_t pos = s.find("World");
if (pos != string::npos) {
    cout << "Found at position: " << pos << endl;  // 6
} else {
    cout << "Not found" << endl;
}

// Find a character
size_t charPos = s.find('o');  // 4 (first 'o')
size_t lastPos = s.rfind('o'); // 7 (last 'o', rfind = search from right)
```

### Replace

```cpp
string s = "I love cats";
s.replace(7, 4, "dogs");  // replace(start, count, new_str)
cout << s;  // "I love dogs"
```

### Insert and Erase

```cpp
string s = "Hello World";
s.insert(5, ", Beautiful");  // insert at position 5
cout << s;  // "Hello, Beautiful World"

s.erase(5, 12);  // erase(start, count)
cout << s;  // "Hello World"
```

### Compare

```cpp
string a = "apple";
string b = "banana";

if (a == b) cout << "equal";
if (a != b) cout << "not equal";
if (a < b)  cout << "a comes before b alphabetically";

int result = a.compare(b);
// 0 = equal, negative = a < b, positive = a > b
```

---

## String Conversion

```cpp
#include <string>

// Number to string
int num = 42;
string s = to_string(num);   // "42"

double d = 3.14;
string sd = to_string(d);    // "3.140000"

// String to number
string str = "123";
int n = stoi(str);           // 123 (string to int)
double f = stod("3.14");     // 3.14 (string to double)
long l = stol("99999");      // long
```

---

## Looping Through a String

```cpp
string s = "Hello";

// By index
for (int i = 0; i < s.length(); i++) {
    cout << s[i] << " ";
}

// Range-based for
for (char c : s) {
    cout << c << " ";
}
// Output: H e l l o

// Count vowels
int vowelCount = 0;
for (char c : s) {
    c = tolower(c);  // convert to lowercase for comparison
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        vowelCount++;
    }
}
```

---

## Useful Character Functions (`<cctype>`)

```cpp
#include <cctype>

char c = 'A';
toupper(c);   // 'A' (already uppercase)
tolower(c);   // 'a'

isalpha('A'); // true — is it a letter?
isdigit('5'); // true — is it a digit?
isalnum('A'); // true — letter or digit?
isspace(' '); // true — whitespace?
ispunct('!'); // true — punctuation?
isupper('A'); // true — uppercase?
islower('a'); // true — lowercase?
```

---

## Real Example: Reverse a String

```cpp
#include <iostream>
#include <string>
#include <algorithm>  // for reverse
using namespace std;

int main() {
    string s = "Hello World";

    // Method 1: std::reverse
    string rev = s;
    reverse(rev.begin(), rev.end());
    cout << rev << endl;  // "dlroW olleH"

    // Method 2: manual
    string manual = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        manual += s[i];
    }
    cout << manual << endl;  // "dlroW olleH"

    return 0;
}
```

---

## C-Style Strings (Know About, Avoid)

```cpp
#include <cstring>

char cstr[] = "Hello";  // null-terminated: H e l l o \0
int len = strlen(cstr); // 5

char dest[20];
strcpy(dest, cstr);     // copy
strcat(dest, " World"); // concatenate
int cmp = strcmp("a", "b"); // compare: negative if a < b

// ⚠️ Easy to overflow buffers! Use std::string instead
```

---

## `std::string_view` — Read Without Copying (C++17)

A `string_view` is a **non-owning view** of a string. It doesn't copy the data — just points at it. Ideal for read-only function parameters:

```cpp
#include <string_view>

// Old way: copies the whole string every call
void printOld(string s) { cout << s; }       // makes a copy — expensive
void printBetter(const string& s) { cout << s; }  // ref, but only works for std::string

// New way: works with string literals, std::string, char arrays — NO copy
void printFast(string_view sv) { cout << sv; }

string s1 = "hello world";
printFast(s1);              // from std::string — no copy
printFast("hello world");   // from string literal — no copy

// Slicing without copying
string_view sv = "hello world";
cout << sv.substr(6, 5);    // "world" — no allocation!
cout << sv.length();        // 11
cout << sv[0];              // 'h'

// Find
if (sv.find("world") != string_view::npos) cout << "found!";
```

> ⚠️ `string_view` doesn't own the data. Make sure the original string outlives the view — don't store a `string_view` to a temporary!

---

## Raw String Literals

Regular strings need escape sequences for backslashes, quotes, newlines. Raw strings let you write them as-is:

```cpp
// Regular string — backslashes need escaping
string path1 = "C:\\Users\\Alice\\Documents\\file.txt";
string regex1 = "\\d+\\.\\d+";

// Raw string: R"(  ...  )"  — everything inside is literal
string path2  = R"(C:\Users\Alice\Documents\file.txt)";
string regex2 = R"(\d+\.\d+)";

// Multi-line raw string
string html = R"(
    <html>
      <body>
        <p>Hello World</p>
      </body>
    </html>
)";
cout << html;  // prints exactly as written, with newlines

// Custom delimiter if you need ) inside your string
string tricky = R"xyz(This has ) inside)xyz";  // delimiter is xyz
```

---

## `std::regex` — Pattern Matching

Find, validate, or extract text using regular expressions:

```cpp
#include <regex>

string text = "Alice: alice@email.com, Bob: bob@work.org";

// Match — does this whole string match a pattern?
regex emailPattern(R"([a-zA-Z0-9.]+@[a-zA-Z0-9.]+\.[a-zA-Z]{2,})");
string email = "test@example.com";
cout << regex_match(email, emailPattern);  // true

// Search — find first match in string
smatch match;
if (regex_search(text, match, emailPattern)) {
    cout << "First email: " << match[0] << endl;  // alice@email.com
}

// Find ALL matches
sregex_iterator it(text.begin(), text.end(), emailPattern);
sregex_iterator end;
while (it != end) {
    cout << (*it)[0] << endl;  // alice@email.com, then bob@work.org
    ++it;
}

// Replace — substitute matches
string result = regex_replace(text, emailPattern, "[HIDDEN]");
cout << result;  // Alice: [HIDDEN], Bob: [HIDDEN]
```

> 💡 Common regex patterns:
>
> - `\d+` — one or more digits
> - `[a-zA-Z]+` — one or more letters
> - `\s+` — whitespace
> - `^` / `$` — start / end of string

---

## Key Takeaways

- Always use `std::string` (include `<string>`) — not C-style char arrays
- `+` concatenates strings; `+=` appends to existing string
- `s.length()` or `s.size()` — both return character count
- `s.substr(start, length)` extracts a substring
- `s.find(target)` returns position or `string::npos` if not found
- `s[i]` accesses character (no bounds check); `s.at(i)` does bounds check
- `to_string(num)` converts number to string; `stoi(s)` converts string to int
- `tolower()`, `toupper()`, `isalpha()`, `isdigit()` for character manipulation (need `<cctype>`)
- **`string_view`** (C++17) — read-only non-copying view; prefer over `const string&` for parameters
- **Raw string literals** `R"(...)"` — no escape sequences needed; great for file paths and regex
- **`std::regex`** — pattern matching, validation, search/replace in strings
