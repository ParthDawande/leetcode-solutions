/*
===========================================================
Problem: Maximum Value for Each Partition
===========================================================

Goal:
-----
For every index, determine the maximum value inside the
smallest valid partition/subarray it belongs to.

-----------------------------------------------------------
Key Observation:
-----------------------------------------------------------

We process the array from RIGHT to LEFT.

For every position:
- Expand left while previous prefix maximum is greater
  than current minimum.

Why?
- If a previous element is larger than the minimum inside
  current segment, then they belong to the same partition.

-----------------------------------------------------------
Prefix Maximum:
-----------------------------------------------------------

prefixMax[i] =
    maximum element from nums[0...i]

Used to quickly determine whether we must expand left.

-----------------------------------------------------------
Approach:
-----------------------------------------------------------

Step 1:
Build prefix maximum array.

Step 2:
Start from rightmost index.

Step 3:
Expand current segment leftward while:
    prefixMax[j-1] > current_minimum

Step 4:
Track maximum value inside this segment.

Step 5:
Assign this maximum to all indices of segment.

-----------------------------------------------------------
Why this works:
-----------------------------------------------------------

If some previous value is greater than the minimum of
current segment, then sorting/partition constraints force
them to belong together.

So we greedily merge them.

-----------------------------------------------------------
Time Complexity:
-----------------------------------------------------------
Worst Case:
    O(n²)

(Inner expansion may revisit elements)

-----------------------------------------------------------
Space Complexity:
-----------------------------------------------------------
O(n)

-----------------------------------------------------------
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {

        int n = nums.size();

        // prefixMax[i] = maximum value from 0...i
        vector<int> prefixMax(n, -1);

        for(int i = 0; i < nums.size(); i++) {
            prefixMax[i] = nums[i];
        }

        for(int i = 1; i < nums.size(); i++) {
            prefixMax[i] = max(prefixMax[i], prefixMax[i - 1]);
        }

        vector<int> ans(n, -1);

        int i = n - 1;

        // Process from right to left
        while(i >= 0) {

            int j = i;

            int maxi = 0;
            int mini = nums[j];

            // Expand segment leftward
            while(j > 0 && prefixMax[j - 1] > mini) {

                maxi = max(maxi, nums[j]);

                j--;

                mini = min(mini, nums[j]);
            }

            maxi = max(maxi, nums[j]);

            // Assign segment maximum to all positions
            for(int k = j; k <= i; k++) {
                ans[k] = maxi;
            }

            // Move to next segment
            i = j - 1;
        }

        return ans;
    }
};