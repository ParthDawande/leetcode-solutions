#include <bits/stdc++.h>
using namespace std;

/*
Problem: Longest Balanced Subarray (Custom Definition)
Platform: LeetCode

Approach:
- Convert array into +1 / -1:
    even → +1
    odd  → -1

- We want longest subarray with sum = 0
    → balanced subarray

- But constraint:
    Only consider ranges where each value is counted once
    (use last occurrence tracking)

- Use Segment Tree with Lazy Propagation:
    - Range update
    - Maintain min and max prefix values

Steps:
1. For each index i:
    - Add +1 or -1 to range [prev+1, i]
    - prev = last occurrence of nums[i]

2. Query:
    - Find leftmost index where prefix sum = 0

3. Update answer

Data Structures:
- Segment Tree with:
    segMin → minimum prefix sum
    segMax → maximum prefix sum
    lazy   → lazy propagation

Time Complexity:
O(n log n)

Space Complexity:
O(n)

Concepts Used:
- Lazy Segment Tree
- Prefix sum transformation
- Hashing (last occurrence)
*/

class Solution {
public:
    vector<int> lazy;
    vector<int> segMax;
    vector<int> segMin;

    // Push lazy updates
    void push(int index, int l, int r) {
        if (lazy[index] != 0) {
            segMax[index] += lazy[index];
            segMin[index] += lazy[index];

            if (l != r) {
                lazy[2 * index + 1] += lazy[index];
                lazy[2 * index + 2] += lazy[index];
            }

            lazy[index] = 0;
        }
    }

    // Range update
    void update(int l, int r, int s, int e, int index, int val) {
        push(index, s, e);

        if (l > e || r < s) {
            return;
        }

        if (l <= s && e <= r) {
            lazy[index] += val;
            push(index, s, e);
            return;
        }

        int m = s + (e - s) / 2;

        update(l, r, s, m, 2 * index + 1, val);
        update(l, r, m + 1, e, 2 * index + 2, val);

        segMax[index] = max(segMax[2 * index + 1], segMax[2 * index + 2]);
        segMin[index] = min(segMin[2 * index + 1], segMin[2 * index + 2]);
    }

    // Find leftmost index where prefix sum == 0
    int leftMostZero(int index, int s, int e) {
        push(index, s, e);

        // No zero possible
        if (segMin[index] > 0 || segMax[index] < 0) {
            return -1;
        }

        if (s == e) {
            return e;
        }

        int m = s + (e - s) / 2;

        int left = leftMostZero(2 * index + 1, s, m);
        if (left == -1) {
            return leftMostZero(2 * index + 2, m + 1, e);
        }
        return left;
    }

    int longestBalanced(vector<int>& nums) {

        int n = nums.size();

        lazy.resize(4 * n, 0);
        segMax.resize(4 * n, 0);
        segMin.resize(4 * n, 0);

        unordered_map<int, int> mp;

        int ans = 0;

        for (int i = 0; i < n; i++) {

            int val = 0;

            // Transform even/odd
            if (nums[i] % 2 == 0) {
                val = 1;
            } else {
                val = -1;
            }

            int prev = -1;

            // Last occurrence
            if (mp.find(nums[i]) != mp.end()) {
                prev = mp[nums[i]];
            }

            // Update range
            update(prev + 1, i, 0, n - 1, 0, val);

            // Query leftmost zero prefix
            int l = leftMostZero(0, 0, n - 1);

            if (l != -1) {
                ans = max(ans, i - l + 1);
            }

            mp[nums[i]] = i;
        }

        return ans;
    }
};