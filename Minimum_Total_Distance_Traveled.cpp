#include <bits/stdc++.h>
using namespace std;

/*
Problem: Minimum Total Distance Traveled
Platform: LeetCode

Approach:
- We have:
    robots[] → positions of robots
    factory[] → {position, capacity}

- Goal:
    Assign each robot to a factory
    such that total distance is minimized

Key Observations:
1. Sort robots and factories
2. Assign robots in order (greedy + DP)
3. Each factory can take limited robots

DP State:
    dp[i][j] →
    minimum cost to assign robots[i...] using factories[j...]

Transitions:
1. Skip current factory:
    dp[i][j] = dp[i][j+1]

2. Assign k robots to current factory:
    Try assigning robots[i → i+k-1]
    where k ≤ factory[j].capacity

    Cost:
    sum of distances + dp[i+k][j+1]

Time Complexity:
O(n * m * k)  (k = capacity)

Space Complexity:
O(n * m)

Concepts Used:
- Sorting
- DP (2D)
- Greedy batching
*/

class Solution {
public:

    long long solve(vector<int>& robot,
                    vector<vector<int>>& factory,
                    int index1, int index2,
                    vector<vector<long long>> &dp) {

        // All robots assigned
        if (index1 >= robot.size()) {
            return 0;
        }

        // No factories left
        if (index2 >= factory.size()) {
            return LLONG_MAX;
        }

        if (dp[index1][index2] != -1LL) {
            return dp[index1][index2];
        }

        // Option 1: skip this factory
        long long ans = solve(robot, factory, index1, index2 + 1, dp);

        long long n = robot.size();

        // Max robots this factory can take
        long long limit = min(n, 1LL * (index1 + factory[index2][1]));

        long long t = 0;

        // Option 2: assign robots to this factory
        for (int i = index1; i < limit; i++) {

            t += 1LL * abs(robot[i] - factory[index2][0]);

            long long d = solve(robot, factory, i + 1, index2 + 1, dp);

            if (d != LLONG_MAX) {
                ans = min(ans, t + d);
            }
        }

        return dp[index1][index2] = ans;
    }

    long long minimumTotalDistance(vector<int>& robot,
                                   vector<vector<int>>& factory) {

        // Step 1: Sort
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        vector<vector<long long>> dp(
            robot.size() + 1,
            vector<long long>(factory.size() + 1, -1LL)
        );

        return solve(robot, factory, 0, 0, dp);
    }
};