#include <bits/stdc++.h>
using namespace std;

/*
Problem: Solve Queries on Circular Array (Same Value Distance)
Platform: LeetCode

Approach:
- For each value, store all indices where it appears
- For each query:
    - Find nearest occurrence of same value
    - Consider circular distance

Steps:
1. Build map: value → sorted list of indices
2. For each query:
    - Find current index in list using binary search
    - Check:
        next occurrence
        previous occurrence
    - Compute circular distance
    - Take minimum

Circular Distance:
For two indices i and j:

distance = min(|i - j|, n - |i - j|)

Time Complexity:
O(n log n + q log n)

Space Complexity:
O(n)

Concepts Used:
- Hashing (map)
- Binary search (lower_bound)
- Circular array logic
*/

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {

        map<int, vector<int>> mp;

        // Step 1: Store indices of each value
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]].push_back(i);
        }

        vector<int> ans;

        // Step 2: Process queries
        for (int i = 0; i < queries.size(); i++) {

            int num = nums[queries[i]];
            vector<int>& temp = mp[num];

            // Only one occurrence
            if (temp.size() <= 1) {
                ans.push_back(-1);
            }
            else {

                int index1 =
                    lower_bound(temp.begin(), temp.end(), queries[i]) - temp.begin();

                int index = temp[index1];
                int n = temp.size();

                // Next occurrence (circular)
                int nextIndex = temp[(index1 + 1) % n];

                int n1 = abs(nextIndex - index);
                int n2 = nums.size() - abs(nextIndex - index);

                int ans1 = min(n1, n2);

                // Previous occurrence (circular)
                int prevIndex = temp[(index1 - 1 + n) % n];

                int n3 = abs(index - prevIndex);
                int n4 = nums.size() - n3;

                int ans2 = min(n3, n4);

                ans.push_back(min(ans1, ans2));
            }
        }

        return ans;
    }
};