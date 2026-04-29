#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ============================================================
    PROBLEM INTUITION
    ------------------------------------------------------------
    We process the grid column by column.

    At each column:
    - We choose a "cut" row (i)
    - Based on previous choice (last), we decide:
        → Take from current column
        → Or take from previous column

    PARAMETERS:
    ------------------------------------------------------------
    index → current column
    last  → previous chosen boundary (row index)
    f     → flag (state of transition)

    dp[index][last][f] = maximum score from this state
    ============================================================
    */

    long long solve(vector<vector<long long>> &grid,
                    int index,
                    int last,
                    int f,
                    vector<vector<vector<long long>>> &dp) {

        // Base case: all columns processed
        if(index >= grid.size()){
            return 0LL;
        }

        // Memoization
        if(dp[index][last][f] != -1LL){
            return dp[index][last][f];
        }

        long long ans = 0;

        /*
        Try all possible row cuts i (0 → n)
        */
        for(int i = 0; i <= grid.size(); i++){

            long long curr = 0LL;

            /*
            ====================================================
            CASE 1: i <= last
            ----------------------------------------------------
            Take segment from CURRENT column

            Using prefix sum:
            grid[x][col] = sum from row 0 → x

            So segment [i ... last-1] =
                grid[last-1][index] - grid[i-1][index]
            ====================================================
            */
            if(i <= last){

                if(last - 1 >= 0){
                    curr = grid[last - 1][index];
                }
                if(i - 1 >= 0){
                    curr -= grid[i - 1][index];
                }

                ans = max(ans,
                          max(curr + solve(grid, index + 1, i, 1, dp),
                              solve(grid, index + 1, i, 0, dp)));
            }

            /*
            ====================================================
            CASE 2: i > last
            ----------------------------------------------------
            Take segment from PREVIOUS column

            Segment [last ... i-1] in column (index-1)
            ====================================================
            */
            else{

                if(index - 1 >= 0){

                    if(i - 1 >= 0){
                        curr = grid[i - 1][index - 1];
                    }
                    if(last - 1 >= 0){
                        curr -= grid[last - 1][index - 1];
                    }

                    /*
                    Only allowed when f == 0
                    */
                    if(f == 0){
                        ans = max(ans,
                                  curr + solve(grid, index + 1, i, 0, dp));
                    }
                }

                /*
                First column → no previous column exists
                */
                else{
                    ans = max(ans,
                              solve(grid, index + 1, i, 0, dp));
                }
            }
        }

        return dp[index][last][f] = ans;
    }

    /*
    ============================================================
    MAIN FUNCTION
    ============================================================
    */
    long long maximumScore(vector<vector<int>>& grid) {

        int n = grid.size();

        /*
        Build column-wise prefix sum
        --------------------------------------------------------
        prefix[i][j] = sum of column j from row 0 → i
        */
        vector<vector<long long>> prefix(n, vector<long long>(n, 0LL));

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                prefix[i][j] = 1LL * grid[i][j];
            }
        }

        for(int j = 0; j < n; j++){
            for(int i = 1; i < n; i++){
                prefix[i][j] += prefix[i - 1][j];
            }
        }

        /*
        3D DP:
        index × last × flag
        */
        vector<vector<vector<long long>>> dp(
            105, vector<vector<long long>>(105, vector<long long>(2, -1LL))
        );

        return solve(prefix, 0, 0, 0, dp);
    }
};