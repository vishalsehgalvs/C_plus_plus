// ============================================================
// 08_hashmaps_sets.cpp  —  LeetCode Style
// Problems: Group Anagrams, Top K Frequent Elements,
//           Two Sum with HashMap, Longest Consecutive Sequence
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;

// ============================================================
// Problem 1: Group Anagrams (LeetCode #49)
// Group strings that are anagrams of each other.
// Approach: Sort each string as a key for the hashmap.
// Time: O(n * k log k)  where k = max string length
// Space: O(n * k)
// ============================================================
class GroupAnagrams
{
public:
    vector<vector<string>> solve(vector<string> &strs)
    {
        unordered_map<string, vector<string>> groups;
        for (const string &s : strs)
        {
            string key = s;
            sort(key.begin(), key.end()); // sorted form = canonical key
            groups[key].push_back(s);
        }
        vector<vector<string>> result;
        for (auto &[key, group] : groups)
            result.push_back(group);
        return result;
    }
};

// ============================================================
// Problem 2: Top K Frequent Elements (LeetCode #347)
// Return k most frequent elements.
// Approach: HashMap count + min-heap of size k
// Time: O(n log k)  Space: O(n)
// ============================================================
class TopKFrequent
{
public:
    vector<int> solve(vector<int> &nums, int k)
    {
        // Count frequencies
        unordered_map<int, int> freq;
        for (int x : nums)
            freq[x]++;

        // Min-heap: (frequency, value) — keeps k largest
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;

        for (auto &[val, count] : freq)
        {
            minHeap.push({count, val});
            if ((int)minHeap.size() > k)
                minHeap.pop(); // kick out smallest
        }

        vector<int> result;
        while (!minHeap.empty())
        {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return result;
    }
};

// ============================================================
// Problem 3: Two Sum (variation) — return values, not indices
// Also shows the canonical HashMap approach clearly.
// Time: O(n)  Space: O(n)
// ============================================================
class TwoSumValues
{
public:
    // Returns whether any two numbers sum to target
    bool solve(vector<int> &nums, int target)
    {
        unordered_set<int> seen;
        for (int x : nums)
        {
            if (seen.count(target - x))
                return true;
            seen.insert(x);
        }
        return false;
    }

    // Count number of pairs
    int countPairs(vector<int> &nums, int target)
    {
        unordered_map<int, int> freq;
        for (int x : nums)
            freq[x]++;
        int pairs = 0;
        unordered_set<int> visited;
        for (auto &[val, cnt] : freq)
        {
            int complement = target - val;
            if (!visited.count(val) && freq.count(complement))
            {
                if (val == complement)
                    pairs += cnt * (cnt - 1) / 2; // pairs within same value
                else
                    pairs += cnt * freq[complement];
                visited.insert(val);
                visited.insert(complement);
            }
        }
        return pairs;
    }
};

// ============================================================
// Problem 4: Longest Consecutive Sequence (LeetCode #128)
// Find length of longest consecutive sequence in unsorted array.
// Approach: HashSet — start sequences only from their beginning.
// Time: O(n)  Space: O(n)
// ============================================================
class LongestConsecutive
{
public:
    int solve(vector<int> &nums)
    {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLen = 0;

        for (int num : numSet)
        {
            // Only start counting if num-1 is NOT in set
            // (this ensures we only start from the beginning of a sequence)
            if (!numSet.count(num - 1))
            {
                int current = num;
                int length = 1;
                while (numSet.count(current + 1))
                {
                    current++;
                    length++;
                }
                maxLen = max(maxLen, length);
            }
        }
        return maxLen;
    }
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Group Anagrams
    cout << "=== Group Anagrams ===" << endl;
    {
        GroupAnagrams s;
        vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
        auto groups = s.solve(strs);
        for (auto &g : groups)
        {
            cout << "[ ";
            for (auto &w : g)
                cout << w << " ";
            cout << "]" << endl;
        }
        // Expected: [eat,tea,ate] [tan,nat] [bat] (order may vary)
    }

    // Top K Frequent
    cout << "\n=== Top K Frequent Elements ===" << endl;
    {
        TopKFrequent s;
        vector<int> nums = {1, 1, 1, 2, 2, 3};
        auto res = s.solve(nums, 2);
        cout << "Top 2: ";
        for (int x : res)
            cout << x << " ";
        cout << endl; // 1 2 (order may vary)

        vector<int> nums2 = {1};
        auto res2 = s.solve(nums2, 1);
        cout << res2[0] << endl; // 1
    }

    // Two Sum values
    cout << "\n=== Two Sum Values ===" << endl;
    {
        TwoSumValues s;
        vector<int> nums = {1, 5, 3, 4, 2};
        cout << boolalpha;
        cout << s.solve(nums, 6) << endl;      // true  (1+5 or 2+4)
        cout << s.solve(nums, 10) << endl;     // false
        cout << s.countPairs(nums, 6) << endl; // 2 (1+5=6, 2+4=6)
    }

    // Longest Consecutive Sequence
    cout << "\n=== Longest Consecutive Sequence ===" << endl;
    {
        LongestConsecutive s;
        vector<int> nums1 = {100, 4, 200, 1, 3, 2};
        cout << s.solve(nums1) << endl; // 4 (sequence: 1,2,3,4)

        vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
        cout << s.solve(nums2) << endl; // 9 (0-8)
    }

    return 0;
}
