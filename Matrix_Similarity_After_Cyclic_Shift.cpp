#include <bits/stdc++.h>
using namespace std;

/*
Problem: Check if Rows are Similar After K Shifts
Platform: LeetCode

Approach:
- Normalize k using modulo (k % m), since shifting m times gives original row
- Create a copy of matrix (arr)
- For each row:
    - Check if every element matches its k-shifted position
    - Compare arr[i][j] with arr[i][(j + k) % m]

- If all rows satisfy cyclic shift condition → return true
- Else return false

Time Complexity: O(n * m)
Space Complexity: O(n * m)

Concepts Used:
- Cyclic Shift (Modulo Arithmetic)
- Matrix Traversal
*/

class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int n = mat.size();
        int m = mat[0].size();

        k = k % m;

        vector<vector<int>> arr(n, vector<int>(m, 0));

        // Copy matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                arr[i][j] = mat[i][j];
            }
        }

        // Check cyclic similarity row-wise
        for (int i = 0; i < n; i++) {
            int j = 0;

            while (j < m) {
                if (arr[i][j] != arr[i][(j + k) % m]) {
                    return false;
                }
                j++;
            }
        }

        return true;
    }
};