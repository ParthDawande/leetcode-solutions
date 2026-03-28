#include <bits/stdc++.h>
using namespace std;

/*
Problem: Find the String from LCP Matrix
Platform: LeetCode

Approach:
1. Validate LCP matrix:
    - lcp[i][i] must be n - i (suffix matches itself)
    - lcp must be symmetric
    - lcp[i][j] ≤ n - j
    - If lcp[i][j] > 0:
        lcp[i][j] = 1 + lcp[i+1][j+1]

2. Construct string:
    - Start with all 'a'
    - For each pair (i, j):
        - If lcp[i][j] > 0 → characters must be same
        - If lcp[i][j] == 0 → characters must differ

3. Adjust characters greedily:
    - If conflict arises → return ""
    - Ensure characters do not exceed 'z'

4. Return constructed string

Time Complexity: O(n^2)
Space Complexity: O(n)

Concepts Used:
- String Construction
- LCP (Longest Common Prefix)
- Matrix Validation
- Greedy Assignment
*/

class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();

        // Step 1: Validate diagonal
        for (int i = 0; i < n; i++) {
            if (lcp[i][i] != n - i) {
                return "";
            }
        }

        // Step 2: Check symmetry
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (lcp[i][j] != lcp[j][i]) {
                    return "";
                }
            }
        }

        // Step 3: Bound check
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (lcp[i][j] > n - j) {
                    return "";
                }
            }
        }

        // Step 4: Recurrence validation
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (lcp[i][j] != 0) {
                    if (i + 1 < n && j + 1 < n) {
                        if (lcp[i][j] != 1 + lcp[i + 1][j + 1]) {
                            return "";
                        }
                    }
                }
            }
        }

        // Step 5: Build string
        string h(n, 'a');

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                if (lcp[i][j] == 0) {
                    // must be different
                    if (h[i] == h[j]) {
                        h[j] = (char)(h[i] + 1);
                    }
                } else {
                    // must be same
                    if (h[i] != h[j]) {
                        return "";
                    }
                }
            }
        }

        // Step 6: Check valid characters
        for (char c : h) {
            if (c > 'z') return "";
        }

        return h;
    }
};