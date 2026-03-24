#include <bits/stdc++.h>
using namespace std;

/*
Problem: Construct Product Matrix
Platform: LeetCode

Approach:
- Treat matrix as a flattened array (row-wise)
- Use prefix and suffix products (like "product of array except self")

Steps:
1. Convert all values mod 12345
2. Build prefix matrix:
    prefix[i][j] = product of all elements before (i,j)
3. Build suffix matrix:
    suffix[i][j] = product of all elements after (i,j)
4. Result:
    grid[i][j] = prefix[i][j] * suffix[i][j] % 12345

Time Complexity: O(n * m)
Space Complexity: O(n * m)

Concepts Used:
- Prefix Product
- Suffix Product
- Modular Arithmetic
*/

class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {

        int n = grid.size();
        int m = grid[0].size();

        // Step 1: Apply modulo
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                grid[i][j] %= 12345;
            }
        }

        vector<vector<int>> prefix(n, vector<int>(m, 1));
        vector<vector<int>> suffix(n, vector<int>(m, 1));

        // Step 2: Prefix product
        int prev = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefix[i][j] = prev;
                prev = (prev * grid[i][j]) % 12345;
            }
        }

        // Step 3: Suffix product
        int next = 1;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                suffix[i][j] = next;
                next = (next * grid[i][j]) % 12345;
            }
        }

        // Step 4: Final result
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                grid[i][j] = (prefix[i][j] * suffix[i][j]) % 12345;
            }
        }

        return grid;
    }
};