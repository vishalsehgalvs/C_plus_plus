// ============================================================
// 03_linked_list.cpp  —  LeetCode Style
// Problems: Reverse Linked List, Detect Cycle,
//           Merge Two Sorted Lists, Find Middle Node
// ============================================================

#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// Node definition shared by all problems
// ============================================================
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Helper: build list from vector
ListNode *makeList(vector<int> vals)
{
    if (vals.empty())
        return nullptr;
    ListNode *head = new ListNode(vals[0]);
    ListNode *cur = head;
    for (int i = 1; i < (int)vals.size(); i++)
    {
        cur->next = new ListNode(vals[i]);
        cur = cur->next;
    }
    return head;
}

// Helper: print list
void printList(ListNode *head)
{
    while (head)
    {
        cout << head->val << (head->next ? " -> " : "");
        head = head->next;
    }
    cout << endl;
}

// Helper: free list
void freeList(ListNode *head)
{
    while (head)
    {
        auto tmp = head->next;
        delete head;
        head = tmp;
    }
}

// ============================================================
// Problem 1: Reverse Linked List (LeetCode #206)
// Reverse a singly linked list.
// Approach: Iterative (3-pointer flip)
// Time: O(n)  Space: O(1)
// ============================================================
class ReverseList
{
public:
    ListNode *solve(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;
        while (curr)
        {
            ListNode *next = curr->next; // save next
            curr->next = prev;           // flip
            prev = curr;                 // advance prev
            curr = next;                 // advance curr
        }
        return prev; // new head
    }
};

// ============================================================
// Problem 2: Linked List Cycle (LeetCode #141)
// Detect if linked list has a cycle.
// Approach: Floyd's Tortoise & Hare (fast/slow pointers)
// Time: O(n)  Space: O(1)
// ============================================================
class HasCycle
{
public:
    bool solve(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true; // they met → cycle!
        }
        return false;
    }
};

// ============================================================
// Problem 3: Merge Two Sorted Lists (LeetCode #21)
// Merge two sorted linked lists into one sorted list.
// Approach: Iterative with dummy head
// Time: O(m+n)  Space: O(1)
// ============================================================
class MergeSortedLists
{
public:
    ListNode *solve(ListNode *l1, ListNode *l2)
    {
        ListNode dummy(0); // sentinel node avoids null checks
        ListNode *tail = &dummy;

        while (l1 && l2)
        {
            if (l1->val <= l2->val)
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2; // attach remaining
        return dummy.next;
    }
};

// ============================================================
// Problem 4: Middle of Linked List (LeetCode #876)
// Find the middle node (if even length, return second middle).
// Approach: Fast/slow pointers
// Time: O(n)  Space: O(1)
// ============================================================
class FindMiddle
{
public:
    ListNode *solve(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow; // slow is at the middle when fast reaches end
    }
};

// ================================================================
// MAIN
// ================================================================
int main()
{
    // Reverse Linked List
    cout << "=== Reverse Linked List ===" << endl;
    {
        ReverseList s;
        ListNode *list = makeList({1, 2, 3, 4, 5});
        printList(list);
        list = s.solve(list);
        printList(list); // 5 -> 4 -> 3 -> 2 -> 1
        freeList(list);
    }

    // Cycle Detection
    cout << "\n=== Detect Cycle ===" << endl;
    {
        HasCycle s;
        ListNode *noCycle = makeList({1, 2, 3, 4});
        cout << boolalpha << s.solve(noCycle) << endl; // false
        freeList(noCycle);

        // Build cycle manually: 1 -> 2 -> 3 -> 4 -> (back to 2)
        ListNode *a = new ListNode(1);
        ListNode *b = new ListNode(2);
        ListNode *c = new ListNode(3);
        ListNode *d = new ListNode(4);
        a->next = b;
        b->next = c;
        c->next = d;
        d->next = b;                // cycle!
        cout << s.solve(a) << endl; // true
        // Don't free (cycle would infinite loop); just leak in demo
    }

    // Merge Sorted Lists
    cout << "\n=== Merge Two Sorted Lists ===" << endl;
    {
        MergeSortedLists s;
        ListNode *l1 = makeList({1, 2, 4});
        ListNode *l2 = makeList({1, 3, 4});
        ListNode *merged = s.solve(l1, l2);
        printList(merged); // 1 -> 1 -> 2 -> 3 -> 4 -> 4
        freeList(merged);
    }

    // Find Middle
    cout << "\n=== Find Middle Node ===" << endl;
    {
        FindMiddle s;
        ListNode *odd = makeList({1, 2, 3, 4, 5});
        ListNode *even = makeList({1, 2, 3, 4});
        cout << s.solve(odd)->val << endl;  // 3 (middle of 5)
        cout << s.solve(even)->val << endl; // 3 (second middle of 4)
        freeList(odd);
        freeList(even);
    }

    return 0;
}
