#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem: Maximum Distance Between Valid Pairs
===========================================================

Given:
- Two NON-INCREASING arrays nums1 and nums2

Find:
Maximum (j - i) such that:
    i <= j AND nums1[i] <= nums2[j]

-----------------------------------------------------------
Key Observation:
Both arrays are sorted in descending order

-----------------------------------------------------------
APPROACH 1: Binary Search (O(n log n))
-----------------------------------------------------------

Idea:
For each index i in nums1:
    → Find the farthest j in nums2 such that nums2[j] >= nums1[i]

We use:
    upper_bound(nums2.begin(), nums2.end(), x, greater<int>())

Why?
- Since nums2 is descending:
  upper_bound gives first element < x

So:
    valid range = [0 ... index-1]
    j = index - 1

Check:
    if j >= i → valid pair

Time Complexity: O(n log n)

-----------------------------------------------------------
APPROACH 2: Two Pointer (Optimal O(n))
-----------------------------------------------------------

Idea:
Use two pointers i and j

- If nums1[i] <= nums2[j]:
      → valid pair → update answer
      → move j forward (try larger distance)

- Else:
      → move i forward (need smaller nums1[i])

Why it works:
- Arrays are monotonic
- Each pointer moves only forward → O(n)

Time Complexity: O(n)

-----------------------------------------------------------
FINAL NOTE:
Two Pointer is optimal and preferred in interviews
===========================================================
*/


// =======================================================
// APPROACH 1: Binary Search
// =======================================================
class Solution_BinarySearch {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int maxi = 0;
        int n = nums1.size();

        for(int i = 0; i < n; i++) {
            int x = nums1[i];

            // Find first element < x in descending array
            int index = upper_bound(nums2.begin(), nums2.end(), x, greater<int>()) - nums2.begin();

            // Last valid index = index - 1
            if(index >= i) {
                maxi = max(maxi, index - i - 1);
            }
        }
        return maxi;
    }
};


// =======================================================
// APPROACH 2: Two Pointer (Optimal)
// =======================================================
class Solution_TwoPointer {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int i = 0, j = 0;
        int maxi = 0;

        while(i < nums1.size() && j < nums2.size()) {

            if(nums1[i] <= nums2[j]) {
                // Valid pair
                maxi = max(maxi, j - i);
                j++;  // try to extend distance
            } else {
                i++;  // need smaller nums1[i]
            }
        }

        return maxi;
    }
};


/*
===========================================================
Example:

nums1 = [5,4]
nums2 = [7,6,5,4]

Binary Search:
i=0 → x=5 → j=2 → distance=2
i=1 → x=4 → j=3 → distance=2

Two Pointer:
i=0,j=0 → valid → j++
i=0,j=1 → valid → j++
i=0,j=2 → valid → j++
→ best distance = 2

===========================================================
*/