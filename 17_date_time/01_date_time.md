# Date and Time in C++

> Source reference: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm

---

## Overview: Two Ways to Handle Time in C++

```
C++ Date/Time Options:
──────────────────────────────────────────────────────────────
Old Way (C-style, <ctime>):          Modern Way (C++11, <chrono>):
  • struct tm                          • std::chrono::duration
  • time_t                             • std::chrono::time_point
  • time(), localtime(), strftime()    • steady_clock, system_clock
  • Simple, works everywhere           • Precise, type-safe, composable
──────────────────────────────────────────────────────────────
```

---

## The C-Style Way (`<ctime>`)

### Getting the Current Time

```cpp
#include <iostream>
#include <ctime>
using namespace std;

int main() {
    // time_t = seconds since Jan 1, 1970 (Unix epoch)
    time_t now = time(nullptr);
    cout << "Raw timestamp: " << now << endl;   // e.g., 1750000000

    // Convert to human-readable string
    cout << "Current time: " << ctime(&now);    // e.g., Mon Jun 29 14:30:00 2026

    return 0;
}
```

### `struct tm` — Breaking Time Into Parts

```cpp
#include <iostream>
#include <ctime>
using namespace std;

int main() {
    time_t now = time(nullptr);

    // Convert to local time struct
    struct tm* localTime = localtime(&now);

    cout << "Year:   " << 1900 + localTime->tm_year << endl;
    cout << "Month:  " << 1 + localTime->tm_mon << endl;   // 0-indexed!
    cout << "Day:    " << localTime->tm_mday << endl;
    cout << "Hour:   " << localTime->tm_hour << endl;
    cout << "Minute: " << localTime->tm_min << endl;
    cout << "Second: " << localTime->tm_sec << endl;
    cout << "Weekday:" << localTime->tm_wday << endl;   // 0=Sunday

    return 0;
}
```

```
struct tm breakdown:
┌──────────────┬───────────────────────────────────────┐
│ tm_year      │ Years since 1900 (add 1900 to get year)│
│ tm_mon       │ Month 0-11 (add 1 to get 1-12)         │
│ tm_mday      │ Day of month (1-31)                    │
│ tm_hour      │ Hour (0-23)                            │
│ tm_min       │ Minute (0-59)                          │
│ tm_sec       │ Second (0-60, 60 for leap second)      │
│ tm_wday      │ Day of week (0=Sunday, 6=Saturday)     │
│ tm_yday      │ Day of year (0-365)                    │
│ tm_isdst     │ Daylight saving time flag              │
└──────────────┴───────────────────────────────────────┘
```

### Formatting Time with `strftime()`

```cpp
#include <iostream>
#include <ctime>
using namespace std;

int main() {
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);

    char buffer[80];

    // Custom formats using strftime
    strftime(buffer, 80, "%Y-%m-%d", t);
    cout << buffer << endl;          // 2026-06-29

    strftime(buffer, 80, "%H:%M:%S", t);
    cout << buffer << endl;          // 14:30:00

    strftime(buffer, 80, "%d %B %Y", t);
    cout << buffer << endl;          // 29 June 2026

    strftime(buffer, 80, "%A, %B %d %Y", t);
    cout << buffer << endl;          // Monday, June 29 2026

    return 0;
}
```

Common `strftime` format codes:

| Code | Meaning           | Example |
| ---- | ----------------- | ------- |
| `%Y` | 4-digit year      | 2026    |
| `%m` | Month (01-12)     | 06      |
| `%d` | Day (01-31)       | 29      |
| `%H` | Hour 24h (00-23)  | 14      |
| `%M` | Minute (00-59)    | 30      |
| `%S` | Second (00-59)    | 00      |
| `%A` | Full weekday name | Monday  |
| `%B` | Full month name   | June    |
| `%I` | Hour 12h (01-12)  | 02      |
| `%p` | AM/PM             | PM      |

---

### Measuring Elapsed Time (C-style)

```cpp
#include <iostream>
#include <ctime>
using namespace std;

int main() {
    clock_t start = clock();

    // Simulate work
    long sum = 0;
    for (long i = 0; i < 100000000; i++) {
        sum += i;
    }

    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Elapsed: " << elapsed << " seconds" << endl;

    return 0;
}
```

