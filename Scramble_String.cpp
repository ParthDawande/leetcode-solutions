#include <bits/stdc++.h>
using namespace std;

/*
Problem: Scramble String
--------------------------------------------------

Definition:
A string is a scrambled version of another if:
- You can recursively split it into two parts
- Optionally swap the parts
- Continue recursively

--------------------------------------------------
APPROACH 1: 4D DP (Your First Code)
--------------------------------------------------

State:
dp[x1][y1][x2][y2]
→ s1[x1..y1] can form s2[x2..y2]

Transition:
Try all splits:
1. No swap
2. Swap

Time: O(n^4)
Space: O(n^4)

--------------------------------------------------
APPROACH 2: 3D DP (Optimized)
--------------------------------------------------

State:
dp[i][j][len]
→ s1[i..i+len-1] can form s2[j..j+len-1]

Why better:
- Removes redundant dimensions
- Same logic, less memory

Time: O(n^4)
Space: O(n^3)

--------------------------------------------------
*/

class Solution {
public:

    // -------------------------------
    // APPROACH 1: 4D DP
    // -------------------------------
    bool solve4D(string s1, string s2,
                 int x1, int y1,
                 int x2, int y2,
                 vector<vector<vector<vector<int>>>> &dp) {

        if (x1 == y1) {
            return s1[x1] == s2[x2];
        }

        if (dp[x1][y1][x2][y2] != -1) {
            return dp[x1][y1][x2][y2];
        }

        bool ans = false;
        int len = y1 - x1 + 1;

        for (int i = x1; i < y1; i++) {

            int len1 = i - x1 + 1;
            int len2 = len - len1;

            // No swap
            bool ans1 =
                solve4D(s1, s2, x1, x1 + len1 - 1, x2, x2 + len1 - 1, dp) &&
                solve4D(s1, s2, i + 1, y1, x2 + len1, y2, dp);

            // Swap
            bool ans2 =
                solve4D(s1, s2, x1, x1 + len1 - 1, y2 - len1 + 1, y2, dp) &&
                solve4D(s1, s2, i + 1, y1, x2, x2 + len2 - 1, dp);

            ans = ans || ans1 || ans2;

            if (ans) break;
        }

        return dp[x1][y1][x2][y2] = ans;
    }

    bool approach4D(string s1, string s2) {
        int n = s1.length();

        vector<vector<vector<vector<int>>>> dp(
            n + 1,
            vector<vector<vector<int>>>(
                n + 1,
                vector<vector<int>>(
                    n + 1,
                    vector<int>(n + 1, -1)
                )
            )
        );

        return solve4D(s1, s2, 0, n - 1, 0, n - 1, dp);
    }

    // -------------------------------
    // APPROACH 2: 3D DP (Your Code)
    // -------------------------------
    int solve3D(string s1, string s2,
                int i, int j, int len,
                vector<vector<vector<int>>> &dp) {

        if (len == 1) {
            return s1[i] == s2[j];
        }

        if (dp[i][j][len] != -1) {
            return dp[i][j][len];
        }

        bool ans = false;

        for (int k = 1; k < len; k++) {

            // No swap
            bool ans1 =
                solve3D(s1, s2, i, j, k, dp) &&
                solve3D(s1, s2, i + k, j + k, len - k, dp);

            // Swap
            bool ans2 =
                solve3D(s1, s2, i, j + len - k, k, dp) &&
                solve3D(s1, s2, i + k, j, len - k, dp);

            ans = ans || ans1 || ans2;

            if (ans) break;
        }

        return dp[i][j][len] = ans;
    }

    bool approach3D(string s1, string s2) {
        int n = s1.length();

        vector<vector<vector<int>>> dp(
            n + 1,
            vector<vector<int>>(n + 1, vector<int>(n + 1, -1))
        );

        return solve3D(s1, s2, 0, 0, n, dp);
    }

    // -------------------------------
    // MAIN FUNCTION
    // -------------------------------
    bool isScramble(string s1, string s2) {

        // Use optimized version by default
        return approach3D(s1, s2);

        // You can switch:
        // return approach4D(s1, s2);
    }
};