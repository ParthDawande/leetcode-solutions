#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem: Sum of Distances Between Equal Elements
===========================================================

Given:
- Array nums

For each index i:
    Find sum of distances between i and all other indices j
    such that nums[i] == nums[j]

Return:
    ans[i] = Σ |i - j| for all j where nums[j] == nums[i]

-----------------------------------------------------------
Brute Force:
-----------------------------------------------------------

For each i:
    Check all j → O(n^2)

Too slow ❌

-----------------------------------------------------------
Optimized Idea:
-----------------------------------------------------------

Group indices by value using hashmap

For each value:
    Process its indices separately

-----------------------------------------------------------
Key Observation:
-----------------------------------------------------------

Let indices = [i1, i2, i3, ..., ik]

For a given index ij:
    Distance = sum of distances to:
        → left elements
        → right elements

-----------------------------------------------------------
Split into 2 parts:
-----------------------------------------------------------

1. LEFT contribution
2. RIGHT contribution

-----------------------------------------------------------
RIGHT PASS (Reverse Loop)
-----------------------------------------------------------

Traverse from right → left

Maintain:
    curr1 = sum of indices to the right
    f = number of elements to the right

Formula:
    contribution = curr1 - f * index

-----------------------------------------------------------
LEFT PASS (Forward Loop)
-----------------------------------------------------------

Traverse from left → right

Maintain:
    curr2 = sum of indices to the left
    f = number of elements to the left

Formula:
    contribution = f * index - curr2

-----------------------------------------------------------
Total:
-----------------------------------------------------------

ans[index] = left contribution + right contribution

-----------------------------------------------------------
Why this works:
-----------------------------------------------------------

Efficiently computes:
    Σ |i - j|

Using prefix sums instead of brute force

-----------------------------------------------------------
Time Complexity:
-----------------------------------------------------------

Grouping: O(n)
Processing each group: O(n)

Total: O(n)

-----------------------------------------------------------
Space Complexity:
-----------------------------------------------------------

O(n)

-----------------------------------------------------------
*/


class Solution {
public:
    vector<long long> distance(vector<int>& nums) {

        unordered_map<int, vector<int>> mp;

        // Group indices by value
        for(int i = 0; i < nums.size(); i++){
            mp[nums[i]].push_back(i);
        }

        int n = nums.size();
        vector<long long> ans(n, 0);

        // Process each group
        for(auto i : mp){

            vector<int>& temp = i.second;

            // -----------------------------
            // RIGHT contribution
            // -----------------------------
            long long curr1 = 0;

            for(int j = temp.size() - 1; j >= 0; j--){
                int f = temp.size() - j - 1;
                int index = temp[j];

                ans[index] += max(0LL, curr1 - 1LL * f * index);

                curr1 += index;
            }

            // -----------------------------
            // LEFT contribution
            // -----------------------------
            long long curr2 = 0;

            for(int j = 0; j < temp.size(); j++){
                int f = j;
                int index = temp[j];

                ans[index] += max(0LL, 1LL * f * index - curr2);

                curr2 += index;
            }
        }

        return ans;
    }
};


/*
===========================================================
Example:
-----------------------------------------------------------

nums = [1,3,1,1,2]

Indices for value 1:
[0,2,3]

For index 2:
|2-0| + |2-3| = 2 + 1 = 3

Computed efficiently using prefix sums

-----------------------------------------------------------
Key Insight:
-----------------------------------------------------------

Instead of computing:
    |i - j| for all pairs

We split into:
    Left sum + Right sum

Using prefix sums:
    → O(n) solution

===========================================================
*/