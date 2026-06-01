/*
========================================================
42. Trapping Rain Water
LeetCode Hard

Approach: Two Pointers
Time Complexity: O(n)
Space Complexity: O(1)

--------------------------------------------------------
IDEA
--------------------------------------------------------

For every index i:

water[i] =
min(max height on left,
    max height on right)
- height[i]

A brute force solution computes left and right maxima
for every index separately, leading to O(n²).

We can optimize to O(n) using two pointers.

--------------------------------------------------------
OBSERVATION
--------------------------------------------------------

Maintain:

left      -> start pointer
right     -> end pointer

maxleft   -> maximum height seen from left side
maxright  -> maximum height seen from right side

At any moment:

If height[left] <= height[right]

then the right side is guaranteed to have a wall at least
as high as height[left].

Therefore the trapped water at left depends only on maxleft.

Similarly,

If height[right] < height[left]

then trapped water at right depends only on maxright.

--------------------------------------------------------
ALGORITHM
--------------------------------------------------------

1. Initialize:
   left = 0
   right = n - 1

2. Maintain:
   maxleft
   maxright

3. If height[left] <= height[right]:

      if height[left] >= maxleft
            update maxleft
      else
            add maxleft - height[left]

      left++

4. Otherwise:

      if height[right] >= maxright
            update maxright
      else
            add maxright - height[right]

      right--

5. Continue until pointers cross.

--------------------------------------------------------
EXAMPLE
--------------------------------------------------------

height = [4,2,0,3,2,5]

left=0 right=5

maxleft=4
maxright=5

Water trapped:

index 1 -> 2
index 2 -> 4
index 3 -> 1
index 4 -> 2

Total = 9

--------------------------------------------------------
WHY IT WORKS
--------------------------------------------------------

When height[left] <= height[right]:

A valid right boundary already exists.

Thus water level at left is determined completely by
maxleft.

Similarly for the right side.

This allows processing one side at a time without
precomputing prefix/suffix maximum arrays.

--------------------------------------------------------
CODE
--------------------------------------------------------
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();

        int left = 0;
        int right = n - 1;

        int maxleft = 0;
        int maxright = 0;

        int area = 0;

        while (left <= right) {

            if (height[left] <= height[right]) {

                if (maxleft <= height[left]) {
                    maxleft = height[left];
                } else {
                    area += maxleft - height[left];
                }

                left++;
            }
            else {

                if (maxright <= height[right]) {
                    maxright = height[right];
                } else {
                    area += maxright - height[right];
                }

                right--;
            }
        }

        return area;
    }
};

