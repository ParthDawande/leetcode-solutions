/*
    LeetCode - Minimum Initial Energy to Finish Tasks

    ---------------------------------------------------------
    Problem:
    ---------------------------------------------------------

    Each task is represented as:

        [actual, minimum]

    actual  = energy consumed after completing task
    minimum = minimum energy required before starting task

    We need to find:
    -> Minimum initial energy required
       to complete all tasks.

    ---------------------------------------------------------
    Key Observation:
    ---------------------------------------------------------

    We should perform tasks with larger:

        (minimum - actual)

    later? No.

    Actually we sort by:

        actual - minimum

    ascending

    equivalent to:

        minimum - actual

    descending

    This greedily prioritizes tasks that require
    much higher starting energy.

    ---------------------------------------------------------
    Why Sorting Works
    ---------------------------------------------------------

    Suppose two tasks:

        A = [a1, m1]
        B = [a2, m2]

    We compare:

        m1 - a1
        m2 - a2

    Task with larger gap should come earlier.

    This minimizes required starting energy.

    ---------------------------------------------------------
    Included Approaches:
    ---------------------------------------------------------

    1. Binary Search + Simulation
    2. Greedy Optimal Solution

*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
        Comparator

        Sort by:
            actual - minimum

        ascending
    */
    static bool cmp(vector<int>& a, vector<int>& b) {

        return a[1] - a[0] < b[1] - b[0];
    }

    /*
    =========================================================
                    APPROACH 1
            Binary Search + Simulation
    =========================================================

    Idea:
    -----
    Binary search answer (initial energy).

    For every energy:
        simulate all tasks.

    If all tasks possible:
        try smaller energy.

    Else:
        increase energy.

    Time Complexity:
    ----------------
    O(n log answer)

    */
    bool check(vector<vector<int>>& tasks, int e) {

        for (int i = 0; i < tasks.size(); i++) {

            /*
                Need at least minimum energy
            */
            if (tasks[i][1] <= e) {

                /*
                    Spend actual energy
                */
                e -= tasks[i][0];
            }

            else {
                return false;
            }
        }

        return true;
    }

    int minimumEffort(vector<vector<int>>& tasks) {

        /*
            Sort tasks greedily
        */
        sort(tasks.begin(), tasks.end(), cmp);

        /*
        =====================================================
                    APPROACH 1
            Binary Search + Simulation
        =====================================================

        Uncomment to use.
        */

        /*
        int l = 1;
        int r = INT_MAX;

        int ans = -1;

        while (l <= r) {

            int m = l + (r - l) / 2;

            if (check(tasks, m)) {

                ans = m;

                r = m - 1;
            }

            else {

                l = m + 1;
            }
        }

        return ans;
        */

        /*
        =====================================================
                    APPROACH 2
                Optimal Greedy
        =====================================================

        Idea:
        -----
        Maintain minimum energy needed so far.

        For every task:

            energy_before_task >= minimum

        So:

            ans = max(ans + actual, minimum)

        Why?
        ----
        If current energy is not enough,
        increase initial energy.

        Time Complexity:
        ----------------
        O(n log n)

        due to sorting.

        Space Complexity:
        -----------------
        O(1)
        */

        int ans = 0;

        for (int i = 0; i < tasks.size(); i++) {

            /*
                Either:
                1. continue with previous energy
                2. increase to meet minimum requirement
            */
            ans = max(ans + tasks[i][0],
                      tasks[i][1]);
        }

        return ans;
    }
};

/*

=========================================================
Example
=========================================================

tasks = [[1,2],[2,4],[4,8]]

After sorting:
same order

Process:

ans = 0

Task 1:
max(0+1,2) = 2

Task 2:
max(2+2,4) = 4

Task 3:
max(4+4,8) = 8

Answer = 8

=========================================================
Approach Comparison
=========================================================

1. Binary Search
----------------
Pros:
- Easy to think about
- Generic

Cons:
- Slower
- Extra log factor

Time:
O(n log answer)

---------------------------------------------------------

2. Greedy Optimal
-----------------
Pros:
- Elegant
- Fast
- Optimal

Time:
O(n log n)

Preferred approach.

=========================================================
Time Complexity
=========================================================

Sorting:
O(n log n)

Greedy traversal:
O(n)

Total:
O(n log n)

=========================================================
Space Complexity
=========================================================

O(1)

=========================================================
Git Commit Message
=========================================================

Added binary search and greedy solutions for minimum initial energy problem


*/