---

## The Modern Way: `<chrono>` (C++11)

`std::chrono` is precise, type-safe, and composable.

### Duration Types

```cpp
#include <chrono>
using namespace std::chrono;

hours h(2);                  // 2 hours
minutes m(30);               // 30 minutes
seconds s(45);               // 45 seconds
milliseconds ms(500);        // 500 milliseconds
microseconds us(1000);       // 1000 microseconds
nanoseconds ns(100);         // 100 nanoseconds

// Convert between units
auto total = h + m + s;      // 2h 30m 45s
cout << duration_cast<seconds>(total).count() << "s" << endl;  // 9045s
```

### Clocks

```
std::chrono clocks:
─────────────────────────────────────────────────────
system_clock    │ Wall clock (real world time). Can go backwards.
steady_clock    │ Always goes forward. Best for measuring elapsed time.
high_resolution_clock │ Highest precision available.
─────────────────────────────────────────────────────
```

### Measuring Elapsed Time (Modern)

```cpp
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    auto start = steady_clock::now();

    // Simulate work
    long sum = 0;
    for (long i = 0; i < 100000000; i++) sum += i;

    auto end = steady_clock::now();

    // Measure in different units
    auto elapsedMs  = duration_cast<milliseconds>(end - start).count();
    auto elapsedUs  = duration_cast<microseconds>(end - start).count();
    auto elapsedNs  = duration_cast<nanoseconds>(end - start).count();

    cout << "Elapsed: " << elapsedMs << " ms" << endl;
    cout << "Elapsed: " << elapsedUs << " μs" << endl;
    cout << "Elapsed: " << elapsedNs << " ns" << endl;

    return 0;
}
```

### Getting Current System Time (Modern)

```cpp
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;

int main() {
    // Get current time as time_point
    auto now = system_clock::now();

    // Convert to time_t for display
    time_t t = system_clock::to_time_t(now);
    cout << "Current time: " << ctime(&t);

    // Get epoch time in seconds
    auto epoch = now.time_since_epoch();
    auto seconds_since_epoch = duration_cast<seconds>(epoch).count();
    cout << "Seconds since epoch: " << seconds_since_epoch << endl;

    return 0;
}
```

---

## Time Flow Diagram

```
Time as C++ Sees It:

Unix Epoch (Jan 1, 1970 00:00:00 UTC)
       │
       │◄──────── time_t (seconds since epoch) ────────────────►
       │
       ▼
   time(nullptr) ──► time_t
       │
       ├── localtime() ──► struct tm ──► strftime() ──► formatted string
       │
       └── gmtime()   ──► struct tm (UTC)

Modern:
   system_clock::now() ──► time_point
       │
       ├── to_time_t() ──► time_t ──► ctime()
       │
       └── time_since_epoch() ──► duration ──► .count()
```

---

## Creating a Timer Class (Practical Example)

```cpp
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Timer {
    steady_clock::time_point startTime;

public:
    Timer() { startTime = steady_clock::now(); }

    void reset() { startTime = steady_clock::now(); }

    double elapsedMs() {
        auto now = steady_clock::now();
        return duration_cast<microseconds>(now - startTime).count() / 1000.0;
    }

    double elapsedSec() {
        return elapsedMs() / 1000.0;
    }
};

int main() {
    Timer t;

    // Some work
    long sum = 0;
    for (long i = 0; i < 10000000; i++) sum += i;

    cout << "Done in: " << t.elapsedMs() << " ms" << endl;
    cout << "Done in: " << t.elapsedSec() << " sec" << endl;

    return 0;
}
```

---

## Quick Summary

| Task          | C-style         | Modern (chrono)         |
| ------------- | --------------- | ----------------------- |
| Current time  | `time(nullptr)` | `system_clock::now()`   |
| Elapsed time  | `clock()`       | `steady_clock::now()`   |
| Format string | `strftime()`    | C++20: `std::format()`  |
| Time struct   | `struct tm`     | `time_point<Clock>`     |
| Duration      | `difftime()`    | `duration_cast<unit>()` |

> 💡 **Use `<chrono>` for timing/benchmarking.** Use `<ctime>` when you need formatted date strings (until C++20's `std::format` or `std::chrono` date formatting).
