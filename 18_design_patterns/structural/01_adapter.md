# Adapter Pattern

**Category:** Structural

---

## What Is It?

The **Adapter** pattern allows objects with **incompatible interfaces to work together**. It acts as a wrapper that translates one interface into another.

> 🔁 **Analogy:** A power plug adapter when you travel internationally. Your laptop charger has a US 2-pin plug, but the wall socket in Europe is a 2-round-pin. The adapter makes them compatible without changing either the charger or the wall.

---

## When to Use It?

- You want to use an existing class but its interface doesn't match what you need
- You're integrating a third-party or legacy library
- You want to reuse several existing subclasses that lack a common interface

---

## Structure

```
Client ──calls──► Target (interface)
                      △
                      │
                  Adapter
                  │ +request()   ← Client calls this
                  │     │
                  │     └──translates to──►  Adaptee
                  │                         │ +specificRequest()
                  │                         │ (old/incompatible interface)
                  └─────────────────────────┘
```

---

## C++ Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// ============ Target Interface (what client expects) ============
class MediaPlayer {
public:
    virtual void play(const string& filename) = 0;
    virtual ~MediaPlayer() {}
};

// ============ Adaptee (old/incompatible class) ============
class LegacyAudioPlayer {
public:
    void playMP3(const string& file) {
        cout << "[LegacyPlayer] Playing MP3: " << file << endl;
    }

    void playWAV(const string& file) {
        cout << "[LegacyPlayer] Playing WAV: " << file << endl;
    }
};

class LegacyVideoPlayer {
public:
    void playMP4(const string& file) {
        cout << "[LegacyVideo] Playing MP4: " << file << endl;
    }
};

// ============ Adapter ============
class MediaAdapter : public MediaPlayer {
    LegacyAudioPlayer audioPlayer;
    LegacyVideoPlayer videoPlayer;

public:
    void play(const string& filename) override {
        // Extract extension
        string ext = filename.substr(filename.find_last_of('.') + 1);

        if (ext == "mp3") {
            audioPlayer.playMP3(filename);
        } else if (ext == "wav") {
            audioPlayer.playWAV(filename);
        } else if (ext == "mp4") {
            videoPlayer.playMP4(filename);
        } else {
            cout << "Unsupported format: " << ext << endl;
        }
    }
};

// ============ Client code ============
int main() {
    MediaPlayer* player = new MediaAdapter();

    // Client just calls play() — doesn't care about the underlying system
    player->play("song.mp3");
    player->play("sound_effect.wav");
    player->play("video.mp4");
    player->play("unknown.flac");

    delete player;
    return 0;
}
```

Output:

```
[LegacyPlayer] Playing MP3: song.mp3
[LegacyPlayer] Playing WAV: sound_effect.wav
[LegacyVideo] Playing MP4: video.mp4
Unsupported format: flac
```

---

## Another Example: Temperature Sensor Adapter

```cpp
// Old sensor gives Fahrenheit, but our system needs Celsius
class FahrenheitSensor {
public:
    double getTemperatureF() {
        return 98.6;   // returns Fahrenheit
    }
};

// Our app interface
class TemperatureSensor {
public:
    virtual double getTemperatureC() = 0;
    virtual ~TemperatureSensor() {}
};

// Adapter
class FahrenheitToCelsiusAdapter : public TemperatureSensor {
    FahrenheitSensor sensor;
public:
    double getTemperatureC() override {
        double f = sensor.getTemperatureF();
        return (f - 32.0) * 5.0 / 9.0;  // convert F → C
    }
};

int main() {
    TemperatureSensor* sensor = new FahrenheitToCelsiusAdapter();
    cout << "Temperature: " << sensor->getTemperatureC() << "°C" << endl;
    // Output: Temperature: 37°C
    delete sensor;
}
```

---

## Translation Diagram

```
Client                 Adapter                 Adaptee (Legacy)
  │                       │                        │
  │── play("song.mp3") ──►│                        │
  │                       │── extract ext: "mp3"   │
  │                       │── playMP3("song.mp3") ─►│
  │                       │                        │ plays file
  │                       │◄───────────────────────│
  │◄──────────────────────│                        │
  (transparent to client)
```

---

## Pros and Cons

| ✅ Pros                                                  | ❌ Cons                                         |
| -------------------------------------------------------- | ----------------------------------------------- |
| Reuse legacy or third-party code without modifying it    | Adds an extra layer — slightly more indirection |
| Client stays decoupled from adaptee details              | Can be overly complex if there are many formats |
| Single Responsibility — adapter handles translation only | Multiple adapters can get hard to maintain      |

---

> 💡 **Common real-world uses:** Database drivers (ODBC), payment gateway adapters, file format converters, API wrappers.
