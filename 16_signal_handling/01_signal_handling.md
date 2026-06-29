# Signal Handling in C++

> Source reference: https://www.tutorialspoint.com/cplusplus/cpp_signal_handling.htm

---

## What Is a Signal?

A **signal** is an asynchronous notification sent to a running program — usually by the OS or by another program — to tell it something happened.

> 🔁 **Analogy:** Signals are like interruptions. You're working at your desk (program running), and suddenly someone taps your shoulder (signal received). You stop what you're doing, handle the situation, and then return to work — or you quit entirely.

```
Your Program (running)
       │
       │ (normal execution)
       │
  ⚡ SIGNAL RECEIVED (e.g., Ctrl+C)
       │
       ├── No handler? → Default action (usually terminate)
       │
       └── Handler registered? → Run signal handler function
                                         │
                                         └── Return → Resume program
                                             OR Exit program
```

---

## Common Signals

| Signal    | Value | Default Action | Triggered By                           |
| --------- | ----- | -------------- | -------------------------------------- |
| `SIGINT`  | 2     | Terminate      | Ctrl+C from keyboard                   |
| `SIGTERM` | 15    | Terminate      | `kill <pid>` command                   |
| `SIGABRT` | 6     | Abort          | `abort()` function                     |
| `SIGFPE`  | 8     | Terminate      | Floating-point error (divide by 0)     |
| `SIGSEGV` | 11    | Terminate      | Segmentation fault (bad memory access) |
| `SIGILL`  | 4     | Terminate      | Illegal instruction                    |
| `SIGALRM` | 14    | Terminate      | Timer expired (`alarm()`)              |

---

## Registering a Signal Handler — `signal()`

```cpp
#include <iostream>
#include <csignal>   // for signal handling
using namespace std;

// Signal handler function — must have this exact signature
void myHandler(int sigNum) {
    cout << "\nSignal " << sigNum << " received!" << endl;
    cout << "Cleaning up and exiting..." << endl;
    exit(0);
}

int main() {
    // Register handler for SIGINT (Ctrl+C)
    signal(SIGINT, myHandler);

    cout << "Program running. Press Ctrl+C to trigger signal..." << endl;

    // Infinite loop — waiting for signal
    while (true) {
        cout << "Working..." << endl;
        // sleep(1);  // sleep 1 second per loop
    }

    return 0;
}
```

```
User presses Ctrl+C
         │
         ▼
   OS sends SIGINT (2) to process
         │
         ▼
   signal() lookup: "Is there a handler for SIGINT?"
         │
    YES ─┘
         │
         ▼
   myHandler(2) called
         │
         ▼
   "Signal 2 received! Cleaning up..."
         │
         ▼
   exit(0)
```

---

## `signal()` Function Signature

```cpp
#include <csignal>

void (*signal(int signum, void (*handler)(int)))(int);

// Simpler way to read it:
signal(SIGNAL_NUMBER, handlerFunction);
//       │                  │
//  which signal      function to call when signal arrives
```

Special handler values:

- `SIG_DFL` — restore the **default** behavior
- `SIG_IGN` — **ignore** the signal

```cpp
signal(SIGINT, SIG_IGN);    // ignore Ctrl+C (program won't stop!)
signal(SIGTERM, SIG_DFL);   // restore default terminate behavior
```

---

## Sending Signals — `raise()`

Your program can send a signal to **itself**:

```cpp
#include <csignal>
#include <iostream>
using namespace std;

void handler(int sig) {
    if (sig == SIGABRT) {
        cout << "Caught SIGABRT! Custom abort handling." << endl;
    }
}

int main() {
    signal(SIGABRT, handler);

    cout << "About to raise SIGABRT..." << endl;
    raise(SIGABRT);    // send SIGABRT to self
    cout << "After raise (only reached if handler returns)" << endl;

    return 0;
}
```

---

## Practical Example: Graceful Shutdown

A real-world use: catch SIGTERM/SIGINT to save state before quitting.

```cpp
#include <iostream>
#include <csignal>
#include <fstream>
using namespace std;

bool running = true;

void shutdownHandler(int sig) {
    cout << "\n[SIGNAL] Shutdown signal received (" << sig << ")" << endl;
    cout << "[SIGNAL] Saving data..." << endl;

    // Simulate saving data
    ofstream f("save_state.txt");
    f << "Progress saved at shutdown" << endl;
    f.close();

    cout << "[SIGNAL] Data saved. Goodbye!" << endl;
    running = false;   // signal main loop to stop cleanly
}

int main() {
    signal(SIGINT, shutdownHandler);   // Ctrl+C
    signal(SIGTERM, shutdownHandler);  // kill command

    cout << "Server started. Ctrl+C to stop..." << endl;

    int tick = 0;
    while (running) {
        cout << "Tick " << tick++ << endl;
        // normally: sleep(1) or process work
        if (tick > 5) break;  // stop after 5 for demo
    }

    cout << "Main loop ended cleanly." << endl;
    return 0;
}
```

---

## Signal Handling Flowchart

```
Program Running
      │
      │ ◄──────── normal work ────────
      │
  SIGNAL ARRIVES
      │
      ▼
  ┌────────────────────────────────────┐
  │  Is signal registered with signal()?│
  └────────────────────────────────────┘
      │                      │
    YES                      NO
      │                      │
      ▼                      ▼
  Run handler(signum)    Default OS action
      │                  (usually terminate)
      ▼
  Handler returns?
      │          │
    YES          NO (exit called inside handler)
      │          │
      ▼          ▼
  Resume        Program
  program       exits
```

---

## Important Limitations of Signal Handlers

> ⚠️ Signal handlers run asynchronously — they can interrupt your code at ANY point. This means:

```
DO in signal handlers:              DON'T in signal handlers:
────────────────────────            ─────────────────────────────
✅ Set a flag (volatile bool)       ❌ Call cout / printf (not async-safe)
✅ call _Exit() or abort()          ❌ Call new / delete
✅ call write() (POSIX)             ❌ Acquire mutexes
✅ read/write volatile variables    ❌ Call most library functions
```

**Safe pattern** — set a flag in handler, check it in main loop:

```cpp
volatile sig_atomic_t stopFlag = 0;   // special type safe for signals

void handler(int) {
    stopFlag = 1;   // just set a flag — nothing else!
}

int main() {
    signal(SIGINT, handler);
    while (!stopFlag) {
        // do work...
        // ...save data, cleanup here safely
    }
    cout << "Exiting cleanly." << endl;
}
```

---

## Quick Summary

| Function                | Purpose                                |
| ----------------------- | -------------------------------------- |
| `signal(sig, handler)`  | Register handler for a signal          |
| `signal(sig, SIG_DFL)`  | Restore default behavior               |
| `signal(sig, SIG_IGN)`  | Ignore the signal                      |
| `raise(sig)`            | Send a signal to yourself              |
| `SIGINT`                | Ctrl+C interrupt                       |
| `SIGTERM`               | Termination request                    |
| `SIGABRT`               | Abort signal                           |
| `SIGSEGV`               | Segmentation fault                     |
| `volatile sig_atomic_t` | Safe variable type for signal handlers |
