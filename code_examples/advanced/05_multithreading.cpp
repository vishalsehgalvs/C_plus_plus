// ============================================================
// 05_multithreading.cpp  —  Advanced
// std::thread, mutex, lock_guard, condition_variable,
// atomic, thread pool pattern
// Compile: g++ -std=c++11 -pthread 05_multithreading.cpp
// ============================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <queue>
#include <functional>
#include <chrono>
using namespace std;

// ================================================================
// 1. Basic threads
// ================================================================
void worker(int id, int repetitions)
{
    for (int i = 0; i < repetitions; i++)
    {
        cout << "Thread " << id << ": iteration " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

// ================================================================
// 2. Race condition and mutex fix
// ================================================================
int sharedCounter = 0;
mutex counterMutex;
atomic<int> atomicCounter(0);

void unsafeIncrement(int times)
{
    for (int i = 0; i < times; i++)
        sharedCounter++; // UNSAFE
}

void safeIncrement(int times)
{
    for (int i = 0; i < times; i++)
    {
        lock_guard<mutex> lock(counterMutex);
        sharedCounter++; // SAFE
    }
}

void atomicIncrement(int times)
{
    for (int i = 0; i < times; i++)
        atomicCounter++; // SAFE and FAST
}

// ================================================================
// 3. Producer-Consumer with condition_variable
// ================================================================
class ThreadSafeQueue
{
    queue<int> q;
    mutex mtx;
    condition_variable cv;
    bool done = false;

public:
    void produce(int val)
    {
        {
            lock_guard<mutex> lock(mtx);
            q.push(val);
            cout << "Produced: " << val << endl;
        }
        cv.notify_one(); // wake up one waiting consumer
    }

    bool consume(int &val)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]
                { return !q.empty() || done; });
        if (q.empty())
            return false;
        val = q.front();
        q.pop();
        cout << "Consumed: " << val << endl;
        return true;
    }

    void finish()
    {
        {
            lock_guard<mutex> lock(mtx);
            done = true;
        }
        cv.notify_all();
    }
};

// ================================================================
// 4. Simple Thread Pool
// ================================================================
class ThreadPool
{
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex qMutex;
    condition_variable qCV;
    bool stopping = false;

public:
    ThreadPool(int numThreads)
    {
        for (int i = 0; i < numThreads; i++)
        {
            workers.emplace_back([this]
                                 {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(qMutex);
                        qCV.wait(lock, [this]{ return stopping || !tasks.empty(); });
                        if (stopping && tasks.empty()) return;
                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task();
                } });
        }
    }

    void submit(function<void()> task)
    {
        {
            lock_guard<mutex> lock(qMutex);
            tasks.push(move(task));
        }
        qCV.notify_one();
    }

    ~ThreadPool()
    {
        {
            lock_guard<mutex> lock(qMutex);
            stopping = true;
        }
        qCV.notify_all();
        for (auto &t : workers)
            t.join();
    }
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    cout << "=== Basic Threads ===" << endl;
    thread t1(worker, 1, 3);
    thread t2(worker, 2, 3);
    t1.join();
    t2.join();

    // Atomic counter
    cout << "\n=== Atomic Counter ===" << endl;
    vector<thread> threads;
    for (int i = 0; i < 5; i++)
    {
        threads.emplace_back(atomicIncrement, 1000);
    }
    for (auto &t : threads)
        t.join();
    cout << "Atomic counter: " << atomicCounter.load() << " (should be 5000)" << endl;

    // Producer-Consumer
    cout << "\n=== Producer-Consumer ===" << endl;
    {
        ThreadSafeQueue tsq;

        thread producer([&tsq]()
                        {
            for (int i = 1; i <= 5; i++) {
                tsq.produce(i * 10);
                this_thread::sleep_for(chrono::milliseconds(20));
            }
            tsq.finish(); });

        thread consumer([&tsq]()
                        {
            int val;
            while (tsq.consume(val)) {
                // already printed in consume()
            } });

        producer.join();
        consumer.join();
    }

    // Thread pool
    cout << "\n=== Thread Pool ===" << endl;
    {
        ThreadPool pool(3);
        mutex printMtx;

        for (int i = 1; i <= 8; i++)
        {
            pool.submit([i, &printMtx]()
                        {
                this_thread::sleep_for(chrono::milliseconds(50));
                lock_guard<mutex> lock(printMtx);
                cout << "Task " << i << " completed by thread "
                     << this_thread::get_id() << endl; });
        }

        this_thread::sleep_for(chrono::milliseconds(500)); // let tasks run
    }

    return 0;
}
