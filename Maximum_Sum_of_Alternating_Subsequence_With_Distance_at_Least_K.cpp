/*
    Problem: Maximum Alternating Subsequence Sum with Constraint (k distance)

    ---------------------------------------------------------
    YOUR APPROACH (DP + Segment Tree + Coordinate Range Query)

    Idea:
    - We want to build an alternating subsequence:
        dp1[i] → max sum starting at i where nums[i] is added (+)
        dp0[i] → max sum starting at i where nums[i] is subtracted (-)

    Constraint:
    - Next chosen index j must satisfy j >= i + k

    ---------------------------------------------------------
    Key Observations:

    For each index i:
    - We look at valid future indices j >= i + k
    - Depending on value comparison:
        • For dp1 (adding): choose next greater value
        • For dp0 (subtracting): choose next smaller value

    This becomes a RANGE MAX QUERY problem.

    ---------------------------------------------------------
    Why Segment Tree?

    - We need fast queries:
        max over range [v+1, V)  → for increasing transitions
        max over range [0, v]    → for decreasing transitions

    - Segment Tree supports:
        ✔ Update in O(log N)
        ✔ Query in O(log N)

    ---------------------------------------------------------
    Steps:

    1. Build segment trees:
        segUp   → stores dp0 values
        segDown → stores dp1 values

    2. Traverse from right → left:
        - Ensure future states are already computed

    3. For each i:
        - Add index j = i + k into segment tree
        - Query best possible continuation

    4. Compute:
        dp1[i] = nums[i] + best from segUp
        dp0[i] = nums[i] + best from segDown

    5. Track global maximum

    ---------------------------------------------------------
    Time Complexity: O(n log V)
    Space Complexity: O(V)

    (V = max value in nums)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> segUp, segDown;
    int M;

    // Point update (maximize value)
    void update(vector<long long>& seg, int pos, long long val) {
        for (pos += M; pos > 0; pos >>= 1) {
            seg[pos] = max(seg[pos], val);
        }
    }

    // Range max query [l, r)
    long long query(vector<long long>& seg, int l, int r) {
        long long res = 0;
        for (l += M, r += M; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, seg[l++]);
            if (r & 1) res = max(res, seg[--r]);
        }
        return res;
    }

    long long maxAlternatingSum(vector<int>& nums, int k) {
        int n = nums.size();

        int maxi = *max_element(nums.begin(), nums.end());
        int V = maxi + 1;

        // Build segment tree size (power of 2)
        M = 1;
        while (M < V) M <<= 1;

        segUp.assign(2 * M, 0);
        segDown.assign(2 * M, 0);

        vector<long long> dp0(n, 0), dp1(n, 0);
        long long ans = 0;

        // Traverse from right to left
        for (int i = n - 1; i >= 0; i--) {

            int j = i + k;

            // Add future index into segment tree
            if (j < n) {
                update(segUp, nums[j], dp0[j]);
                update(segDown, nums[j], dp1[j]);
            }

            int v = nums[i];

            // Query best transitions
            long long best1 = query(segUp, v + 1, V); // greater values
            long long best2 = query(segDown, 0, v);   // smaller values

            // Compute DP
            dp1[i] = v + best1;
            dp0[i] = v + best2;

            ans = max({ans, dp1[i], dp0[i]});
        }

        return ans;
    }
};

/*
---------------------------------------------------------
Intuition Summary:

- Convert problem into DP with transitions based on value comparison
- Use segment tree to optimize "find best future" queries
- Traverse backward to ensure valid states

---------------------------------------------------------
Pros:
✔ Handles constraints efficiently
✔ Optimized using segment tree
✔ Works in O(n log V)

Cons:
✖ Higher space due to segment tree
✖ Requires understanding of range queries

---------------------------------------------------------
*/