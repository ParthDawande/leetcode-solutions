#include <bits/stdc++.h>
using namespace std;

/*
Problem: Minimum Number of Seconds to Complete Mountain

Approach:
- Binary search on time (answer)
- For a given time limit, calculate how much height can be reduced
- Each worker removes height in increasing time:
    t, 2t, 3t, ..., kt → total time = t * (k*(k+1)/2)

- Using quadratic formula, find maximum k such that:
    t * (k*(k+1)/2) <= limit

- Sum all k values for workers
- If total >= mountainHeight → feasible

Time Complexity:
O(n * log(maxTime))

Space Complexity:
O(1)

Concepts Used:
- Binary Search on Answer
- Math (Quadratic Equation)
- Greedy accumulation
*/

class Solution {
public:

    // Check if we can reduce mountainHeight within 'limit' time
    bool check(int mountainHeight, long long limit, vector<int>& workerTimes) {
        long long total = 0;

        for (int i = 0; i < workerTimes.size(); i++) {

            // Solve: t * (k*(k+1)/2) <= limit
            // k ≈ sqrt(2*limit/t + 0.25) - 0.5

            long long k = max(0.0, floor(sqrt(2.0 * limit / workerTimes[i] + 0.25) - 0.5));

            total += k;
        }

        return total >= mountainHeight;
    }

    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {

        int maxi = 0;
        for (int i = 0; i < workerTimes.size(); i++) {
            maxi = max(maxi, workerTimes[i]);
        }

        long long l = 1;
        long long r = 1LL * maxi * mountainHeight * (mountainHeight + 1) / 2;

        long long ans = -1;

        // Binary search on time
        while (l <= r) {
            long long mid = l + (r - l) / 2;

            if (check(mountainHeight, mid, workerTimes)) {
                ans = mid;
                r = mid - 1; // try smaller time
            } else {
                l = mid + 1;
            }
        }

        return ans;
    }
};