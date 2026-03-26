#include <bits/stdc++.h>
using namespace std;

/*
Problem: Check if Grid Can Be Partitioned into Equal Sum (with Rotation)

Approach:
1. Compute total sum of grid
2. Try partitioning row-wise:
    - Maintain prefix sum (top part)
    - Remaining = bottom part
    - Check if both sums can be made equal:
        a) Directly equal
        b) Removing a single element (using set lookup)

3. To handle vertical partitions:
    - Rotate the grid 90 degrees
    - Repeat the same logic

4. Perform this check for all 4 rotations

Key Observations:
- Instead of checking all submatrices, we only split row-wise
- Rotation converts column splits → row splits
- Using set helps check if removing one element balances partition

Time Complexity:
O(4 * m * n) ≈ O(m * n)

Space Complexity:
O(m * n) (for set in worst case)

Concepts Used:
- Prefix Sum
- Hash Set
- Matrix Rotation
- Greedy Partitioning
*/

class Solution {
public:

    bool check(vector<vector<int>>& grid,long long total){
        int m = grid.size();
        int n = grid[0].size();

        unordered_set<long long> st;
        long long top = 0;

        for(int i = 0; i <= m-2; i++) {

            for(int j = 0; j < n; j++) {
                st.insert(grid[i][j]);
                top += grid[i][j];
            }

            long long bottom = (total - top);
            long long diff = top - bottom;

            // Case 1: equal partition
            if (diff == 0) return true;

            // Case 2: removing boundary elements
            if (diff == (long long)grid[0][0])   return true;
            if (diff == (long long)grid[0][n-1]) return true;
            if (diff == (long long)grid[i][0])   return true;

            // Case 3: removing any element seen so far
            if(i > 0 && n > 1 && st.count(diff)) {
                return true;
            }
        }

        return false;
    }

    vector<vector<int>> rotate(vector<vector<int>>& grid){
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> ans(m,vector<int>(n,0));

        // transpose
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans[j][i] = grid[i][j];
            }
        }

        // reverse rows
        for(int i=0;i<ans.size();i++){
            int l = 0, r = ans[0].size()-1;
            while(l<r){
                swap(ans[i][l],ans[i][r]);
                l++; r--;
            }
        }

        return ans;
    }

    bool canPartitionGrid(vector<vector<int>>& grid) {
        long long total = 0;

        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                total += grid[i][j];
            }
        }

        // Try all 4 orientations
        for(int rot = 0; rot < 4; rot++){
            if(check(grid,total)){
                return true;
            }
            grid = rotate(grid);
        }

        return false;
    }
};