/*
    LeetCode - Maximum Number of Jumps to Reach the Last Index

    Approach:
    ----------
    We use Dynamic Programming + Recursion (Memoization).

    From every index:
    -> Try jumping to all future indices.
    -> A jump is valid if:

       abs(nums[i] - nums[index]) <= target

    We recursively compute:
    maximum jumps possible from current index to reach the end.

    ------------------------------------------------------

    State:
    dp[index]
    = maximum jumps possible starting from index.

    ------------------------------------------------------

    Transition:
    For every i > index:

        if valid jump:
            ans = max(ans, 1 + solve(i))

    ------------------------------------------------------

    Base Case:
    If index reaches last index:
        return 0

    ------------------------------------------------------

    Example:
    nums = [1,3,6,4,1,2]
    target = 2

    1 -> 3 -> 4 -> 2

    Total jumps = 3

    ------------------------------------------------------

    Time Complexity:
    O(n^2)

    For every index we may try all future indices.

    Space Complexity:
    O(n)

*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int solve(vector<int>& nums,
              int target,
              int index,
              vector<int>& dp) {

        /*
            Reached last index
        */
        if (index >= nums.size() - 1) {
            return 0;
        }

        /*
            Memoization
        */
        if (dp[index] != -1) {
            return dp[index];
        }

        int ans = INT_MIN;

        /*
            Try all possible jumps
        */
        for (int i = index + 1; i < nums.size(); i++) {

            /*
                Valid jump condition
            */
            if (abs(nums[i] - nums[index]) <= target) {

                ans = max(ans,
                          1 + solve(nums, target, i, dp));
            }
        }

        /*
            No valid path found
        */
        if (ans < 0) {
            return dp[index] = INT_MIN;
        }

        return dp[index] = ans;
    }

    int maximumJumps(vector<int>& nums, int target) {

        int n = nums.size();

        vector<int> dp(n + 1, -1);

        int ans = solve(nums, target, 0, dp);

        /*
            Cannot reach end
        */
        if (ans == INT_MIN) {
            return -1;
        }

        return ans;
    }
};

/*

-----------------------------------
Dry Run
-----------------------------------

nums = [1,3,6,4,1,2]
target = 2

index = 0

Possible jumps:
1 -> 3

Then:
3 -> 4
4 -> 2

Total jumps = 3

Answer = 3

-----------------------------------
Time Complexity
-----------------------------------

O(n^2)

-----------------------------------
Space Complexity
-----------------------------------

O(n)

-----------------------------------
Git Commit Message
-----------------------------------

Added memoized DP solution for maximum jumps problem

-----------------------------------
Git Push Commands
-----------------------------------

git add .
git commit -m "Added maximum jumps DP solution"
git push origin main

*/