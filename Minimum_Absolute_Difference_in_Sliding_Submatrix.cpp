#include <bits/stdc++.h>
using namespace std;

/*
Problem: Minimum Absolute Difference in Each K x K Submatrix

Approach:
- Traverse all k x k submatrices
- Extract unique elements
- Sort them
- Compute minimum difference between consecutive elements

Time Complexity:
O((n-k+1)*(m-k+1)*k^2 log(k^2))

Space Complexity:
O(k^2)
*/

class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> ans;

        // Traverse all top-left corners of k x k submatrix
        for (int i = 0; i <= n - k; i++) {
            vector<int> row;

            for (int j = 0; j <= m - k; j++) {

                vector<int> arr;
                unordered_map<int, int> mp;

                // Extract k x k submatrix
                for (int x = 0; x < k; x++) {
                    for (int y = 0; y < k; y++) {
                        int val = grid[i + x][j + y];

                        // Keep only unique elements
                        if (mp.find(val) == mp.end()) {
                            arr.push_back(val);
                            mp[val]++;
                        }
                    }
                }

                // If only one unique element
                if (arr.size() == 1) {
                    row.push_back(0);
                } else {
                    // Sort values
                    sort(arr.begin(), arr.end());

                    int mini = INT_MAX;

                    // Find minimum absolute difference
                    for (int t = 0; t < arr.size() - 1; t++) {
                        mini = min(mini, abs(arr[t] - arr[t + 1]));
                    }

                    row.push_back(mini);
                }
            }

            ans.push_back(row);
        }

        return ans;
    }
};