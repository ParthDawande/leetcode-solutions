#include <bits/stdc++.h>
using namespace std;

/*
Problem: Minimum Increase to Make Peaks
Platform: LeetCode

Approach:
- We want to convert some indices into "peaks"
  A peak means:
      nums[i] > nums[i-1] and nums[i] > nums[i+1]

- At each index i (1 ≤ i ≤ n-2):
    Two choices:
    1. Skip → move to i+1
    2. Take → make nums[i] a peak and move to i+2

- DP state:
    dp[i] = {number_of_peaks, total_cost}

- Transition:
    - Skip → dp[i+1]
    - Take → dp[i+2] + cost to make nums[i] peak

- Cost calculation:
    nums[i] must be ≥ max(nums[i-1]+1, nums[i+1]+1)

- Compare:
    - Prefer more peaks
    - If equal peaks → minimize cost

Time Complexity: O(n)
Space Complexity: O(n)

Concepts Used:
- DP with decisions
- Greedy peak construction
- Multi-criteria comparison
*/

class Solution {
public:
    long long minIncrease(vector<int>& nums) {

        vector<vector<long long>> dp(nums.size() + 1, vector<long long>(2, 0));

        // Traverse backwards
        for (int i = nums.size() - 2; i >= 1; i--) {

            vector<long long> skip = dp[i + 1];
            vector<long long> take = dp[i + 2];

            // Calculate required height to make nums[i] a peak
            int maxi = max({nums[i], nums[i - 1] + 1, nums[i + 1] + 1});

            // Cost to increase
            take[1] += 1LL * (maxi - nums[i]);
            take[0]++; // increase peak count

            // Choose better option
            if (take[0] < skip[0]) {
                dp[i] = skip;
            } 
            else if (take[0] > skip[0]) {
                dp[i] = take;
            } 
            else {
                // Same number of peaks → minimize cost
                if (take[1] <= skip[1]) {
                    dp[i] = take;
                } else {
                    dp[i] = skip;
                }
            }
        }

        return dp[1][1];
    }
};