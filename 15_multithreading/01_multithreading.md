# Multithreading in C++

> Source reference: https://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm

---

## What Is Multithreading?

A **thread** is a single path of execution in your program. **Multithreading** means running multiple such paths simultaneously — doing several things at the same time.

> 🔁 **Analogy:** A single-threaded program is like one chef in a kitchen — they do everything one step at a time. A multi-threaded program is like a whole kitchen crew — the chef cooks, the sous chef preps vegetables, and the baker handles dessert, all at the same time.

```
Single-threaded:                    Multi-threaded:
──────────────────────────          ─────────────────────────────────
Main Thread                         Main Thread
  │                                   │
  ├─ Task A (2 sec)                    ├─── Thread 1: Task A (2 sec) ───┐
  │                                   │                                 ├── All 3 run
  ├─ Task B (2 sec)                   ├─── Thread 2: Task B (2 sec) ───┤    in parallel
  │                                   │                                 │
  └─ Task C (2 sec)                   └─── Thread 3: Task C (2 sec) ───┘
        │
  Total: 6 seconds                Total: ~2 seconds
```

---

## C++ Thread Library (`<thread>`)

C++11 introduced the `std::thread` class. Include `<thread>` to use it.

### Creating and Running a Thread

```cpp
#include <iostream>
#include <thread>
using namespace std;

void greet(string name) {
    cout << "Hello from thread! Name: " << name << endl;
}

int main() {
    // Create a thread that runs greet()
    thread t(greet, "Alice");

    cout << "Main thread is still running..." << endl;

    t.join();   // Wait for thread t to finish before continuing

    cout << "Thread finished!" << endl;
    return 0;
}
```

```
Timeline:
main() starts
    │
    ├──────────────────────┐
    │                      │ t (thread)
    │ "Main is running"    │ greet("Alice")
    │                      │
    └──── t.join() ────────┘
    │  (waits here)
    │
    "Thread finished!"
```

---

## Thread with Lambda

```cpp
#include <iostream>
#include <thread>
using namespace std;

int main() {
    // Use lambda as thread function
    thread t([]() {
        cout << "Lambda thread running!" << endl;
    });

    t.join();
    return 0;
}
```

---

## `join()` vs `detach()`

```
thread t(someFunction);
       │
       ├── t.join()    → Main thread WAITS for t to finish
       │                 (safe — you know t is done before main exits)
       │
       └── t.detach()  → Main thread DOES NOT wait
                         t runs independently in background
                         (risky — main may exit before t finishes!)
```

```cpp
thread t(someFunction);

// Option 1: join — wait for it
t.join();

// Option 2: detach — let it run on its own
t.detach();

// After join() or detach(), calling join()/detach() again is an error!
// Check first:
if (t.joinable()) {
    t.join();
}
```

---

## Running Multiple Threads

```cpp
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void printNumbers(int id, int count) {
    for (int i = 0; i < count; i++) {
        cout << "Thread " << id << ": " << i << endl;
    }
}

int main() {
    vector<thread> threads;

    // Launch 5 threads
    for (int i = 0; i < 5; i++) {
        threads.emplace_back(printNumbers, i, 3);
    }

    // Wait for all of them
    for (auto& t : threads) {
        t.join();
    }

    cout << "All threads done!" << endl;
    return 0;
}
```

> ⚠️ The output order will be **unpredictable** — threads run concurrently and can interleave.

---

## Race Conditions — The Main Problem

When two threads access the **same variable at the same time**, you get a **race condition** — corrupt data.

```cpp
#include <iostream>
#include <thread>
using namespace std;

int counter = 0;    // shared variable

void increment() {
    for (int i = 0; i < 10000; i++) {
        counter++;    // NOT SAFE! Read-modify-write is not atomic
    }
}

int main() {
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << counter << endl;    // Should be 20000, but often less!
}
```

```
Thread 1 reads counter = 5
Thread 2 reads counter = 5     (SAME VALUE!)
Thread 1 writes counter = 6
Thread 2 writes counter = 6    (INCREMENT LOST!)
Result: 6 instead of 7
```

---

## `mutex` — Mutual Exclusion Lock

A **mutex** is a lock that only one thread can hold at a time. It protects shared data.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
mutex mtx;     // the lock

void safeIncrement() {
    for (int i = 0; i < 10000; i++) {
        mtx.lock();       // grab the lock
        counter++;        // safe — only one thread here at a time
        mtx.unlock();     // release the lock
    }
}

int main() {
    thread t1(safeIncrement);
    thread t2(safeIncrement);

    t1.join();
    t2.join();

    cout << counter << endl;    // Always 20000 now!
}
```

---

## `lock_guard` — Automatic Mutex Management (Prefer This!)

`lock_guard` automatically unlocks the mutex when it goes out of scope — even if an exception is thrown:

```cpp
#include <mutex>

mutex mtx;
int counter = 0;

void safeIncrement() {
    for (int i = 0; i < 10000; i++) {
        lock_guard<mutex> guard(mtx);   // locks on creation
        counter++;
        // guard automatically unlocks here (end of scope)
    }
}
```

---

## `std::atomic` — Lock-Free for Simple Values

For simple operations on single variables, `std::atomic` is faster than a mutex:

```cpp
#include <atomic>
#include <thread>
using namespace std;

atomic<int> counter(0);   // atomic integer

void increment() {
    for (int i = 0; i < 10000; i++) {
        counter++;   // atomic — thread-safe, no mutex needed!
    }
}
```

```
When to use what:
  Simple int/bool operations  → std::atomic
  Complex operations on data  → std::mutex + lock_guard
  Waiting for a condition     → std::condition_variable
```

---

## Thread Lifecycle Diagram

```
                    ┌──────────┐
                    │  thread  │
                    │  t(func) │
                    └────┬─────┘
                         │ created
                         ▼
                    ┌──────────┐
                    │ Runnable │  ← waiting for CPU time
                    └────┬─────┘
                         │ CPU assigned
                         ▼
                    ┌──────────┐
                    │ Running  │  ← executing func()
                    └────┬─────┘
                    ┌────┴─────┐
                    │          │
              waiting for    func() done
              mutex/IO         │
                    │          ▼
                    │    ┌──────────┐
                    │    │ Finished │
                    │    └────┬─────┘
                    │         │
                    └─────────┘
                              │ t.join() or t.detach()
                              ▼
                          Destroyed
```

---

## Quick Summary

| Concept           | Header     | Purpose                        |
| ----------------- | ---------- | ------------------------------ |
| `std::thread`     | `<thread>` | Create and run a thread        |
| `t.join()`        | —          | Wait for thread to finish      |
| `t.detach()`      | —          | Let thread run independently   |
| `std::mutex`      | `<mutex>`  | Lock shared data               |
| `std::lock_guard` | `<mutex>`  | Auto-unlocking mutex wrapper   |
| `std::atomic<T>`  | `<atomic>` | Lock-free thread-safe variable |

> 💡 **Compile with threading enabled:** `g++ -std=c++11 -pthread file.cpp -o file`
