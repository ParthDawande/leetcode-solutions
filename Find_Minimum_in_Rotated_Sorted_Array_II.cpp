/*
    LeetCode - Find Minimum in Rotated Sorted Array II

    ---------------------------------------------------------
    Problem:
    ---------------------------------------------------------

    We are given:
        a rotated sorted array
        possibly containing duplicates.

    We need to find:
        minimum element.

    ---------------------------------------------------------
    Examples
    ---------------------------------------------------------

    nums = [3,4,5,1,2]

    Rotated at index 3

    Minimum = 1

    ---------------------------------------------------------

    nums = [2,2,2,0,1]

    Minimum = 0

    ---------------------------------------------------------
    Key Observation
    ---------------------------------------------------------

    In rotated sorted array:

        Left part  -> larger values
        Right part -> smaller values

    Minimum lies in the sorted transition point.

    ---------------------------------------------------------
    Important Duplicate Handling
    ---------------------------------------------------------

    Example:

        [2,2,2,0,1,2]

    Here:

        nums[l] == nums[r]

    Binary search becomes ambiguous.

    So we shrink left pointer:

        l++

    until ambiguity reduces.

    ---------------------------------------------------------
    Binary Search Logic
    ---------------------------------------------------------

    Compare nums[mid] with nums[n-1]

    If:

        nums[mid] <= nums[n-1]

    then:
        minimum may lie at mid
        move left.

    Else:
        minimum lies right side.

    ---------------------------------------------------------
    Time Complexity
    ---------------------------------------------------------

    Average:
        O(log n)

    Worst case with duplicates:
        O(n)

    ---------------------------------------------------------
    Space Complexity
    ---------------------------------------------------------

    O(1)

*/

#include<bits/stdc++.h> 
using namespace std;    

class Solution {
public:

    int findMin(vector<int>& nums) {

        int n = nums.size();

        /*
            Already sorted
        */
        if (nums[0] < nums[n - 1]) {

            return nums[0];
        }

        int l = 0;
        int r = n - 1;

        /*
            Remove duplicate ambiguity

            Example:
            [2,2,2,0,1,2]
        */
        while (l < r &&
               nums[l] == nums[r]) {

            l++;
        }

        int ans = 6000;

        /*
            Binary Search
        */
        while (l <= r) {

            int m = l + (r - l) / 2;

            /*
                Mid belongs to right sorted part
            */
            if (nums[m] <= nums[n - 1]) {

                ans = min(ans, nums[m]);

                r = m - 1;
            }

            /*
                Mid belongs to left larger part
            */
            else {

                l = m + 1;
            }
        }

        return ans;
    }
};

/*

=========================================================
Example 1
=========================================================

nums = [4,5,6,7,0,1,2]

mid eventually reaches right sorted half.

Minimum found = 0

=========================================================
Example 2
=========================================================

nums = [2,2,2,0,1]

Duplicates create ambiguity.

We shrink boundary first.

Minimum = 0

=========================================================
Why Compare with nums[n-1]
=========================================================

Right sorted portion always satisfies:

    nums[mid] <= nums[n-1]

Minimum lies there.

If nums[mid] > nums[n-1]:

    we are still in left rotated portion.

=========================================================
Why Worst Case O(n)
=========================================================

Case:

    [2,2,2,2,2]

Duplicates force linear shrinking.

=========================================================
Time Complexity
=========================================================

Average:
O(log n)

Worst:
O(n)

=========================================================
Space Complexity
=========================================================

O(1)

=========================================================
Git Commit Message
=========================================================

Added binary search solution for rotated sorted array with duplicates


*/