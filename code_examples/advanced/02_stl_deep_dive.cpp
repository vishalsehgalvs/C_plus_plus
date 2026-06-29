// ============================================================
// 02_stl_deep_dive.cpp  —  Advanced
// STL containers and algorithms with real-world patterns
// ============================================================

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>
using namespace std;

int main()
{
    // ================================================================
    // 1. vector — most common container
    // ================================================================
    cout << "=== vector ===" << endl;
    vector<int> v = {5, 2, 8, 1, 9, 3};

    sort(v.begin(), v.end()); // sort ascending
    for (int x : v)
        cout << x << " ";
    cout << endl;

    sort(v.begin(), v.end(), greater<int>()); // sort descending
    for (int x : v)
        cout << x << " ";
    cout << endl;

    // partition: even numbers first
    auto even_first = partition(v.begin(), v.end(), [](int x)
                                { return x % 2 == 0; });
    cout << "Even first: ";
    for (int x : v)
        cout << x << " ";
    cout << endl;

    // accumulate — sum, product, etc.
    int sum = accumulate(v.begin(), v.end(), 0);
    cout << "Sum: " << sum << endl;

    int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());
    cout << "Product: " << product << endl;

    // ================================================================
    // 2. map — sorted key-value pairs
    // ================================================================
    cout << "\n=== map (word count) ===" << endl;
    string text = "the cat sat on the mat the cat";
    map<string, int> wordCount;

    // Count words
    string word;
    for (char c : text)
    {
        if (c == ' ')
        {
            if (!word.empty())
            {
                wordCount[word]++;
                word.clear();
            }
        }
        else
        {
            word += c;
        }
    }
    if (!word.empty())
        wordCount[word]++;

    for (auto &[w, cnt] : wordCount)
    { // structured bindings (C++17)
        cout << w << ": " << cnt << endl;
    }

    // Most frequent word using max_element
    auto maxEntry = max_element(wordCount.begin(), wordCount.end(),
                                [](const auto &a, const auto &b)
                                { return a.second < b.second; });
    cout << "Most frequent: \"" << maxEntry->first << "\" (" << maxEntry->second << ")" << endl;

    // ================================================================
    // 3. unordered_map — O(1) average lookup
    // ================================================================
    cout << "\n=== unordered_map (phone book) ===" << endl;
    unordered_map<string, string> phonebook = {
        {"Alice", "555-1234"},
        {"Bob", "555-5678"},
        {"Carol", "555-9012"}};

    phonebook["Dave"] = "555-3456";

    auto it = phonebook.find("Alice");
    if (it != phonebook.end())
    {
        cout << "Alice's number: " << it->second << endl;
    }

    // ================================================================
    // 4. set — sorted unique elements
    // ================================================================
    cout << "\n=== set ===" << endl;
    set<int> s = {5, 3, 8, 1, 5, 3, 9}; // duplicates removed!
    for (int x : s)
        cout << x << " "; // sorted: 1 3 5 8 9
    cout << endl;

    // Find and erase
    s.erase(3);
    cout << "After erase(3): ";
    for (int x : s)
        cout << x << " ";
    cout << endl;

    cout << "Contains 5? " << (s.count(5) ? "yes" : "no") << endl;

    // ================================================================
    // 5. priority_queue — max-heap by default
    // ================================================================
    cout << "\n=== priority_queue ===" << endl;
    priority_queue<int> maxHeap;
    for (int x : {5, 3, 8, 1, 9, 2})
        maxHeap.push(x);

    cout << "Max-heap order: ";
    while (!maxHeap.empty())
    {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;

    // Min-heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : {5, 3, 8, 1, 9, 2})
        minHeap.push(x);
    cout << "Min-heap order: ";
    while (!minHeap.empty())
    {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;

    // ================================================================
    // 6. Algorithms — transform, filter, etc.
    // ================================================================
    cout << "\n=== Algorithms ===" << endl;
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // transform — apply function to every element
    vector<int> squares;
    transform(nums.begin(), nums.end(), back_inserter(squares),
              [](int x)
              { return x * x; });
    cout << "Squares: ";
    for (int x : squares)
        cout << x << " ";
    cout << endl;

    // copy_if — filter elements
    vector<int> evens;
    copy_if(nums.begin(), nums.end(), back_inserter(evens),
            [](int x)
            { return x % 2 == 0; });
    cout << "Evens:   ";
    for (int x : evens)
        cout << x << " ";
    cout << endl;

    // for_each
    cout << "Doubled: ";
    for_each(nums.begin(), nums.end(), [](int &x)
             { x *= 2; });
    for (int x : nums)
        cout << x << " ";
    cout << endl;

    // binary_search (on sorted range)
    vector<int> sorted = {1, 3, 5, 7, 9, 11, 13};
    cout << "\nbinary_search(7): " << binary_search(sorted.begin(), sorted.end(), 7) << endl;
    cout << "binary_search(4): " << binary_search(sorted.begin(), sorted.end(), 4) << endl;

    // lower_bound / upper_bound
    auto lb = lower_bound(sorted.begin(), sorted.end(), 7);
    cout << "lower_bound(7) points to: " << *lb << endl;

    return 0;
}
