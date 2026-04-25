/*
===========================================================
📌 Problem: Maximize Distance on Square Boundary
===========================================================

🧠 Idea:
We are given points lying on the boundary of a square of side = `side`.

We need to pick `k` points such that:
👉 Minimum distance between consecutive chosen points (circularly) is maximized.

-----------------------------------------------------------
🚀 Approach: Linearization + Binary Search + Greedy
-----------------------------------------------------------

1️⃣ Convert 2D boundary points → 1D representation

We map the square boundary into a line of length = 4 * side:

    Left edge   (x=0)       →  y
    Top edge    (y=side)    →  side + x
    Right edge  (x=side)    →  3*side - y
    Bottom edge (y=0)       →  4*side - x

👉 This converts circular boundary into linear array.

-----------------------------------------------------------
2️⃣ Sort the array

Now problem becomes:
👉 Pick k points such that min gap ≥ limit

-----------------------------------------------------------
3️⃣ Binary Search on Answer

Search range:
    l = 1
    r = side

For each mid = possible minimum distance:
    Check if we can pick k points

-----------------------------------------------------------
4️⃣ Greedy Check

For each starting point:
    - Keep selecting next valid point using lower_bound
    - Ensure spacing ≥ limit
    - Ensure we don’t exceed circular boundary

If we can pick k points → valid

-----------------------------------------------------------
⏱ Complexity:
Time:  O(n log n + n * k * log n)
Space: O(n)

-----------------------------------------------------------
📌 Key Insight:
Convert circular geometry into linear + use binary search on answer.
-----------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Check if we can pick k points with minimum distance = limit
    bool check(vector<long long>& arr, int limit, int k, int side) {

        for (int i = 0; i < arr.size(); i++) {
            long long start = arr[i];

            // Circular boundary limit
            long long end = 4LL * side + start - limit;

            long long curr = start;
            int f = 1;

            for (int j = 0; j < k - 1; j++) {
                long long target = curr + limit;

                int index = lower_bound(arr.begin(), arr.end(), target) - arr.begin();

                if (index < arr.size() && arr[index] <= end) {
                    curr = arr[index];
                } else {
                    f = 0;
                    break;
                }
            }

            if (f == 1) {
                return true;
            }
        }
        return false;
    }

    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<long long> arr;

        // Convert 2D boundary points to 1D
        for (int i = 0; i < points.size(); i++) {
            int x = points[i][0];
            int y = points[i][1];

            if (x == 0) {
                arr.push_back(1LL * y);
            } 
            else if (y == side) {
                arr.push_back(1LL * side + x);
            } 
            else if (x == side) {
                arr.push_back(3LL * side - y);
            } 
            else {
                arr.push_back(4LL * side - x);
            }
        }

        sort(arr.begin(), arr.end());

        long long l = 1;
        long long r = side;
        long long ans = 0;

        // Binary search on answer
        while (l <= r) {
            long long mid = l + (r - l) / 2;

            if (check(arr, mid, k, side)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return (int)ans;
    }
};