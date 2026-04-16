#include <bits/stdc++.h>
using namespace std;

/*
Problem: Solve Queries on Circular Array (Optimized)
Platform: LeetCode

Approach:
- For each value, store all indices where it appears
- Precompute the minimum circular distance for every index

Key Idea:
- For each occurrence of a value:
    Only its immediate next and previous occurrences matter
    (because indices are sorted)

Steps:
1. Build map: value → list of indices
2. For each list:
    - For every index:
        compute distance with:
            next occurrence
            previous occurrence
        store best distance
3. Answer queries in O(1)

Circular Distance:
distance(i, j) = min(|i - j|, n - |i - j|)

Time Complexity:
O(n + q)

Space Complexity:
O(n)

Concepts Used:
- Hashing
- Circular array
- Greedy nearest neighbor
*/

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {

        unordered_map<int, vector<int>> mp;

        // Step 1: Store indices
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]].push_back(i);
        }

        int n = nums.size();

        // Step 2: Precompute answers
        vector<int> best(n, -1);

        for (auto i : mp) {

            vector<int>& temp = i.second;
            int m = temp.size();

            if (m >= 2) {

                for (int j = 0; j < m; j++) {

                    int jnext = (j + 1) % m;
                    int jprev = (j - 1 + m) % m;

                    // Distance to next
                    int ans1 = abs(temp[j] - temp[jnext]);
                    int ans2 = n - ans1;

                    // Distance to previous
                    int ans3 = abs(temp[j] - temp[jprev]);
                    int ans4 = n - ans3;

                    best[temp[j]] = min({ans1, ans2, ans3, ans4});
                }
            }
        }

        // Step 3: Answer queries
        vector<int> ans;
        for (int i = 0; i < queries.size(); i++) {
            ans.push_back(best[queries[i]]);
        }

        return ans;
    }
};