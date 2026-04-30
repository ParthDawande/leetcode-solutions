#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ============================================================
    PROBLEM INTUITION
    ------------------------------------------------------------
    - We move from (0,0) → (n-1,m-1)
    - Allowed moves: RIGHT or DOWN

    - Each cell has a value:
        → positive → requires "charge"
        → negative → free (no charge needed)

    - We have at most k charges
    - Goal: maximize path sum

    ============================================================
    STATE DEFINITION
    ------------------------------------------------------------
    dp[x][y][k] = maximum score from (x,y) → destination
                  with k charges remaining
    ============================================================
    */

    int solve(vector<vector<int>>& grid,
              int x, int y, int k,
              vector<vector<vector<int>>> &dp){

        /*
        ========================================================
        BASE CASE: reached destination
        ========================================================
        */
        if(x == grid.size() - 1 && y == grid[0].size() - 1){

            // If positive cell → need 1 charge
            if(grid[x][y] > 0){
                if(k > 0){
                    return grid[x][y];
                }
                return -90000; // impossible
            }

            // negative or zero → no charge needed
            return grid[x][y];
        }

        /*
        ========================================================
        MEMOIZATION
        ========================================================
        */
        if(dp[x][y][k] != -1){
            return dp[x][y][k];
        }

        int curr = grid[x][y];

        /*
        charge = 1 if positive cell else 0
        */
        int charge = (grid[x][y] > 0 ? 1 : 0);

        /*
        If not enough charge → invalid path
        */
        if(k - charge < 0){
            return -90000;
        }

        int ans = -90000;

        /*
        ========================================================
        TRY MOVES
        ========================================================
        */

        // DOWN
        if(x + 1 < grid.size()){
            ans = max(ans,
                      curr + solve(grid, x + 1, y, k - charge, dp));
        }

        // RIGHT
        if(y + 1 < grid[0].size()){
            ans = max(ans,
                      curr + solve(grid, x, y + 1, k - charge, dp));
        }

        return dp[x][y][k] = ans;
    }

    /*
    ============================================================
    MAIN FUNCTION
    ============================================================
    */
    int maxPathScore(vector<vector<int>>& grid, int k) {

        int n = grid.size();
        int m = grid[0].size();

        /*
        3D DP:
        n × m × k
        */
        vector<vector<vector<int>>> dp(
            n + 1,
            vector<vector<int>>(m + 1, vector<int>(k + 1, -1))
        );

        int ans = solve(grid, 0, 0, k, dp);

        /*
        If negative → no valid path
        */
        if(ans < 0){
            return -1;
        }

        return ans;
    }
};