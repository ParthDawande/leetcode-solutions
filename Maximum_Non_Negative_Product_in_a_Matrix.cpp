#include <bits/stdc++.h>
using namespace std;

/*
Problem: Maximum Non-Negative Product in a Matrix
Platform: LeetCode

Approach:
- Use DP with two states:
    dp[i][j][0] → maximum product from (i,j) to end
    dp[i][j][1] → minimum product from (i,j) to end

- Why min? Because negative * negative = positive

- Traverse from bottom-right → top-left
- At each cell, consider:
    - Down move
    - Right move

- Compute all possible products and take:
    - max for dp[i][j][0]
    - min for dp[i][j][1]

- Final answer:
    - If max product < 0 → return -1
    - Else return max % MOD

Time Complexity: O(n * m)
Space Complexity: O(n * m)

Concepts Used:
- Dynamic Programming
- Handling negative numbers
*/

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<vector<long long>>> dp(
            n, vector<vector<long long>>(m, vector<long long>(2))
        );

        // Initialize
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dp[i][j][0] = grid[i][j];
                dp[i][j][1] = grid[i][j];
            }
        }

        // Bottom-up DP
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {

                long long num = grid[i][j];

                if (i + 1 < n && j + 1 < m) {
                    dp[i][j][0] = max({
                        num * dp[i + 1][j][0],
                        num * dp[i + 1][j][1],
                        num * dp[i][j + 1][0],
                        num * dp[i][j + 1][1]
                    });

                    dp[i][j][1] = min({
                        num * dp[i + 1][j][0],
                        num * dp[i + 1][j][1],
                        num * dp[i][j + 1][0],
                        num * dp[i][j + 1][1]
                    });
                }
                else if (i + 1 < n) {
                    dp[i][j][0] = max(num * dp[i + 1][j][0], num * dp[i + 1][j][1]);
                    dp[i][j][1] = min(num * dp[i + 1][j][0], num * dp[i + 1][j][1]);
                }
                else if (j + 1 < m) {
                    dp[i][j][0] = max(num * dp[i][j + 1][0], num * dp[i][j + 1][1]);
                    dp[i][j][1] = min(num * dp[i][j + 1][0], num * dp[i][j + 1][1]);
                }
            }
        }

        long long ans = dp[0][0][0];

        if (ans < 0) return -1;

        return ans % 1000000007;
    }
};