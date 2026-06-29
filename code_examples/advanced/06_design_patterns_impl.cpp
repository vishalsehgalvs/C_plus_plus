// ============================================================
// 06_design_patterns_impl.cpp  —  Advanced
// Quick implementations of key design patterns in one file
// ============================================================

#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <map>
using namespace std;

// ================================================================
// 1. SINGLETON — one instance only (Meyer's, thread-safe C++11)
// ================================================================
class AppConfig
{
    map<string, string> settings;
    AppConfig()
    {
        settings["theme"] = "dark";
        settings["lang"] = "en";
    }
    AppConfig(const AppConfig &) = delete;
    AppConfig &operator=(const AppConfig &) = delete;

public:
    static AppConfig &get()
    {
        static AppConfig instance;
        return instance;
    }
    string getSetting(const string &key) { return settings.count(key) ? settings[key] : ""; }
    void setSetting(const string &key, const string &val) { settings[key] = val; }
};

// ================================================================
// 2. OBSERVER — event notification system
// ================================================================
class EventBus
{
    map<string, vector<function<void(const string &)>>> listeners;

public:
    void subscribe(const string &event, function<void(const string &)> handler)
    {
        listeners[event].push_back(handler);
    }
    void publish(const string &event, const string &data)
    {
        if (listeners.count(event))
        {
            for (auto &handler : listeners[event])
                handler(data);
        }
    }
};

// ================================================================
// 3. STRATEGY — pluggable algorithm
// ================================================================
class Sorter
{
    function<void(vector<int> &)> strategy;

public:
    void setStrategy(function<void(vector<int> &)> s) { strategy = s; }
    void sort(vector<int> &v)
    {
        if (strategy)
            strategy(v);
    }
};

// ================================================================
// 4. DECORATOR — wrap and extend behavior
// ================================================================
class Logger
{
    function<string(const string &)> pipeline = [](const string &s)
    { return s; };

public:
    Logger &withTimestamp()
    {
        auto prev = pipeline;
        pipeline = [prev](const string &s)
        { return "[2026-06-29] " + prev(s); };
        return *this;
    }
    Logger &withLevel(const string &level)
    {
        auto prev = pipeline;
        pipeline = [prev, level](const string &s)
        { return "[" + level + "] " + prev(s); };
        return *this;
    }
    void log(const string &msg) { cout << pipeline(msg) << endl; }
};

// ================================================================
// 5. FACTORY — create objects by type name
// ================================================================
class Button
{
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

class WinButton : public Button
{
public:
    void render() override { cout << "[ Windows Button ]" << endl; }
};

class MacButton : public Button
{
public:
    void render() override { cout << "( Mac Button )" << endl; }
};

unique_ptr<Button> createButton(const string &platform)
{
    if (platform == "windows")
        return make_unique<WinButton>();
    if (platform == "mac")
        return make_unique<MacButton>();
    return nullptr;
}

// ================================================================
// 6. COMMAND — encapsulate actions + undo
// ================================================================
class TextBuffer
{
    string text;
    vector<pair<string, function<void()>>> history;

public:
    void execute(const string &desc, function<void()> action, function<void()> undo)
    {
        action();
        history.push_back({desc, undo});
    }
    void undo()
    {
        if (!history.empty())
        {
            cout << "Undoing: " << history.back().first << endl;
            history.back().second();
            history.pop_back();
        }
    }
    void append(const string &s)
    {
        string old = text;
        execute("append '" + s + "'", [&, s]
                { text += s; cout << "text: [" << text << "]" << endl; }, [&, old]
                { text = old; cout << "text: [" << text << "]" << endl; });
    }
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Singleton
    cout << "=== Singleton Config ===" << endl;
    AppConfig::get().setSetting("theme", "light");
    cout << "theme: " << AppConfig::get().getSetting("theme") << endl;
    cout << "lang:  " << AppConfig::get().getSetting("lang") << endl;

    // Observer / EventBus
    cout << "\n=== EventBus ===" << endl;
    EventBus bus;
    bus.subscribe("login", [](const string &d)
                  { cout << "[Auth] User logged in: " << d << endl; });
    bus.subscribe("login", [](const string &d)
                  { cout << "[Log] Login event: " << d << endl; });
    bus.subscribe("logout", [](const string &d)
                  { cout << "[Auth] Logged out: " << d << endl; });
    bus.publish("login", "alice@example.com");
    bus.publish("logout", "alice@example.com");

    // Strategy
    cout << "\n=== Strategy Sort ===" << endl;
    Sorter sorter;
    vector<int> v = {5, 2, 8, 1, 9};
    sorter.setStrategy([](vector<int> &v)
                       { sort(v.begin(), v.end()); });
    sorter.sort(v);
    for (int x : v)
        cout << x << " ";
    cout << endl;
    sorter.setStrategy([](vector<int> &v)
                       { sort(v.rbegin(), v.rend()); });
    sorter.sort(v);
    for (int x : v)
        cout << x << " ";
    cout << endl;

    // Decorator Logger
    cout << "\n=== Decorator Logger ===" << endl;
    Logger logger;
    logger.withTimestamp().withLevel("ERROR").log("File not found");
    logger.withLevel("INFO").log("App started");

    // Factory
    cout << "\n=== Factory Button ===" << endl;
    auto btn = createButton("mac");
    if (btn)
        btn->render();

    // Command + Undo
    cout << "\n=== Command Undo ===" << endl;
    TextBuffer buf;
    buf.append("Hello");
    buf.append(", World");
    buf.append("!!!");
    buf.undo();
    buf.undo();

    return 0;
}
