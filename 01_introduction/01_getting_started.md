# Getting Started with C++

> Source: https://www.programiz.com/cpp-programming/getting-started

---

## What Is C++?

C++ is a **general-purpose programming language** created by Bjarne Stroustrup in 1983 as an extension of the C language. It adds **object-oriented features** on top of C's speed and power.

> 🔁 **Analogy:** If C is a powerful manual car, C++ is the same car but with extra features — automatic gearbox, GPS, cruise control. The engine (performance) is still the same, but you get more tools.

**Where is C++ used?**

- Game engines (Unreal Engine, Unity internals)
- Operating systems (Windows, Linux parts)
- Browsers (Chrome, Firefox engines)
- High-frequency trading systems
- Embedded systems (cars, robots, IoT)
- Compilers and interpreters

---

## How C++ Works: Compilation

Unlike Python or JavaScript that run directly, C++ must be **compiled** first — translated from human-readable code into machine code your CPU can run.

```
You write code         Compiler            CPU runs
(source .cpp file) → (translates it) → (machine code / .exe)
```

### Step-by-step flow:

```
┌──────────────┐    ┌───────────────┐    ┌──────────────┐    ┌──────────┐
│  source.cpp  │───▶│ Preprocessor  │───▶│   Compiler   │───▶│  Linker  │
│  (your code) │    │ (handles #)   │    │  (creates    │    │ (merges  │
└──────────────┘    └───────────────┘    │  object file)│    │ into exe)│
                                         └──────────────┘    └──────────┘
                                                                    │
                                                                    ▼
                                                             ┌──────────────┐
                                                             │ program.exe  │
                                                             │ (runs on CPU)│
                                                             └──────────────┘
```

1. **Preprocessor**: handles `#include`, `#define` directives
2. **Compiler**: converts `.cpp` to object code (`.obj` or `.o`)
3. **Linker**: combines object files + libraries into final executable

---

## Setting Up C++

### Option 1: Online Compiler (Easiest — Start Here)

Visit: https://www.programiz.com/cpp-programming/online-compiler/

No installation needed. Just type and run.

### Option 2: Install a Compiler (Recommended Long-Term)

**Windows:**

```
1. Download MinGW from mingw-w64.org (includes g++ compiler)
2. Add C:\mingw64\bin to your PATH environment variable
3. Open Command Prompt → type: g++ --version
4. If it shows a version number, you're ready!
```

**Mac:**

```bash
xcode-select --install    # installs clang/g++ compiler
g++ --version             # verify installation
```

**Linux:**

```bash
sudo apt install g++      # Ubuntu/Debian
g++ --version             # verify
```

### Option 3: IDE (All-in-One — Best for Beginners)

- **VS Code** + C++ extension + MinGW
- **Code::Blocks** (free, beginner-friendly)
- **CLion** (professional, paid)

---

## Your First C++ Program

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

**Output:**

```
Hello, World!
```

### What each line means:

```cpp
#include <iostream>   // Include the I/O library (gives us cout, cin)
using namespace std;  // Use the "std" namespace (so we type cout, not std::cout)

int main() {          // The main function — execution always starts here
                      // int = returns an integer

    cout << "Hello, World!" << endl;
    // cout  = "character output" — prints to screen
    // <<    = insertion operator (send this to cout)
    // endl  = end line (newline + flush buffer)

    return 0;         // 0 = program ran successfully
                      // any non-zero = error
}
```

---

## Compiling & Running From Terminal

```bash
# Step 1: Compile
g++ hello.cpp -o hello

# Step 2: Run
./hello          # Mac/Linux
hello.exe        # Windows

# Output:
Hello, World!
```

### What g++ flags mean:

| Flag            | Meaning                 |
| --------------- | ----------------------- |
| `g++ hello.cpp` | compile this file       |
| `-o hello`      | name the output "hello" |
| `-Wall`         | show all warnings       |
| `-std=c++17`    | use C++17 standard      |

---

## C++ vs Other Languages

| Feature        | C++             | Python      | JavaScript   |
| -------------- | --------------- | ----------- | ------------ |
| Speed          | ⚡ Very fast    | 🐢 Slow     | 🚶 Medium    |
| Learning curve | 📈 Steep        | 📉 Easy     | 📊 Medium    |
| Memory control | ✅ Full control | ❌ Managed  | ❌ Managed   |
| Use case       | Systems, games  | Scripts, AI | Web, apps    |
| Compilation    | Compiled        | Interpreted | JIT compiled |

---

## Key Takeaways

- C++ is a compiled language — code must be translated to machine code before running
- The compilation pipeline: source → preprocessor → compiler → linker → executable
- Every C++ program needs a `main()` function — that's where execution starts
- `#include <iostream>` gives access to `cout` (print) and `cin` (input)
- `return 0` at the end of `main()` signals success
- Use an online compiler (programiz.com/cpp-programming/online-compiler) to practice without setup
