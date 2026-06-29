// ============================================================
// 06_sorting_searching.cpp  —  LeetCode Style
// Problems: Binary Search, Search in Rotated Sorted Array,
//           Merge Sort implementation, Quick Select (kth largest)
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// Problem 1: Binary Search (LeetCode #704)
// Find target in sorted array, return index (-1 if not found).
// Time: O(log n)  Space: O(1)
// ============================================================
class BinarySearch
{
public:
    int solve(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2; // avoid overflow vs (l+r)/2
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    // Find first position where condition is true (lower_bound style)
    int lowerBound(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size();
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }
};

// ============================================================
// Problem 2: Search in Rotated Sorted Array (LeetCode #33)
// Array was sorted then rotated at some pivot.
// Approach: Modified binary search — one half is always sorted
// Time: O(log n)  Space: O(1)
// ============================================================
class SearchRotated
{
public:
    int solve(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;

            // Determine which half is properly sorted
            if (nums[left] <= nums[mid])
            {
                // Left half is sorted
                if (nums[left] <= target && target < nums[mid])
                    right = mid - 1; // target in left half
                else
                    left = mid + 1; // target in right half
            }
            else
            {
                // Right half is sorted
                if (nums[mid] < target && target <= nums[right])
                    left = mid + 1; // target in right half
                else
                    right = mid - 1; // target in left half
            }
        }
        return -1;
    }
};

// ============================================================
// Problem 3: Merge Sort implementation
// Time: O(n log n)  Space: O(n)
// ============================================================
class MergeSort
{
    void merge(vector<int> &arr, int left, int mid, int right)
    {
        vector<int> tmp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right)
        {
            if (arr[i] <= arr[j])
                tmp[k++] = arr[i++];
            else
                tmp[k++] = arr[j++];
        }
        while (i <= mid)
            tmp[k++] = arr[i++];
        while (j <= right)
            tmp[k++] = arr[j++];

        for (int x = 0; x < k; x++)
            arr[left + x] = tmp[x];
    }

    void mergeSort(vector<int> &arr, int left, int right)
    {
        if (left >= right)
            return;
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

public:
    void solve(vector<int> &arr)
    {
        mergeSort(arr, 0, arr.size() - 1);
    }
};

// ============================================================
// Problem 4: Kth Largest Element (LeetCode #215)
// Find kth largest without fully sorting.
// Approach: Quick Select — average O(n), worst O(n^2)
// ============================================================
class KthLargest
{
    int partition(vector<int> &nums, int left, int right)
    {
        int pivot = nums[right];
        int i = left;
        for (int j = left; j < right; j++)
        {
            if (nums[j] <= pivot)
                swap(nums[i++], nums[j]);
        }
        swap(nums[i], nums[right]);
        return i;
    }

    int quickSelect(vector<int> &nums, int left, int right, int k)
    {
        if (left == right)
            return nums[left];
        int pivotIdx = partition(nums, left, right);
        // kth largest is at position (n-k) in sorted order
        if (pivotIdx == k)
            return nums[pivotIdx];
        else if (pivotIdx < k)
            return quickSelect(nums, pivotIdx + 1, right, k);
        else
            return quickSelect(nums, left, pivotIdx - 1, k);
    }

public:
    int solve(vector<int> nums, int k)
    { // pass by value (we modify it)
        // kth largest is at index (n - k) in sorted array
        return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
    }
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Binary Search
    cout << "=== Binary Search ===" << endl;
    {
        BinarySearch s;
        vector<int> nums = {-1, 0, 3, 5, 9, 12};
        cout << s.solve(nums, 9) << endl;      // 4
        cout << s.solve(nums, 2) << endl;      // -1
        cout << s.lowerBound(nums, 4) << endl; // 3 (first position >= 4, which is index 3 = 5)
    }

    // Search Rotated
    cout << "\n=== Search Rotated Array ===" << endl;
    {
        SearchRotated s;
        vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
        cout << s.solve(nums, 0) << endl; // 4
        cout << s.solve(nums, 3) << endl; // -1
        cout << s.solve(nums, 4) << endl; // 0
    }

    // Merge Sort
    cout << "\n=== Merge Sort ===" << endl;
    {
        MergeSort s;
        vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
        cout << "Before: ";
        for (int x : arr)
            cout << x << " ";
        cout << endl;
        s.solve(arr);
        cout << "After:  ";
        for (int x : arr)
            cout << x << " ";
        cout << endl;
    }

    // Kth Largest
    cout << "\n=== Kth Largest Element ===" << endl;
    {
        KthLargest s;
        vector<int> nums1 = {3, 2, 1, 5, 6, 4};
        cout << s.solve(nums1, 2) << endl; // 5

        vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
        cout << s.solve(nums2, 4) << endl; // 4
    }

    return 0;
}
