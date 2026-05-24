/*
========================================================
Jump Game V
========================================================

Problem:
Given an array arr and an integer d,
you can jump from index i to:

1. Any index j on the LEFT within distance d
2. Any index j on the RIGHT within distance d

Conditions:
- arr[j] < arr[i]
- All elements between i and j must also be smaller
- If a greater/equal element appears, movement stops

Return the maximum number of indices
that can be visited.

========================================================
Approach Used
========================================================

This solution uses:

1. DFS + Memoization (Top Down DP)

For every index:
- Try jumping LEFT
- Try jumping RIGHT
- Take the best possible path

--------------------------------------------------------
Key Observation
--------------------------------------------------------

From index i,
we can only move to smaller values.

Therefore,
the graph is acyclic,
which makes DP possible.

--------------------------------------------------------
DP Definition
--------------------------------------------------------

dp[i] =
Maximum jumps possible starting from index i

--------------------------------------------------------
Transition
--------------------------------------------------------

For every valid jump:

dp[i] =
1 + max(dp[nextIndex])

The +1 counts current index itself.

--------------------------------------------------------
Left Expansion
--------------------------------------------------------

We move left up to distance d.

Stop immediately if:
arr[t2] >= arr[index]

because movement beyond that point
is invalid.

--------------------------------------------------------
Right Expansion
--------------------------------------------------------

Similarly,
move right up to distance d.

Stop when:
arr[t1] >= arr[index]

--------------------------------------------------------
Complexity
========================================================

Let:
n = arr.size()

Each index explores at most d positions.

Time Complexity:
O(n * d)

Space Complexity:
O(n)

========================================================
Dry Run
========================================================

arr = [6,4,14,6,8,13,9,7,10,6,12]
d = 2

From index 10 (12):
Can jump to:
10 -> 8 -> 6 -> 7

Maximum path length computed using DFS + DP.

========================================================
Code
========================================================
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int solve(vector<int>& arr,
              int d,
              int index,
              vector<int> &dp) {

        // Out of bounds
        if(index >= arr.size()) {
            return 0;
        }

        // Memoized result
        if(dp[index] != -1) {
            return dp[index];
        }

        // Minimum answer is 1
        // (current index itself)
        int ans = 1;

        int curr = 0;

        int n = arr.size();

        /*
        ------------------------------------------------
        Explore RIGHT side
        ------------------------------------------------
        */

        int t1 = index + 1;

        while(t1 <= min(n - 1, index + d)) {

            // Cannot cross greater/equal element
            if(arr[t1] >= arr[index]) {
                break;
            }

            curr = max(curr,
                       solve(arr, d, t1, dp));

            t1++;
        }

        /*
        ------------------------------------------------
        Explore LEFT side
        ------------------------------------------------
        */

        int t2 = index - 1;

        while(t2 >= max(0, index - d)) {

            // Cannot cross greater/equal element
            if(arr[t2] >= arr[index]) {
                break;
            }

            curr = max(curr,
                       solve(arr, d, t2, dp));

            t2--;
        }

        // Include current index
        return dp[index] = ans + curr;
    }

    int maxJumps(vector<int>& arr, int d) {

        int n = arr.size();

        int ans = 0;

        vector<int> dp(n, -1);

        // Try starting from every index
        for(int i = 0; i < arr.size(); i++) {

            ans = max(ans,
                      solve(arr, d, i, dp));
        }

        return ans;
    }
};

