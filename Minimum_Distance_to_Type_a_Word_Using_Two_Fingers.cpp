#include <bits/stdc++.h>
using namespace std;

/*
Problem: Minimum Distance to Type a Word Using Two Fingers
Platform: LeetCode

Approach:
- We have a keyboard arranged in 6 columns
- Each character has coordinates:
    x = index / 6
    y = index % 6

- Use 2 fingers:
    At each step, choose which finger types the next character

DP State:
    dp[index][i][j]
    index → current character in word
    i → position of finger1 (0–25)
    j → position of finger2 (0–25)

Transition:
    Either:
    1. Move finger1 to current character
    2. Move finger2 to current character

Goal:
    Minimize total movement distance

Time Complexity:
O(n * 26 * 26)

Space Complexity:
O(n * 26 * 26)

Concepts Used:
- 3D DP
- Manhattan distance
- State transitions
*/

class Solution {
public:

    int solve(string word, int index, int i, int j,
              vector<vector<vector<int>>> &dp) {

        if (index >= word.length()) {
            return 0;
        }

        if (dp[index][i][j] != -1) {
            return dp[index][i][j];
        }

        int target = word[index] - 'A';

        // Target coordinates
        int tarx = target / 6;
        int tary = target % 6;

        // Finger1 coordinates
        int ix = i / 6;
        int iy = i % 6;

        // Finger2 coordinates
        int jx = j / 6;
        int jy = j % 6;

        // Option 1: Use finger1
        int ans1 = abs(ix - tarx) + abs(iy - tary) +
                   solve(word, index + 1, target, j, dp);

        // Option 2: Use finger2
        int ans2 = abs(jx - tarx) + abs(jy - tary) +
                   solve(word, index + 1, i, target, dp);

        return dp[index][i][j] = min(ans1, ans2);
    }

    int minimumDistance(string word) {

        int ans = INT_MAX;

        vector<vector<vector<int>>> dp(
            word.size() + 1,
            vector<vector<int>>(26, vector<int>(26, -1))
        );

        // Try all initial finger positions
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                ans = min(ans, solve(word, 0, i, j, dp));
            }
        }

        return ans;
    }
};