/*
    Problem: Patching Array (LeetCode 330)

    Given a sorted array nums and an integer n,
    add minimum number of patches such that every number
    in range [1, n] can be formed using elements of nums.

    ---------------------------------------------------------
    YOUR APPROACH (Greedy)

    Idea:
    - Maintain a variable `miss` → smallest number we CANNOT form yet.
    - Initially, miss = 1 (we cannot form 1)

    Cases:
    1. If nums[i] <= miss:
       → we can extend reachable range
       → new range becomes [1, miss + nums[i] - 1]

    2. If nums[i] > miss OR no elements left:
       → we must patch by adding `miss`
       → this doubles coverage:
         new range becomes [1, 2*miss - 1]

    ---------------------------------------------------------
    Example:

    nums = [1,3], n = 6

    miss = 1 → use 1 → miss = 2
    miss = 2 → patch 2 → miss = 4
    miss = 4 → use 3 → miss = 7

    Answer = 1 patch

    ---------------------------------------------------------
    Time Complexity: O(n)
    Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        long long miss = 1;   // smallest missing number
        int result = 0;       // number of patches
        int i = 0;            // pointer for nums

        while (miss <= n) {
            // Case 1: nums[i] helps extend coverage
            if (i < nums.size() && nums[i] <= miss) {
                miss += nums[i];
                i++;
            }
            // Case 2: need to patch
            else {
                miss += miss;   // add 'miss' itself
                result++;
            }
        }

        return result;
    }
};

/*
---------------------------------------------------------
Intuition:

At any point, we can form all numbers in [1, miss-1].

If next number <= miss:
    → we extend the range safely

Else:
    → we MUST fill the gap by adding `miss`

Greedy works because:
- Adding the smallest missing number gives maximum coverage

---------------------------------------------------------
Pros:
✔ Optimal O(n) solution
✔ Constant space
✔ Classic greedy pattern

---------------------------------------------------------
*/