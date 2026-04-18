#include <bits/stdc++.h>
using namespace std;

/*
Problem: Count Good Subsequences with Updates
--------------------------------------------------

Goal:
After each query (point update), determine whether:
- The array can have GCD = 1
- Either directly OR by removing exactly one element

--------------------------------------------------

Key Transformation:
Instead of working with nums directly:
    value = nums[i] / p  (if divisible by p)
    else value = 0

Why?
- We only care about contribution to GCD after dividing by p
- Non-divisible elements become 0 → ignored in GCD

--------------------------------------------------

Segment Tree:
- Stores GCD over transformed values
- Supports:
    1. Build
    2. Point update
    3. Query-like traversal (canLeaveOne)

--------------------------------------------------

Core Logic:

Case 1:
If GCD of whole array == 1:
    → already valid
    BUT must ensure at least one element is NOT divisible by p

Case 2:
If all elements divisible by p:
    → Try removing exactly one element
    → Check if remaining GCD == 1

--------------------------------------------------

Important Function: canLeaveOne()

Idea:
Try removing one element such that:
    GCD of remaining elements == 1

Technique:
- While traversing segment tree:
    pass "external gcd" (ext)
- At each node:
    Try:
        remove left subtree → keep right
        remove right subtree → keep left

--------------------------------------------------

Time Complexity:
Build: O(n)
Each query: O(log n)

Total: O((n + q) log n)

Space Complexity:
O(4n)

Concepts Used:
- Segment Tree
- GCD
- Divide & Conquer
- Query optimization
*/

class Solution {
public:
    vector<int> seg;

    // -------------------------------
    // BUILD SEGMENT TREE
    // -------------------------------
    void build(int index, int l, int r, vector<int>& nums, int p) {
        if (l == r) {
            seg[index] = ((nums[l] % p == 0) ? nums[l] / p : 0);
            return;
        }

        int m = l + (r - l) / 2;

        build(2 * index + 1, l, m, nums, p);
        build(2 * index + 2, m + 1, r, nums, p);

        seg[index] = __gcd(seg[2 * index + 1], seg[2 * index + 2]);
    }

    // -------------------------------
    // POINT UPDATE
    // -------------------------------
    void update(int index, int l, int r, int idx, int val, int p) {
        if (l == r) {
            seg[index] = ((val % p == 0) ? val / p : 0);
            return;
        }

        int m = l + (r - l) / 2;

        if (idx <= m) {
            update(2 * index + 1, l, m, idx, val, p);
        } else {
            update(2 * index + 2, m + 1, r, idx, val, p);
        }

        seg[index] = __gcd(seg[2 * index + 1], seg[2 * index + 2]);
    }

    // -------------------------------
    // CHECK: CAN REMOVE ONE ELEMENT?
    // -------------------------------
    bool canLeaveOne(int index, int l, int r, int ext) {

        // Leaf node → removing this element
        if (l == r) {
            return ext == 1;
        }

        /*
        Important logic:

        left  = gcd(ext, right subtree)
        right = gcd(ext, left subtree)

        Why?
        - If removing LEFT subtree → keep RIGHT
        - If removing RIGHT subtree → keep LEFT
        */

        int left = __gcd(seg[2 * index + 2], ext);
        int right = __gcd(seg[2 * index + 1], ext);

        if (left == 1 || right == 1) {
            return true;
        }

        int m = l + (r - l) / 2;

        return canLeaveOne(2 * index + 1, l, m, left) ||
               canLeaveOne(2 * index + 2, m + 1, r, right);
    }

    // -------------------------------
    // MAIN FUNCTION
    // -------------------------------
    int countGoodSubseq(vector<int>& nums, int p,
                        vector<vector<int>>& queries) {

        int n = nums.size();
        seg.resize(4 * n, 0);

        // Count elements divisible by p
        int active = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] % p == 0) {
                active++;
            }
        }

        build(0, 0, n - 1, nums, p);

        int ans = 0;

        for (int i = 0; i < queries.size(); i++) {

            int index = queries[i][0];
            int newval = queries[i][1];

            // Update active count
            if (nums[index] % p == 0) active--;
            if (newval % p == 0) active++;

            nums[index] = newval;

            update(0, 0, n - 1, index, newval, p);

            // Case 1: GCD already 1
            if (seg[0] == 1) {

                if (active < n) {
                    // At least one non-divisible element exists
                    ans++;
                } else {
                    // All divisible → must remove one
                    if (canLeaveOne(0, 0, n - 1, 0)) {
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};