/*
========================================================
Search in Rotated Sorted Array
========================================================

Problem:
Given a rotated sorted array nums and a target value,
return the index of target if it exists, otherwise return -1.

--------------------------------------------------------
Approach Used
--------------------------------------------------------

This solution uses TWO Binary Searches:

1. Find the Peak (Largest Element)
2. Decide which sorted half contains target
3. Apply Binary Search on that half

--------------------------------------------------------
Key Observation
--------------------------------------------------------

A rotated sorted array consists of TWO sorted parts.

Example:
nums = [4,5,6,7,0,1,2]

Peak = 7 at index 3

Left Half  = [4,5,6,7]
Right Half = [0,1,2]

If target >= nums[0],
target must lie in LEFT half.

Else,
target lies in RIGHT half.

--------------------------------------------------------
Step 1: Find Peak
--------------------------------------------------------

We binary search for the last element >= nums[0].

Example:
[4,5,6,7,0,1,2]

Peak index = 3

Time Complexity:
O(log n)

--------------------------------------------------------
Step 2: Choose Correct Half
--------------------------------------------------------

If target >= nums[0]:
Search in [0 ... peak]

Else:
Search in [peak+1 ... n-1]

--------------------------------------------------------
Step 3: Binary Search
--------------------------------------------------------

Perform standard binary search
on the selected sorted half.

--------------------------------------------------------
Complexity
--------------------------------------------------------

Time Complexity:
O(log n)

Space Complexity:
O(1)

--------------------------------------------------------
Dry Run
--------------------------------------------------------

nums = [4,5,6,7,0,1,2]
target = 0

Peak = 3

0 < nums[0]
=> Search right half [4..6]

Binary Search:
mid -> found 0 at index 4

Answer = 4

========================================================
Code
========================================================
*/
#include <bits/stdc++.h>
using namespace std;    

class Solution {
public:
    int search(vector<int>& nums, int target) {

        // Step 1:
        // Find peak index (largest element)

        int peak = -1;

        int l = 0;
        int r = nums.size() - 1;

        while(l <= r) {

            int m = l + (r - l) / 2;

            // Still in left sorted portion
            if(nums[m] >= nums[0]) {

                peak = m;
                l = m + 1;
            }
            else {

                r = m - 1;
            }
        }

        // Step 2:
        // Decide which half to search

        if(target >= nums[0]) {

            // Search LEFT sorted half

            int l1 = 0;
            int r1 = peak;

            while(l1 <= r1) {

                int m = l1 + (r1 - l1) / 2;

                if(nums[m] == target) {
                    return m;
                }
                else if(nums[m] < target) {
                    l1 = m + 1;
                }
                else {
                    r1 = m - 1;
                }
            }
        }
        else {

            // Search RIGHT sorted half

            int l1 = peak + 1;
            int r1 = nums.size() - 1;

            while(l1 <= r1) {

                int m = l1 + (r1 - l1) / 2;

                if(nums[m] == target) {
                    return m;
                }
                else if(nums[m] < target) {
                    l1 = m + 1;
                }
                else {
                    r1 = m - 1;
                }
            }
        }

        return -1;
    }
};

