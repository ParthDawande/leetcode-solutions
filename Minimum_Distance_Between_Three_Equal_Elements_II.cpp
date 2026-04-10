#include <bits/stdc++.h>
using namespace std;

/*
Problem: Minimum Distance Between Equal Elements (Triplet Version)
Platform: LeetCode

Approach:
- Group indices of each value using hashmap
- For each value:
    - Consider consecutive triplets of indices
    - Compute sum of pairwise distances

Observation:
For indices i < j < k:
distance = |j - i| + |k - j| + |k - i|

- Minimize this value over all triplets

Steps:
1. Store indices for each value
2. For each list:
    - Slide window of size 3
    - Compute distance
3. Track minimum

Time Complexity:
O(n)

Space Complexity:
O(n)

Concepts Used:
- Hashing
- Sliding window
- Index-based optimization
*/

class Solution {
public:
    int minimumDistance(vector<int>& nums) {

        unordered_map<int,vector<int>> mp;

        // Step 1: Store indices
        for(int i=0;i<nums.size();i++){
            mp[nums[i]].push_back(i);
        }

        int ans = INT_MAX;

        // Step 2: Process each value group
        for(auto i : mp){

            vector<int> temp = i.second;

            int j = 2;

            // Step 3: Sliding window of size 3
            while(j < temp.size()){

                ans = min(ans,
                    abs(temp[j] - temp[j-1]) +
                    abs(temp[j-1] - temp[j-2]) +
                    abs(temp[j-2] - temp[j])
                );

                j++;
            }
        }

        // Step 4: Edge case
        if(ans == INT_MAX){
            return -1;
        }

        return ans;
    }
};