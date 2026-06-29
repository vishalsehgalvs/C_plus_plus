// ============================================================
// 02_strings_problems.cpp  —  LeetCode Style
// Problems: Valid Palindrome, Valid Anagram,
//           Longest Substring Without Repeating Characters,
//           Longest Common Prefix
// ============================================================

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// ============================================================
// Problem 1: Valid Palindrome (LeetCode #125)
// A phrase is palindrome if reads same forward/backward
// after lowercasing and removing non-alphanumeric chars.
// Time: O(n)  Space: O(1)
// ============================================================
class ValidPalindrome
{
public:
    bool solve(string s)
    {
        int left = 0, right = s.size() - 1;
        while (left < right)
        {
            while (left < right && !isalnum(s[left]))
                left++;
            while (left < right && !isalnum(s[right]))
                right--;
            if (tolower(s[left]) != tolower(s[right]))
                return false;
            left++;
            right--;
        }
        return true;
    }
};

// ============================================================
// Problem 2: Valid Anagram (LeetCode #242)
// Check if two strings are anagrams of each other.
// Time: O(n)  Space: O(1) — fixed 26-char alphabet
// ============================================================
class ValidAnagram
{
public:
    bool solve(string s, string t)
    {
        if (s.size() != t.size())
            return false;
        int count[26] = {};
        for (char c : s)
            count[c - 'a']++;
        for (char c : t)
            count[c - 'a']--;
        for (int x : count)
            if (x != 0)
                return false;
        return true;
    }
};

// ============================================================
// Problem 3: Longest Substring Without Repeating (LeetCode #3)
// Approach: Sliding window with hash map
// Time: O(n)  Space: O(min(m,n)) where m = charset size
// ============================================================
class LongestSubstringNoRepeat
{
public:
    int solve(string s)
    {
        unordered_map<char, int> lastSeen; // char → last index
        int maxLen = 0;
        int left = 0;

        for (int right = 0; right < (int)s.size(); right++)
        {
            char c = s[right];
            if (lastSeen.count(c) && lastSeen[c] >= left)
            {
                left = lastSeen[c] + 1; // shrink window
            }
            lastSeen[c] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};

// ============================================================
// Problem 4: Longest Common Prefix (LeetCode #14)
// Find longest common prefix among array of strings.
// Approach: Vertical scanning
// Time: O(S) where S = sum of all char lengths  Space: O(1)
// ============================================================
class LongestCommonPrefix
{
public:
    string solve(vector<string> &strs)
    {
        if (strs.empty())
            return "";
        for (int col = 0; col < (int)strs[0].size(); col++)
        {
            char c = strs[0][col];
            for (int row = 1; row < (int)strs.size(); row++)
            {
                // If column out of bounds OR char doesn't match
                if (col >= (int)strs[row].size() || strs[row][col] != c)
                {
                    return strs[0].substr(0, col);
                }
            }
        }
        return strs[0];
    }
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Valid Palindrome
    cout << "=== Valid Palindrome ===" << endl;
    {
        ValidPalindrome s;
        cout << boolalpha;
        cout << s.solve("A man, a plan, a canal: Panama") << endl; // true
        cout << s.solve("race a car") << endl;                     // false
        cout << s.solve(" ") << endl;                              // true
    }

    // Valid Anagram
    cout << "\n=== Valid Anagram ===" << endl;
    {
        ValidAnagram s;
        cout << boolalpha;
        cout << s.solve("anagram", "nagaram") << endl; // true
        cout << s.solve("rat", "car") << endl;         // false
        cout << s.solve("listen", "silent") << endl;   // true
    }

    // Longest Substring Without Repeating
    cout << "\n=== Longest Substring No Repeat ===" << endl;
    {
        LongestSubstringNoRepeat s;
        cout << s.solve("abcabcbb") << endl; // 3 ("abc")
        cout << s.solve("bbbbb") << endl;    // 1 ("b")
        cout << s.solve("pwwkew") << endl;   // 3 ("wke")
    }

    // Longest Common Prefix
    cout << "\n=== Longest Common Prefix ===" << endl;
    {
        LongestCommonPrefix s;
        vector<string> v1 = {"flower", "flow", "flight"};
        cout << s.solve(v1) << endl; // "fl"

        vector<string> v2 = {"dog", "racecar", "car"};
        cout << s.solve(v2) << endl; // "" (no common prefix)

        vector<string> v3 = {"abc", "abcd", "abcdef"};
        cout << s.solve(v3) << endl; // "abc"
    }

    return 0;
}
