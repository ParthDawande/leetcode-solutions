#include <bits/stdc++.h>
using namespace std;

/*
Problem: Maximum Amount with Limited Negative Skips
Platform: LeetCode

Approach:
- Use DP with state (x, y, r):
    x, y → current position
    r → number of skips allowed (for negative cells)

- At each cell:
    1. If positive:
        - Must take it
        - Move right or down

    2. If negative:
        - Option 1: Take it (add value)
        - Option 2: Skip it (if r > 0)

- Use recursion + memoization

- Base cases:
    - Out of bounds → invalid (INT_MIN)
    - Reached end → return 0

Time Complexity:
O(n * m * r)

Space Complexity:
O(n * m * r)

Concepts Used:
- 3D DP
- Grid traversal
- Recursion + Memoization
*/

class Solution {
public:

    int solve(vector<vector<int>>& coins,int x,int y,int r,vector<vector<vector<int>>> &dp){
        
        // Reached beyond valid path
        if((x>=coins.size() && y==coins[0].size()-1) || 
           (x==coins.size()-1 && y>=coins[0].size())){
            return 0;
        }

        // Out of bounds
        if(x>=coins.size() || y>=coins[0].size()){
            return INT_MIN;
        }

        // No skips left
        if(r < 0){
            return INT_MIN;
        }
        
        // Memoization
        if(dp[x][y][r] != -600000){
            return dp[x][y][r];
        }

        int ans = 0;

        // Case 1: Positive cell
        if(coins[x][y] > 0){
            ans = coins[x][y];

            int down = solve(coins,x+1,y,r,dp);
            int right = solve(coins,x,y+1,r,dp);

            if(max(down, right) != INT_MIN){
                return dp[x][y][r] = ans + max(down, right);
            }
            return INT_MIN;
        }
        else{
            // Case 2: Negative cell

            int take = coins[x][y];

            int down = solve(coins,x+1,y,r,dp);
            int right = solve(coins,x,y+1,r,dp);

            if(max(down, right) != INT_MIN){
                ans = take + max(down, right);
            }

            // Option: skip negative
            if(r > 0){
                int downSkip = solve(coins,x+1,y,r-1,dp);
                int rightSkip = solve(coins,x,y+1,r-1,dp);

                if(max(downSkip, rightSkip) != INT_MIN){
                    ans = max(ans, max(downSkip, rightSkip));
                }
            }

            return dp[x][y][r] = ans;
        }
    }

    int maximumAmount(vector<vector<int>>& coins) {
        int n = coins.size();
        int m = coins[0].size();

        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(m, vector<int>(3, -600000))
        );

        return solve(coins, 0, 0, 2, dp);
    }
};