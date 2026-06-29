# Facade Pattern

**Category:** Structural

---

## What Is It?

The **Facade** pattern provides a **simplified interface** to a complex subsystem. It hides the complexity and gives clients one easy-to-use interface.

> 🔁 **Analogy:** Your car's dashboard. To drive, you only use the steering wheel, pedals, and gear shift. Underneath, the car has a massively complex engine, fuel injection system, transmission, ABS, etc. The dashboard is the facade — it hides all that complexity.

---

## When to Use It?

- A subsystem is complex and hard to use directly
- You want to provide a simple entry point to a library or API
- You want to layer your subsystem (facade = public API, internals stay private)

---

## Structure

```
Client
  │
  └──► Facade   (simple interface)
           │
     ┌─────┼──────┐
     │     │      │
  SubA   SubB   SubC   (complex subsystem — client never touches these)
```

---

## C++ Implementation: Home Theater System

```cpp
#include <iostream>
using namespace std;

// ============ Complex Subsystem Classes ============
class Amplifier {
public:
    void on()  { cout << "[Amp] Turning on" << endl; }
    void off() { cout << "[Amp] Turning off" << endl; }
    void setVolume(int v) { cout << "[Amp] Volume set to " << v << endl; }
};

class DVDPlayer {
public:
    void on()   { cout << "[DVD] Turning on" << endl; }
    void off()  { cout << "[DVD] Turning off" << endl; }
    void play(const string& movie) {
        cout << "[DVD] Playing: " << movie << endl;
    }
    void stop() { cout << "[DVD] Stopped" << endl; }
};

class Projector {
public:
    void on()    { cout << "[Projector] Turning on" << endl; }
    void off()   { cout << "[Projector] Turning off" << endl; }
    void wideScreenMode() { cout << "[Projector] Wide screen mode" << endl; }
};

class Lights {
public:
    void dim(int level) { cout << "[Lights] Dimming to " << level << "%" << endl; }
    void on()  { cout << "[Lights] Full brightness" << endl; }
};

class SoundSystem {
public:
    void on()      { cout << "[Sound] Surround sound on" << endl; }
    void off()     { cout << "[Sound] Surround sound off" << endl; }
    void setSurround() { cout << "[Sound] Surround mode: 5.1" << endl; }
};

// ============ Facade ============
class HomeTheaterFacade {
    Amplifier amp;
    DVDPlayer dvd;
    Projector projector;
    Lights lights;
    SoundSystem sound;

public:
    // ONE simple method for the client
    void watchMovie(const string& movie) {
        cout << "=== Getting ready to watch: " << movie << " ===" << endl;
        lights.dim(10);
        projector.on();
        projector.wideScreenMode();
        amp.on();
        amp.setVolume(15);
        sound.on();
        sound.setSurround();
        dvd.on();
        dvd.play(movie);
        cout << "=== Enjoy the movie! ===" << endl;
    }

    void endMovie() {
        cout << "\n=== Shutting down home theater ===" << endl;
        dvd.stop();
        dvd.off();
        sound.off();
        amp.off();
        projector.off();
        lights.on();
        cout << "=== Done ===" << endl;
    }
};

// ============ Main ============
int main() {
    HomeTheaterFacade theater;

    // Client only needs to know about the facade
    theater.watchMovie("Inception");

    theater.endMovie();

    return 0;
}
```

Output:

```
=== Getting ready to watch: Inception ===
[Lights] Dimming to 10%
[Projector] Turning on
[Projector] Wide screen mode
[Amp] Turning on
[Amp] Volume set to 15
[Sound] Surround sound on
[Sound] Surround mode: 5.1
[DVD] Turning on
[DVD] Playing: Inception
=== Enjoy the movie! ===

=== Shutting down home theater ===
[DVD] Stopped
[DVD] Turning off
[Sound] Surround sound off
[Amp] Turning off
[Projector] Turning off
[Lights] Full brightness
=== Done ===
```

---

## Real-World Example: Compiler Facade

```cpp
// A compiler has many stages: scan → parse → analyze → generate → link
// The facade provides one simple method: compile()

class Scanner {
public:
    void scan(const string& file) {
        cout << "[Scanner] Tokenizing: " << file << endl;
    }
};

class Parser {
public:
    void parse() { cout << "[Parser] Building AST" << endl; }
};

class SemanticAnalyzer {
public:
    void analyze() { cout << "[Semantic] Checking types" << endl; }
};

class CodeGenerator {
public:
    void generate() { cout << "[CodeGen] Generating assembly" << endl; }
};

class Linker {
public:
    void link(const string& output) {
        cout << "[Linker] Linking → " << output << endl;
    }
};

// Facade
class Compiler {
    Scanner    scanner;
    Parser     parser;
    SemanticAnalyzer analyzer;
    CodeGenerator codeGen;
    Linker     linker;

public:
    void compile(const string& sourceFile, const string& outputFile) {
        cout << "Compiling " << sourceFile << "..." << endl;
        scanner.scan(sourceFile);
        parser.parse();
        analyzer.analyze();
        codeGen.generate();
        linker.link(outputFile);
        cout << "Build successful: " << outputFile << endl;
    }
};

int main() {
    Compiler c;
    c.compile("main.cpp", "main.exe");
}
```

---

## Facade vs Adapter

```
Facade:                        Adapter:
─────────────────────────      ─────────────────────────────
Simplifies a complex           Makes incompatible interfaces
subsystem                      work together

Provides a NEW interface       Translates one existing
(high-level overview)          interface to another

Hides multiple classes         Usually wraps a single class
behind one simple API          to match another interface
```

---

## Pros and Cons

| ✅ Pros                                      | ❌ Cons                                                |
| -------------------------------------------- | ------------------------------------------------------ |
| Simplifies complex subsystem usage           | Facade can become a "god object" if too much goes in   |
| Decouples client from subsystem              | Subsystem still accessible directly (not fully hidden) |
| Easy to add more steps to complex operations | Adding features to facade grows it                     |
| Great for layered architecture               |                                                        |

---

> 💡 **Common uses:** Library wrappers, API gateways, OS system call wrappers, SDK entry points.
