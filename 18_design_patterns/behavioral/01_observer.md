# Observer Pattern

**Category:** Behavioral

---

## What Is It?

The **Observer** pattern defines a one-to-many relationship: when one object (the **Subject**) changes state, all its dependents (**Observers**) are automatically notified and updated.

> 🔁 **Analogy:** A YouTube channel (Subject) and its subscribers (Observers). When the channel posts a new video, ALL subscribers get notified automatically. Subscribers can join or leave any time without the channel caring.

---

## When to Use It?

- An object change should trigger updates in other objects, and you don't know how many
- Objects should be able to notify others without knowing who they are
- Event systems, GUIs, reactive programming, pub/sub systems

---

## Structure

```
┌───────────────────────┐         ┌──────────────┐
│       Subject         │         │   Observer   │
├───────────────────────┤         │  (interface) │
│ -observers: list      │◄────────├──────────────┤
│ +attach(Observer*)    │         │ +update()    │
│ +detach(Observer*)    │         └──────────────┘
│ +notify()             │                △
└───────────────────────┘         ┌──────┴──────┐
                                ObserverA    ObserverB
                                │ update()    │ update()
```

---

## C++ Implementation: Weather Station

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ============ Observer Interface ============
class Observer {
public:
    virtual void update(float temp, float humidity, float pressure) = 0;
    virtual ~Observer() {}
};

// ============ Subject Interface ============
class Subject {
public:
    virtual void attach(Observer* o) = 0;
    virtual void detach(Observer* o) = 0;
    virtual void notify() = 0;
    virtual ~Subject() {}
};

// ============ Concrete Subject ============
class WeatherStation : public Subject {
    vector<Observer*> observers;
    float temperature, humidity, pressure;

public:
    void attach(Observer* o) override {
        observers.push_back(o);
        cout << "[Station] Observer registered" << endl;
    }

    void detach(Observer* o) override {
        observers.erase(remove(observers.begin(), observers.end(), o), observers.end());
        cout << "[Station] Observer unregistered" << endl;
    }

    void notify() override {
        for (Observer* o : observers) {
            o->update(temperature, humidity, pressure);
        }
    }

    // When data changes, notify all
    void setMeasurements(float temp, float hum, float press) {
        temperature = temp;
        humidity    = hum;
        pressure    = press;
        cout << "\n[Station] New data: T=" << temp << "°C H=" << hum << "% P=" << press << "hPa" << endl;
        notify();
    }
};

// ============ Concrete Observers ============
class PhoneDisplay : public Observer {
    string owner;
public:
    PhoneDisplay(string name) : owner(name) {}

    void update(float temp, float humidity, float pressure) override {
        cout << "[" << owner << "'s Phone] Temp: " << temp
             << "°C | Humidity: " << humidity << "%" << endl;
    }
};

class WeatherWebsite : public Observer {
public:
    void update(float temp, float humidity, float pressure) override {
        cout << "[Website] Weather update: " << temp << "°C, "
             << humidity << "% humidity, " << pressure << " hPa" << endl;
    }
};

class AlertSystem : public Observer {
public:
    void update(float temp, float humidity, float pressure) override {
        if (temp > 38.0f) {
            cout << "[ALERT!] HEAT WARNING: " << temp << "°C" << endl;
        }
        if (humidity > 90.0f) {
            cout << "[ALERT!] HIGH HUMIDITY: " << humidity << "%" << endl;
        }
    }
};

int main() {
    WeatherStation station;

    PhoneDisplay alice("Alice");
    PhoneDisplay bob("Bob");
    WeatherWebsite website;
    AlertSystem alerts;

    station.attach(&alice);
    station.attach(&bob);
    station.attach(&website);
    station.attach(&alerts);

    station.setMeasurements(25.0f, 65.0f, 1013.0f);
    station.setMeasurements(40.0f, 92.0f, 1010.0f);   // triggers alerts!

    cout << "\nBob unsubscribes:" << endl;
    station.detach(&bob);
    station.setMeasurements(22.0f, 55.0f, 1015.0f);   // Bob doesn't get this

    return 0;
}
```

Output:

```
[Station] Observer registered ×4

[Station] New data: T=25°C H=65% P=1013hPa
[Alice's Phone] Temp: 25°C | Humidity: 65%
[Bob's Phone] Temp: 25°C | Humidity: 65%
[Website] Weather update: 25°C, 65% humidity, 1013 hPa

[Station] New data: T=40°C H=92% P=1010hPa
[Alice's Phone] Temp: 40°C | Humidity: 92%
[Bob's Phone] Temp: 40°C | Humidity: 92%
[Website] Weather update: 40°C, 92% humidity, 1010 hPa
[ALERT!] HEAT WARNING: 40°C
[ALERT!] HIGH HUMIDITY: 92%

Bob unsubscribes:
[Station] Observer unregistered

[Station] New data: T=22°C H=55% P=1015hPa
[Alice's Phone] Temp: 22°C | Humidity: 55%
[Website] Weather update: 22°C, 55% humidity, 1015 hPa
```

---

## Observer Notification Flow

```
WeatherStation.setMeasurements(40, 92, 1010)
         │
         ▼
    data updated internally
         │
         ▼
    notify()
     │
     ├──► alice.update(40, 92, 1010)   → displays on Alice's phone
     ├──► bob.update(40, 92, 1010)     → displays on Bob's phone
     ├──► website.update(40, 92, 1010) → updates website
     └──► alerts.update(40, 92, 1010)  → triggers heat/humidity alerts
```

---

## Pros and Cons

| ✅ Pros                                               | ❌ Cons                                          |
| ----------------------------------------------------- | ------------------------------------------------ |
| Loose coupling — subject doesn't know who observes it | Unexpected updates if subject changes frequently |
| Observers can be added/removed at runtime             | Debugging notification chains can be hard        |
| Supports broadcast communication                      | Memory leaks if observers not properly detached  |

---

> 💡 **Used everywhere:** Qt signals/slots, JavaScript `addEventListener`, `std::function` callbacks, MVC (Model notifies View), React state, Redux store subscriptions.
