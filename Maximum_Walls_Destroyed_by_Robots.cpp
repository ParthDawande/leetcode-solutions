#include <bits/stdc++.h>
using namespace std;

/*
Problem: Maximum Walls Covered by Robots
Platform: LeetCode

Approach:
- Each robot can extend either LEFT or RIGHT within its distance
- While choosing direction, we must:
    1. Avoid overlapping with previous robot decisions
    2. Stay within valid boundaries
    3. Count walls covered using binary search

- Use DP:
    dp[index][d]
        index → current robot
        d → previous robot direction (0 = LEFT, 1 = RIGHT)

Steps:
1. Sort robots by position
2. Sort walls
3. For each robot:
    - Option 1: Extend LEFT
    - Option 2: Extend RIGHT
4. Use binary search to count walls in range
5. Take max of both options

Time Complexity:
O(n * log m)

Space Complexity:
O(n)

Concepts Used:
- DP (Top-down)
- Binary Search (lower_bound, upper_bound)
- Greedy interval handling
*/

class Solution {
public:

    int solve(vector<vector<int>>& arr, vector<int>& walls, int index, int d,
              vector<vector<int>>& dp) {

        // Base case
        if (index >= arr.size()) {
            return 0;
        }

        // Memoization
        if (dp[index][d] != -1) {
            return dp[index][d];
        }

        int ans = 0;

        // ---------------- LEFT ----------------

        int L = arr[index][0] - arr[index][1];

        // Avoid overlap with previous robot
        if (index - 1 >= 0) {
            L = max(L, arr[index - 1][0] + 1);
        }

        // If previous was RIGHT, adjust more strictly
        if (d == 1) {
            int prevR = min(arr[index - 1][0] + arr[index - 1][1],
                            arr[index][0] - 1);
            L = max(L, prevR + 1);
        }

        int R = arr[index][0];

        // Count walls in [L, R]
        int left = lower_bound(walls.begin(), walls.end(), L) - walls.begin();
        int right = upper_bound(walls.begin(), walls.end(), R) - walls.begin();

        int count = right - left;

        ans = max(ans, count + solve(arr, walls, index + 1, 0, dp));

        // ---------------- RIGHT ----------------

        int L1 = arr[index][0];
        int R1 = arr[index][0] + arr[index][1];

        // Avoid overlap with next robot
        if (index + 1 < arr.size()) {
            R1 = min(R1, arr[index + 1][0] - 1);
        }

        // Count walls in [L1, R1]
        int left1 = lower_bound(walls.begin(), walls.end(), L1) - walls.begin();
        int right1 = upper_bound(walls.begin(), walls.end(), R1) - walls.begin();

        int count1 = right1 - left1;

        ans = max(ans, count1 + solve(arr, walls, index + 1, 1, dp));

        return dp[index][d] = ans;
    }

    int maxWalls(vector<int>& robots, vector<int>& distance,
                 vector<int>& walls) {

        vector<vector<int>> arr;

        // Combine robots and distances
        for (int i = 0; i < robots.size(); i++) {
            arr.push_back({robots[i], distance[i]});
        }

        // Sort robots and walls
        sort(arr.begin(), arr.end());
        sort(walls.begin(), walls.end());

        vector<vector<int>> dp(arr.size() + 1, vector<int>(2, -1));

        return solve(arr, walls, 0, 0, dp);
    }
};