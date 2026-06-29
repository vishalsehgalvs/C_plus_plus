// ============================================================
// 07_stacks_queues.cpp  —  LeetCode Style
// Problems: Valid Parentheses, Min Stack,
//           LRU Cache, Sliding Window Maximum
// ============================================================

#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_map>
#include <list>
#include <string>
#include <vector>
#include <climits>
using namespace std;

// ============================================================
// Problem 1: Valid Parentheses (LeetCode #20)
// Check if brackets are properly nested and closed.
// Time: O(n)  Space: O(n)
// ============================================================
class ValidParentheses
{
public:
    bool solve(string s)
    {
        stack<char> st;
        for (char c : s)
        {
            if (c == '(' || c == '[' || c == '{')
            {
                st.push(c);
            }
            else
            {
                if (st.empty())
                    return false;
                char top = st.top();
                st.pop();
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{'))
                    return false;
            }
        }
        return st.empty(); // all opened must be closed
    }
};

// ============================================================
// Problem 2: Min Stack (LeetCode #155)
// Stack that supports push, pop, top, and getMin in O(1).
// Approach: Pair each value with the minimum seen so far
// Time: O(1) all operations  Space: O(n)
// ============================================================
class MinStack
{
    stack<pair<int, int>> st; // (value, min_so_far)
public:
    void push(int val)
    {
        int currentMin = st.empty() ? val : min(val, st.top().second);
        st.push({val, currentMin});
    }
    void pop() { st.pop(); }
    int top() { return st.top().first; }
    int getMin() { return st.top().second; }
};

// ============================================================
// Problem 3: LRU Cache (LeetCode #146)
// Least Recently Used cache with O(1) get and put.
// Approach: doubly-linked list + hash map
//   - List front = most recently used
//   - List back  = least recently used
// Time: O(1) both operations  Space: O(capacity)
// ============================================================
class LRUCache
{
    int capacity;
    list<pair<int, int>> cache;                             // (key, value) — front = MRU
    unordered_map<int, list<pair<int, int>>::iterator> map; // key → iterator

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key)
    {
        if (!map.count(key))
            return -1;
        // Move to front (most recently used)
        cache.splice(cache.begin(), cache, map[key]);
        return map[key]->second;
    }

    void put(int key, int value)
    {
        if (map.count(key))
        {
            map[key]->second = value;
            cache.splice(cache.begin(), cache, map[key]);
        }
        else
        {
            if ((int)cache.size() == capacity)
            {
                // Evict least recently used (back of list)
                map.erase(cache.back().first);
                cache.pop_back();
            }
            cache.push_front({key, value});
            map[key] = cache.begin();
        }
    }
};

// ============================================================
// Problem 4: Sliding Window Maximum (LeetCode #239)
// Find max in every window of size k.
// Approach: Monotonic deque (stores indices)
// Time: O(n)  Space: O(k)
// ============================================================
class SlidingWindowMax
{
public:
    vector<int> solve(vector<int> &nums, int k)
    {
        deque<int> dq; // stores indices; front = largest element's index
        vector<int> result;

        for (int i = 0; i < (int)nums.size(); i++)
        {
            // Remove indices outside window
            while (!dq.empty() && dq.front() <= i - k)
                dq.pop_front();

            // Remove smaller elements from back (they can never be max)
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();

            dq.push_back(i);

            // Start recording results once first window is complete
            if (i >= k - 1)
                result.push_back(nums[dq.front()]);
        }
        return result;
    }
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Valid Parentheses
    cout << "=== Valid Parentheses ===" << endl;
    {
        ValidParentheses s;
        cout << boolalpha;
        cout << s.solve("()") << endl;     // true
        cout << s.solve("()[]{}") << endl; // true
        cout << s.solve("(]") << endl;     // false
        cout << s.solve("([)]") << endl;   // false
        cout << s.solve("{[]}") << endl;   // true
    }

    // Min Stack
    cout << "\n=== Min Stack ===" << endl;
    {
        MinStack ms;
        ms.push(-2);
        ms.push(0);
        ms.push(-3);
        cout << ms.getMin() << endl; // -3
        ms.pop();
        cout << ms.top() << endl;    // 0
        cout << ms.getMin() << endl; // -2
    }

    // LRU Cache
    cout << "\n=== LRU Cache ===" << endl;
    {
        LRUCache lru(2);
        lru.put(1, 1);
        lru.put(2, 2);
        cout << lru.get(1) << endl; // 1   (key 1 is now MRU)
        lru.put(3, 3);              // evicts key 2 (LRU)
        cout << lru.get(2) << endl; // -1  (evicted)
        lru.put(4, 4);              // evicts key 1 (now LRU after key 3 was inserted)
        cout << lru.get(1) << endl; // -1  (evicted)
        cout << lru.get(3) << endl; // 3
        cout << lru.get(4) << endl; // 4
    }

    // Sliding Window Maximum
    cout << "\n=== Sliding Window Maximum ===" << endl;
    {
        SlidingWindowMax s;
        vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
        auto res = s.solve(nums, 3);
        for (int x : res)
            cout << x << " ";
        cout << endl; // 3 3 5 5 6 7

        vector<int> nums2 = {1};
        auto res2 = s.solve(nums2, 1);
        cout << res2[0] << endl; // 1
    }

    return 0;
}
