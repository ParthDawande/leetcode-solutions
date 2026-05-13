/*
    LeetCode - Minimum Moves to Make Array Complementary

    ---------------------------------------------------------
    Problem:
    ---------------------------------------------------------

    We are given:
        nums
        limit

    For every pair:

        nums[i]
        nums[n-1-i]

    We want all pair sums to become SAME.

    In one move:
        change any number to any value
        between [1, limit].

    Goal:
        minimum total moves.

    ---------------------------------------------------------
    Key Observation
    ---------------------------------------------------------

    For a pair (a,b):

        a = min(x,y)
        b = max(x,y)

    We analyze how many operations are needed
    for every possible target sum.

    ---------------------------------------------------------
    Number of Operations Required
    ---------------------------------------------------------

    For target sum S:

    2 moves:
        everywhere initially

    1 move:
        when:
            S in [a+1 , b+limit]

    0 moves:
        when:
            S == a+b

    ---------------------------------------------------------
    Efficient Trick:
    ---------------------------------------------------------

    Use Difference Array.

    Instead of updating every sum individually,
    update ranges in O(1).

    ---------------------------------------------------------
    Transition Logic
    ---------------------------------------------------------

    Initially:
        every sum requires 2 moves

    So:

        diff[2] += 2

    Then optimize ranges.

    ---------------------------------------------------------
    Range Updates
    ---------------------------------------------------------

    For pair (a,b):

    1 move range:
        [a+1 , b+limit]

    0 move point:
        [a+b]

    Using difference array:

        diff[a+1] -= 1
        diff[a+b] -= 1
        diff[a+b+1] += 1
        diff[b+limit+1] += 1

    ---------------------------------------------------------
    Time Complexity:
    ---------------------------------------------------------

    O(n + limit)

    ---------------------------------------------------------
    Space Complexity:
    ---------------------------------------------------------

    O(limit)

*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int minMoves(vector<int>& nums, int limit) {

        /*
            Difference array for sums
        */
        vector<int> diff(2 * limit + 2, 0);

        int n = nums.size();

        /*
            Process symmetric pairs
        */
        for (int i = 0; i < nums.size() / 2; i++) {

            int a = min(nums[i],
                        nums[n - 1 - i]);

            int b = max(nums[i],
                        nums[n - 1 - i]);

            /*
                Initially:
                every sum requires 2 moves
            */
            diff[2] += 2;

            /*
                One move improvement
                range starts
            */
            diff[a + 1] -= 1;

            /*
                Zero move point
            */
            diff[a + b] -= 1;

            /*
                Back to one move
            */
            diff[a + b + 1] += 1;

            /*
                Back to two moves
            */
            diff[b + limit + 1] += 1;
        }

        /*
            Prefix sum reconstruction
        */
        for (int i = 2; i < diff.size(); i++) {

            diff[i] += diff[i - 1];
        }

        /*
            Minimum operations over all sums
        */
        int mini = INT_MAX;

        for (int i = 2; i < diff.size(); i++) {

            mini = min(mini, diff[i]);
        }

        return mini;
    }
};

/*

=========================================================
Example
=========================================================

nums = [1,2,4,3]
limit = 4

Pairs:
(1,3)
(2,4)

For pair (1,3):

Possible sums:
2 to 8

0 move:
4

1 move:
2 to 7

2 moves:
outside

Difference array efficiently tracks this.

=========================================================
Why Difference Array Works
=========================================================

Instead of updating every sum individually:

for s in range:
    cost[s] += x

We do:

diff[l] += x
diff[r+1] -= x

Then prefix sum reconstructs all values.

This reduces complexity dramatically.

=========================================================
Time Complexity
=========================================================

Processing pairs:
O(n)

Prefix sum:
O(limit)

Total:
O(n + limit)

=========================================================
Space Complexity
=========================================================

O(limit)

=========================================================
Git Commit Message
=========================================================

Added difference array solution for minimum complementary array moves

*/