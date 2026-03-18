#include <bits/stdc++.h>
using namespace std;

/*
Problem: Count Submatrices With Sum <= K
Platform: LeetCode

Approach:
1. Convert grid into 2D prefix sum
2. Each cell (i, j) stores sum of submatrix from (0,0) to (i,j)
3. For each row, values are non-decreasing (if all elements >= 0)
4. Use binary search (upper_bound) to count how many <= k

Time Complexity: O(n * m + n * log m)
Space Complexity: O(1)
*/

class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();

        // Step 1: Row-wise prefix sum
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < m; j++) {
                grid[i][j] += grid[i][j - 1];
            }
        }

        // Step 2: Column-wise prefix sum (build full 2D prefix)
        for (int j = 0; j < m; j++) {
            for (int i = 1; i < n; i++) {
                grid[i][j] += grid[i - 1][j];
            }
        }

        long long total = 0;

        // Step 3: Count using binary search
        for (int i = 0; i < n; i++) {
            int index = upper_bound(grid[i].begin(), grid[i].end(), k) - grid[i].begin();
            total += index;
        }

        return (int)total;
    }
};