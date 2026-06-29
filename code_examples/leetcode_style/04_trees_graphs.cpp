// ============================================================
// 04_trees_graphs.cpp  —  LeetCode Style
// Problems: Level Order Traversal, Max Depth,
//           Validate BST, BFS/DFS on Graph
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <climits>
using namespace std;

// ============================================================
// Binary Tree Node
// ============================================================
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode *makeNode(int v, TreeNode *l = nullptr, TreeNode *r = nullptr)
{
    TreeNode *n = new TreeNode(v);
    n->left = l;
    n->right = r;
    return n;
}

// ============================================================
// Problem 1: Binary Tree Level Order Traversal (LeetCode #102)
// Return node values level by level.
// Approach: BFS with a queue
// Time: O(n)  Space: O(n)
// ============================================================
class LevelOrder
{
public:
    vector<vector<int>> solve(TreeNode *root)
    {
        vector<vector<int>> result;
        if (!root)
            return result;

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            int levelSize = q.size(); // nodes at current level
            vector<int> level;

            for (int i = 0; i < levelSize; i++)
            {
                TreeNode *node = q.front();
                q.pop();
                level.push_back(node->val);
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            result.push_back(level);
        }
        return result;
    }
};

// ============================================================
// Problem 2: Maximum Depth of Binary Tree (LeetCode #104)
// Approach: DFS (recursive)
// Time: O(n)  Space: O(h) where h = height
// ============================================================
class MaxDepth
{
public:
    int solve(TreeNode *root)
    {
        if (!root)
            return 0;
        int leftDepth = solve(root->left);
        int rightDepth = solve(root->right);
        return 1 + max(leftDepth, rightDepth);
    }
};

// ============================================================
// Problem 3: Validate Binary Search Tree (LeetCode #98)
// BST property: left < root < right (for entire subtrees!)
// Approach: Pass valid range [min, max] down recursively
// Time: O(n)  Space: O(h)
// ============================================================
class ValidateBST
{
    bool dfs(TreeNode *node, long minVal, long maxVal)
    {
        if (!node)
            return true;
        if (node->val <= minVal || node->val >= maxVal)
            return false;
        return dfs(node->left, minVal, node->val) &&
               dfs(node->right, node->val, maxVal);
    }

public:
    bool solve(TreeNode *root)
    {
        return dfs(root, LONG_MIN, LONG_MAX);
    }
};

// ============================================================
// Problem 4: Graph BFS — find shortest path
// Approach: BFS (guarantees shortest path in unweighted graph)
// Time: O(V+E)  Space: O(V)
// ============================================================
class GraphBFS
{
public:
    int shortestPath(int n, vector<vector<int>> &edges, int start, int end)
    {
        // Build adjacency list
        unordered_map<int, vector<int>> adj;
        for (auto &e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        unordered_set<int> visited;
        queue<pair<int, int>> q; // (node, distance)
        q.push({start, 0});
        visited.insert(start);

        while (!q.empty())
        {
            auto [node, dist] = q.front();
            q.pop();
            if (node == end)
                return dist;
            for (int neighbor : adj[node])
            {
                if (!visited.count(neighbor))
                {
                    visited.insert(neighbor);
                    q.push({neighbor, dist + 1});
                }
            }
        }
        return -1; // not reachable
    }
};

// ============================================================
// Problem 5: Graph DFS — detect cycle in undirected graph
// Time: O(V+E)  Space: O(V)
// ============================================================
class GraphDFS
{
    bool dfs(int node, int parent, unordered_map<int, vector<int>> &adj,
             unordered_set<int> &visited)
    {
        visited.insert(node);
        for (int neighbor : adj[node])
        {
            if (!visited.count(neighbor))
            {
                if (dfs(neighbor, node, adj, visited))
                    return true;
            }
            else if (neighbor != parent)
            {
                return true; // back edge = cycle
            }
        }
        return false;
    }

public:
    bool hasCycle(int n, vector<vector<int>> &edges)
    {
        unordered_map<int, vector<int>> adj;
        for (auto &e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        unordered_set<int> visited;
        for (int i = 0; i < n; i++)
        {
            if (!visited.count(i))
            {
                if (dfs(i, -1, adj, visited))
                    return true;
            }
        }
        return false;
    }
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Level Order
    cout << "=== Level Order Traversal ===" << endl;
    {
        //     3
        //    / \
        //   9  20
        //      / \
        //     15   7
        TreeNode *root = makeNode(3,
                                  makeNode(9),
                                  makeNode(20, makeNode(15), makeNode(7)));
        LevelOrder s;
        auto levels = s.solve(root);
        for (auto &level : levels)
        {
            for (int v : level)
                cout << v << " ";
            cout << endl;
        }
        // Output: 3 / 9 20 / 15 7
    }

    // Max Depth
    cout << "\n=== Max Depth ===" << endl;
    {
        TreeNode *root = makeNode(3,
                                  makeNode(9),
                                  makeNode(20, makeNode(15), makeNode(7)));
        MaxDepth s;
        cout << s.solve(root) << endl; // 3
    }

    // Validate BST
    cout << "\n=== Validate BST ===" << endl;
    {
        ValidateBST s;
        //   2
        //  / \
        // 1   3   — valid BST
        TreeNode *valid = makeNode(2, makeNode(1), makeNode(3));
        cout << boolalpha << s.solve(valid) << endl; // true

        //   5
        //  / \
        // 1   4     — invalid (4 < 5 but 4's right child 6 > 5)
        //     / \
        //    3   6
        TreeNode *invalid = makeNode(5, makeNode(1), makeNode(4, makeNode(3), makeNode(6)));
        cout << s.solve(invalid) << endl; // false
    }

    // Graph BFS
    cout << "\n=== Graph BFS (Shortest Path) ===" << endl;
    {
        GraphBFS s;
        // 0 -- 1 -- 3
        //  \       /
        //   2 ----
        vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
        cout << s.shortestPath(4, edges, 0, 3) << endl; // 2 (0->1->3 or 0->2->3)
    }

    // Graph DFS — cycle detection
    cout << "\n=== Graph DFS (Cycle Detection) ===" << endl;
    {
        GraphDFS s;
        vector<vector<int>> noCycle = {{0, 1}, {1, 2}, {2, 3}};
        vector<vector<int>> hasCycle = {{0, 1}, {1, 2}, {2, 0}};
        cout << boolalpha;
        cout << s.hasCycle(4, noCycle) << endl;  // false
        cout << s.hasCycle(3, hasCycle) << endl; // true
    }

    return 0;
}
