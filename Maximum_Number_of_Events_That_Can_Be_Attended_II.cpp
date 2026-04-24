/*
===========================================================
📌 Problem: Maximum Value of Attending Events II
===========================================================

🧠 Idea:
We are given events in the form:
[start, end, value]

We can attend at most k events, and events must NOT overlap.

Goal:
👉 Maximize total value.

-----------------------------------------------------------
🚀 Approach: DP + Binary Search
-----------------------------------------------------------

1. Sort events by start time.

2. At each index, we have two choices:
   ➤ Skip current event
   ➤ Take current event

3. If we take event[i]:
   - We must find the next event whose start > current end
   - This is done using binary search

4. Use DP:
   dp[k][index] = maximum value using k events starting from index

-----------------------------------------------------------
⏱ Complexity:
Time:  O(n log n * k)
Space: O(n * k)

-----------------------------------------------------------
📌 Key Insight:
Binary search helps us jump to the next valid event efficiently.
-----------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int solve(vector<vector<int>>& events, int k, int index, vector<vector<int>> &dp) {
        // Base case
        if(index >= events.size() || k == 0) {
            return 0;
        }

        // Memoization
        if(dp[k][index] != -1) {
            return dp[k][index];
        }

        // Option 1: Skip current event
        int ans1 = solve(events, k, index + 1, dp);

        // Option 2: Take current event
        int index2 = events.size();

        int low = index + 1;
        int high = events.size() - 1;

        // Binary search to find next non-overlapping event
        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(events[mid][0] > events[index][1]) {
                index2 = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        int ans2 = events[index][2] + solve(events, k - 1, index2, dp);

        return dp[k][index] = max(ans1, ans2);
    }

    int maxValue(vector<vector<int>>& events, int k) {
        // Sort by start time
        sort(events.begin(), events.end());

        vector<vector<int>> dp(k + 1, vector<int>(events.size() + 1, -1));

        return solve(events, k, 0, dp);
    }
};