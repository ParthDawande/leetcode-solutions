#include <bits/stdc++.h>
using namespace std;

/*
Problem: XOR After Queries
Platform: LeetCode

Approach:
- Convert nums into long long array for safe multiplication
- For each query [l, r, k, v]:
    - Start from index l
    - Update every k-th element until r:
        arr[j] = (arr[j] * v) % MOD

- After processing all queries:
    - Compute XOR of all elements

Time Complexity:
O(sum of ((r-l)/k)) → worst O(n * q)

Space Complexity:
O(n)

Concepts Used:
- Simulation
- Modular arithmetic
- XOR operation
*/

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {

        vector<long long> arr;

        // Step 1: Copy to long long
        for (int i = 0; i < nums.size(); i++) {
            arr.push_back(1LL * nums[i]);
        }

        // Step 2: Process queries
        for (int i = 0; i < queries.size(); i++) {

            long long l = queries[i][0];
            long long r = queries[i][1];
            long long k = queries[i][2];
            long long v = queries[i][3];

            long long j = l;

            while (j <= r) {
                arr[j] = (arr[j] * v) % 1000000007;
                j += k;
            }
        }

        // Step 3: Compute XOR
        long long ans = 0;

        for (int i = 0; i < arr.size(); i++) {
            ans = (ans ^ arr[i]);
        }

        return (int)ans;
    }
};