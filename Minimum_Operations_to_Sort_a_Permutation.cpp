/*
========================================================
Minimum Operations to Make Array Sorted
========================================================

Problem:
Given a circular array nums,
find the minimum operations needed
to make the array sorted.

Operations allowed:
- Rotate array
- Reverse + rotate

Return:
- Minimum operations required
- Or -1 if impossible

========================================================
Idea Behind the Solution
========================================================

This solution checks BOTH possibilities:

1. Array can become increasing sorted
2. Array can become decreasing sorted

We count the number of "break points".

--------------------------------------------------------
Break Point
--------------------------------------------------------

For increasing sorted circular array:

nums[i] > nums[i+1]

should happen at most once.

Example:
[3,4,5,1,2]

Only one break:
5 > 1

So this is a rotated sorted array.

--------------------------------------------------------
Similarly for decreasing sorted:
--------------------------------------------------------

nums[i] < nums[i+1]

should happen at most once.

========================================================
Functions
========================================================

1. check1(nums)
Counts decreasing violations.

Used for:
Increasing rotated sorted check.

--------------------------------------------------------

2. check2(nums)
Counts increasing violations.

Used for:
Decreasing rotated sorted check.

========================================================
Approach
========================================================

CASE 1:
Array can become increasing sorted

- Find pivot using binary search
- Compute minimum rotations

--------------------------------------------------------

CASE 2:
Array can become decreasing sorted

- Again find pivot
- Compute reverse rotation cost

--------------------------------------------------------

Take minimum among both.

========================================================
Complexity
========================================================

Time Complexity:
O(n) + O(log n)

= O(n)

Space Complexity:
O(1)

========================================================
Dry Run
========================================================

nums = [3,4,5,1,2]

check1 = 1

Binary search pivot:
index = 3

Operations:
min(index, n-index+2)

Answer = 3

========================================================
Code
========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ----------------------------------------------------
    Counts decreasing violations
    Used for increasing sorted rotation
    ----------------------------------------------------
    */
    int check1(vector<int> &nums) {

        int cnt = 0;

        for(int i = 0; i < nums.size() - 1; i++) {

            if(nums[i] > nums[i + 1]) {
                cnt++;
            }
        }

        int n = nums.size();

        if(nums[n - 1] > nums[0]) {
            cnt++;
        }

        return cnt;
    }

    /*
    ----------------------------------------------------
    Counts increasing violations
    Used for decreasing sorted rotation
    ----------------------------------------------------
    */
    int check2(vector<int> &nums) {

        int cnt = 0;

        for(int i = 0; i < nums.size() - 1; i++) {

            if(nums[i] < nums[i + 1]) {
                cnt++;
            }
        }

        int n = nums.size();

        if(nums[n - 1] < nums[0]) {
            cnt++;
        }

        return cnt;
    }

    int minOperations(vector<int>& nums) {

        /*
        ------------------------------------------------
        Edge Cases
        ------------------------------------------------
        */

        if(nums.size() == 1) {
            return 0;
        }

        if(nums.size() == 2) {

            if(nums[0] < nums[1]) {
                return 0;
            }

            return 1;
        }

        int n = nums.size();

        int cnt1 = check1(nums);

        int cnt2 = check2(nums);

        int ans = INT_MAX;

        /*
        =================================================
        CASE 1:
        Increasing Rotated Sorted Array
        =================================================
        */

        if(cnt1 <= 1) {

            int index = -1;

            int l = 0;
            int r = n - 1;

            // Already sorted
            if(nums[l] < nums[r]) {
                return 0;
            }

            /*
            Find pivot using binary search
            */
            while(l <= r) {

                int m = l + (r - l) / 2;

                if(nums[0] <= nums[m]) {

                    l = m + 1;
                }
                else {

                    index = m;

                    r = m - 1;
                }
            }

            /*
            Rotation cost
            */
            ans = min(ans,
                      min(index,
                          (n - index) + 2));
        }

        /*
        =================================================
        CASE 2:
        Decreasing Rotated Sorted Array
        =================================================
        */

        if(cnt2 <= 1) {

            int index = -1;

            int l = 0;
            int r = n - 1;

            // Already reverse sorted
            if(nums[l] > nums[r]) {
                return 1;
            }

            /*
            Find pivot
            */
            while(l <= r) {

                int m = l + (r - l) / 2;

                if(nums[0] >= nums[m]) {

                    index = m;

                    l = m + 1;
                }
                else {

                    r = m - 1;
                }
            }

            /*
            Reverse rotation cost
            */
            ans = min(ans,
                      min(index + 2,
                          n - index));
        }

        if(ans == INT_MAX) {
            return -1;
        }

        return ans;
    }
};

/*
========================================================
Important Notes
========================================================

Increasing Rotation:
- Only one decreasing breakpoint allowed

Decreasing Rotation:
- Only one increasing breakpoint allowed

Binary search helps locate pivot efficiently.

*/