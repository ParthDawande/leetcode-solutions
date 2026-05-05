/*
===========================================================
Problem: Rotate Linked List to the Right by k places
===========================================================

Goal:
-----
Rotate the linked list to the right by k positions.

Example:
--------
Input:  1 -> 2 -> 3 -> 4 -> 5, k = 2
Output: 4 -> 5 -> 1 -> 2 -> 3

-----------------------------------------------------------
Key Observations:
-----------------------------------------------------------

1. Rotating right by k is equivalent to:
   moving last k nodes to the front.

2. If k >= length:
   rotation repeats → so take:
        k = k % length

3. New Head will be:
        (len - k)-th node

-----------------------------------------------------------
Approach:
-----------------------------------------------------------

Step 1: Compute length of linked list

Step 2: Normalize k
        k = k % len

Step 3: Find new tail:
        position = len - k - 1

Step 4:
        newHead = newTail->next

Step 5:
        Break link:
        newTail->next = NULL

Step 6:
        Attach old tail to old head

-----------------------------------------------------------
Time Complexity:
-----------------------------------------------------------
O(n)

-----------------------------------------------------------
Space Complexity:
-----------------------------------------------------------
O(1)

-----------------------------------------------------------
*/

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {

        // Edge cases
        if(head == nullptr || head->next == nullptr) {
            return head;
        }

        // Step 1: Find length
        int len = 0;
        ListNode* temp = head;
        while(temp != nullptr) {
            len++;
            temp = temp->next;
        }

        // Step 2: Normalize k
        k = k % len;
        if(k == 0) {
            return head;
        }

        // Step 3: Find new tail (len-k-1)
        int steps = len - k - 1;
        ListNode* newTail = head;

        while(steps--) {
            newTail = newTail->next;
        }

        // Step 4: New head
        ListNode* newHead = newTail->next;

        // Step 5: Break connection
        newTail->next = nullptr;

        // Step 6: Attach old tail to old head
        ListNode* tail = newHead;
        while(tail->next != nullptr) {
            tail = tail->next;
        }
        tail->next = head;

        return newHead;
    }
};