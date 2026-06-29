// ============================================================
// 05_dp_problems.cpp  —  LeetCode Style
// Problems: Fibonacci (memo + tab), 0/1 Knapsack,
//           Longest Common Subsequence, Coin Change
// ============================================================

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <climits>
using namespace std;

// ============================================================
// Problem 1: Fibonacci — memoization vs tabulation
// ============================================================
class Fibonacci
{
    unordered_map<int, long long> memo;

public:
    // Top-down: memoization
    long long topDown(int n)
    {
        if (n <= 1)
            return n;
        if (memo.count(n))
            return memo[n];
        return memo[n] = topDown(n - 1) + topDown(n - 2);
    }

    // Bottom-up: tabulation
    long long bottomUp(int n)
    {
        if (n <= 1)
            return n;
        vector<long long> dp(n + 1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
            dp[i] = dp[i - 1] + dp[i - 2];
        return dp[n];
    }

    // Optimized: only need last two values
    long long optimized(int n)
    {
        if (n <= 1)
            return n;
        long long a = 0, b = 1;
        for (int i = 2; i <= n; i++)
        {
            long long tmp = a + b;
            a = b;
            b = tmp;
        }
        return b;
    }
};

// ============================================================
// Problem 2: 0/1 Knapsack
// Given items with weights and values, max value with capacity W.
// Time: O(n*W)  Space: O(n*W) or O(W) optimized
// ============================================================
class Knapsack
{
public:
    int solve(int W, vector<int> &weights, vector<int> &values)
    {
        int n = weights.size();
        // dp[i][w] = max value using first i items with capacity w
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int w = 0; w <= W; w++)
            {
                dp[i][w] = dp[i - 1][w]; // skip item i
                if (weights[i - 1] <= w)
                {
                    // take item i: value[i-1] + best with remaining capacity
                    dp[i][w] = max(dp[i][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
                }
            }
        }
        return dp[n][W];
    }

    // Space-optimized: single 1D DP array (traverse right to left!)
    int solveOptimized(int W, vector<int> &weights, vector<int> &values)
    {
        int n = weights.size();
        vector<int> dp(W + 1, 0);
        for (int i = 0; i < n; i++)
        {
            for (int w = W; w >= weights[i]; w--)
            { // RIGHT to LEFT (prevent reuse)
                dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
            }
        }
        return dp[W];
    }
};

// ============================================================
// Problem 3: Longest Common Subsequence (LCS)
// Find length of longest subsequence common to both strings.
// Time: O(m*n)  Space: O(m*n)
// ============================================================
class LCS
{
public:
    int solve(string s1, string s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1]; // chars match → extend
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // skip one char
            }
        }
        return dp[m][n];
    }

    // Reconstruct the actual LCS string
    string reconstruct(string s1, string s2)
    {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }

        // Backtrack
        string result;
        int i = m, j = n;
        while (i > 0 && j > 0)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                result += s1[i - 1];
                i--;
                j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1])
                i--;
            else
                j--;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

// ============================================================
// Problem 4: Coin Change (LeetCode #322)
// Fewest coins to make up an amount. Return -1 if impossible.
// Approach: BFS (guarantees fewest) or DP tabulation
// Time: O(amount * coins)  Space: O(amount)
// ============================================================
class CoinChange
{
public:
    int solve(vector<int> &coins, int amount)
    {
        // dp[i] = min coins to make amount i
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;

        for (int a = 1; a <= amount; a++)
        {
            for (int coin : coins)
            {
                if (coin <= a && dp[a - coin] != INT_MAX)
                {
                    dp[a] = min(dp[a], 1 + dp[a - coin]);
                }
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Fibonacci
    cout << "=== Fibonacci ===" << endl;
    {
        Fibonacci f;
        for (int i : {0, 1, 5, 10, 30})
        {
            cout << "fib(" << i << ") = "
                 << f.optimized(i) << endl;
        }
    }

    // Knapsack
    cout << "\n=== 0/1 Knapsack ===" << endl;
    {
        Knapsack ks;
        vector<int> weights = {2, 3, 4, 5};
        vector<int> values = {3, 4, 5, 6};
        int capacity = 8;
        cout << ks.solve(capacity, weights, values) << endl;          // 10
        cout << ks.solveOptimized(capacity, weights, values) << endl; // 10
    }

    // LCS
    cout << "\n=== Longest Common Subsequence ===" << endl;
    {
        LCS lcs;
        cout << lcs.solve("abcde", "ace") << endl;       // 3
        cout << lcs.reconstruct("abcde", "ace") << endl; // "ace"
        cout << lcs.solve("abc", "abc") << endl;         // 3
        cout << lcs.solve("abc", "def") << endl;         // 0
    }

    // Coin Change
    cout << "\n=== Coin Change ===" << endl;
    {
        CoinChange s;
        vector<int> coins1 = {1, 5, 10, 25};
        cout << s.solve(coins1, 41) << endl; // 3 (25+10+5+1 = wait, 25+10+5+1 = 4 ... 25+16? no, 25+10+5+1=4)
        // Actually 25+10+5+1 = 4 coins. But 25+16 isn't possible with those denominations.
        // 41 = 25+10+5+1 = 4 coins

        vector<int> coins2 = {1, 2, 5};
        cout << s.solve(coins2, 11) << endl; // 3  (5+5+1)
        cout << s.solve(coins2, 3) << endl;  // 2  (2+1)

        vector<int> coins3 = {2};
        cout << s.solve(coins3, 3) << endl; // -1 (impossible)
    }

    return 0;
}
