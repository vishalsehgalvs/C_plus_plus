// ============================================================
// 01_arrays_problems.cpp  —  LeetCode Style
// Problems: Two Sum, Maximum Subarray, Rotate Array,
//           Product Except Self
// ============================================================

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// ============================================================
// Problem 1: Two Sum (LeetCode #1)
// Given an array and target, return indices of two numbers
// that add up to target.
// Time: O(n)  Space: O(n)
// ============================================================
class TwoSum
{
public:
    vector<int> solve(vector<int> &nums, int target)
    {
        unordered_map<int, int> seen; // value → index
        for (int i = 0; i < (int)nums.size(); i++)
        {
            int complement = target - nums[i];
            if (seen.count(complement))
            {
                return {seen[complement], i};
            }
            seen[nums[i]] = i;
        }
        return {};
    }
};

// ============================================================
// Problem 2: Maximum Subarray (LeetCode #53)
// Find contiguous subarray with largest sum.
// Approach: Kadane's Algorithm
// Time: O(n)  Space: O(1)
// ============================================================
class MaxSubarray
{
public:
    int solve(vector<int> &nums)
    {
        int maxSum = nums[0];
        int currentSum = nums[0];

        for (int i = 1; i < (int)nums.size(); i++)
        {
            // Either extend current subarray or start fresh
            currentSum = max(nums[i], currentSum + nums[i]);
            maxSum = max(maxSum, currentSum);
        }
        return maxSum;
    }
};

// ============================================================
// Problem 3: Rotate Array (LeetCode #189)
// Rotate array to the right by k steps.
// Approach: Three reverse trick
// Time: O(n)  Space: O(1)
// ============================================================
class RotateArray
{
public:
    void solve(vector<int> &nums, int k)
    {
        int n = nums.size();
        k %= n;                                  // handle k > n
        reverse(nums.begin(), nums.end());       // reverse all
        reverse(nums.begin(), nums.begin() + k); // reverse first k
        reverse(nums.begin() + k, nums.end());   // reverse rest
    }
};

// ============================================================
// Problem 4: Product of Array Except Self (LeetCode #238)
// Return array where each element is product of all others.
// Constraint: No division allowed.
// Approach: Prefix and suffix products
// Time: O(n)  Space: O(1) extra (output array doesn't count)
// ============================================================
class ProductExceptSelf
{
public:
    vector<int> solve(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> result(n, 1);

        // Pass 1: result[i] = product of all elements to the LEFT of i
        int prefixProduct = 1;
        for (int i = 0; i < n; i++)
        {
            result[i] = prefixProduct;
            prefixProduct *= nums[i];
        }

        // Pass 2: multiply in product of all elements to the RIGHT of i
        int suffixProduct = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            result[i] *= suffixProduct;
            suffixProduct *= nums[i];
        }

        return result;
    }
};

// ================================================================
// MAIN — test all problems
// ================================================================
int main()
{
    // Two Sum
    cout << "=== Two Sum ===" << endl;
    {
        TwoSum s;
        vector<int> nums = {2, 7, 11, 15};
        auto res = s.solve(nums, 9);
        cout << "[" << res[0] << ", " << res[1] << "]" << endl; // [0, 1]

        vector<int> nums2 = {3, 2, 4};
        auto res2 = s.solve(nums2, 6);
        cout << "[" << res2[0] << ", " << res2[1] << "]" << endl; // [1, 2]
    }

    // Max Subarray
    cout << "\n=== Maximum Subarray ===" << endl;
    {
        MaxSubarray s;
        vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        cout << s.solve(nums) << endl; // 6  (subarray: [4,-1,2,1])

        vector<int> nums2 = {1};
        cout << s.solve(nums2) << endl; // 1

        vector<int> nums3 = {-1, -2, -3};
        cout << s.solve(nums3) << endl; // -1
    }

    // Rotate Array
    cout << "\n=== Rotate Array ===" << endl;
    {
        RotateArray s;
        vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
        s.solve(nums, 3);
        for (int x : nums)
            cout << x << " ";
        cout << endl; // 5 6 7 1 2 3 4
    }

    // Product Except Self
    cout << "\n=== Product Except Self ===" << endl;
    {
        ProductExceptSelf s;
        vector<int> nums = {1, 2, 3, 4};
        auto res = s.solve(nums);
        for (int x : res)
            cout << x << " ";
        cout << endl; // 24 12 8 6

        vector<int> nums2 = {-1, 1, 0, -3, 3};
        auto res2 = s.solve(nums2);
        for (int x : res2)
            cout << x << " ";
        cout << endl; // 0 0 9 0 0
    }

    return 0;
}
