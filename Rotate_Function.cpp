/*
    Problem: Rotate Function (LeetCode 396)

    Given an array nums of size n, define:
    F(k) = sum of i * nums[(i + k) % n] for i = 0 to n-1

    Goal: Find maximum value of F(k) for all rotations.

    ---------------------------------------------------------
    YOUR APPROACH (Prefix Sum + Circular Array Simulation)

    Idea:
    - Instead of using the mathematical recurrence, we simulate rotations.
    - Create an extended array to handle circular behavior.
    - Use prefix sum to quickly compute range sums.
    - Update rotation value efficiently using previous value.

    ---------------------------------------------------------
    Steps:

    1. Create extended array:
       - Copy nums[1...n-1] first
       - Then append full nums
       → Helps simulate rotations easily

    2. Compute F(0):
       curr = sum(i * nums[i])

    3. Build prefix sum array:
       → prefix[i] = sum of elements from 0 to i

    4. Iterate rotations backwards:
       For each rotation:
       - Remove contribution of last element
       - Add contribution of shifted elements using prefix sum

    ---------------------------------------------------------
    Time Complexity: O(n)
    Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;

        vector<int> arr;
        vector<int> prefix;

        // Step 1: Build partial extended array (nums[1...n-1])
        for (int i = 1; i < n; i++) {
            arr.push_back(nums[i]);
            prefix.push_back(nums[i]);
        }

        int curr = 0;

        // Step 2: Compute F(0) and complete extended array
        for (int i = 0; i < n; i++) {
            arr.push_back(nums[i]);
            prefix.push_back(nums[i]);
            curr += i * nums[i];
        }

        // Step 3: Build prefix sum
        for (int i = 1; i < prefix.size(); i++) {
            prefix[i] += prefix[i - 1];
        }

        int maxi = INT_MIN;

        // Step 4: Process all rotations
        int i = n - 1;
        while (i >= 0) {
            maxi = max(maxi, curr);

            // Remove contribution of element moving from end to front
            curr -= (n - 1) * arr[i + n - 1];

            // Add contribution of shifted elements
            int sum = prefix[i + n - 2];
            if (i - 1 >= 0) {
                sum -= prefix[i - 1];
            }

            curr += sum;
            i--;
        }

        return maxi;
    }
};

/*
---------------------------------------------------------
Intuition Behind Update:

When rotating:
- One element moves from end → front
- Remaining elements shift right → their index increases by 1

So:
- Remove (n-1) * last_element
- Add sum of remaining elements

Prefix sum helps compute range sum in O(1)

---------------------------------------------------------
Pros:
✔ Efficient O(n) time
✔ Uses prefix sum for fast updates

Cons:
✖ Extra space O(n)
✖ More complex than optimal recurrence solution

---------------------------------------------------------
*/