/*
===========================================================
Problem: Max Fixed Points
===========================================================

Goal:
-----
Maximize number of indices i such that:
    nums[i] == i
after reordering.

-----------------------------------------------------------
Key Insight:
-----------------------------------------------------------
For a value nums[i] to become a fixed point at some index j:

    nums[i] <= j

So only elements satisfying:
    nums[i] <= i
are even candidates.

-----------------------------------------------------------
Transformation:
-----------------------------------------------------------
For each valid element:
    slack = i - nums[i]

We store:
    {slack, value}

Why?
- slack → flexibility (how far it can shift)
- value → actual number we want to place

-----------------------------------------------------------
Greedy Strategy:
-----------------------------------------------------------
1. Sort by slack (ascending)
   → elements with less flexibility handled first

2. Now choose maximum valid elements such that:
   their values form increasing order

Why increasing?
- ensures we can assign positions without conflicts

-----------------------------------------------------------
Reduction:
-----------------------------------------------------------
This becomes a classic:
    Longest Increasing Subsequence (LIS)

-----------------------------------------------------------
Algorithm:
-----------------------------------------------------------
- Filter valid elements
- Sort by slack
- Apply LIS on values using binary search

-----------------------------------------------------------
Time Complexity:
-----------------------------------------------------------
O(n log n)

-----------------------------------------------------------
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxFixedPoints(vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> arr;

        // Step 1: Filter valid candidates
        for(int i = 0; i < n; i++) {
            if(nums[i] <= i) {
                // store {flexibility, value}
                arr.push_back({i - nums[i], nums[i]});
            }
        }

        // Step 2: Sort by flexibility (greedy)
        sort(arr.begin(), arr.end());

        vector<int> lis;

        // Step 3: Apply LIS on values
        for(int i = 0; i < arr.size(); i++) {
            int val = arr[i][1];

            // Find position using binary search
            int index = lower_bound(lis.begin(), lis.end(), val) - lis.begin();

            if(index == lis.size()) {
                lis.push_back(val);
            } else {
                lis[index] = val;
            }
        }

        // LIS length = max fixed points
        return lis.size();
    }
};