#include <bits/stdc++.h>
using namespace std;

/*
Problem: Largest Submatrix With Rearrangements
Link: https://leetcode.com/problems/largest-submatrix-with-rearrangements/

Approach:
1. Convert matrix into heights (like histogram column-wise)
2. For each row:
   - Count heights
   - Use sorting logic via map
   - Calculate max area

Time Complexity: O(n * m log m)
Space Complexity: O(m)
*/

class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        // Step 1: Build heights
        for (int i = 0; i < m; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (matrix[j][i] == 0) {
                    cnt = 0;
                } else {
                    cnt++;
                }
                matrix[j][i] = cnt;
            }
        }

        int maxi = 0;

        // Step 2: Process each row
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            map<int, int> mp;

            for (int j = 0; j < m; j++) {
                if (matrix[i][j] != 0) {
                    cnt++;
                    mp[matrix[i][j]]++;
                }
            }

            for (auto it : mp) {
                maxi = max(maxi, it.first * cnt);
                cnt -= it.second;
            }
        }

        return maxi;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> matrix = {
        {0, 0, 1},
        {1, 1, 1},
        {1, 0, 1}
    };

    cout << "Largest Submatrix Area: " << sol.largestSubmatrix(matrix) << endl;

    return 0;
}