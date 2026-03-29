#include <bits/stdc++.h>
using namespace std;

/*
Problem: Count Sortable Integers Based on Rotated Non-Decreasing Segments

Approach:
1. For every divisor 'len' of n:
    - Split array into segments of size 'len'
    - For each segment:
        a) Check if it is a rotated non-decreasing array
        b) If not → reject this length

2. While processing segments:
    - Track previous segment's maximum
    - Ensure current segment's minimum ≥ previous maximum
    - Otherwise → not globally sortable

3. If all segments satisfy conditions → add 'len' to answer

Helper Function:
- minMaxIfRotatedNonDecreasing():
    - Checks if subarray is rotated sorted
    - Returns {min, max} if valid
    - Else returns {-1, -1}

Time Complexity:
O(n * number_of_divisors)

Space Complexity:
O(1)

Concepts Used:
- Divisors
- Rotated Sorted Array Check
- Greedy Validation
*/

class Solution {
public:

    vector<int> minMaxIfRotatedNonDecreasing(vector<int>& arr, int l, int r) {
        if (l == r) {
            return {arr[l], arr[l]};
        }

        int count = 0;

        // Count violations (where order breaks)
        for (int i = l; i < r; i++) {
            if (arr[i] > arr[i + 1]) {
                count++;
            }
        }

        // Circular condition
        if (arr[r] > arr[l]) {
            count++;
        }

        // More than 1 violation → not valid rotated sorted
        if (count > 1) return {-1, -1};

        // Find min and max
        int mn = arr[l], mx = arr[l];
        for (int i = l + 1; i <= r; i++) {
            mn = min(mn, arr[i]);
            mx = max(mx, arr[i]);
        }

        return {mn, mx};
    }

    int sortableIntegers(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();

        vector<int> divisors;

        // Find all divisors of n
        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                divisors.push_back(i);
            }
        }

        // Try each segment length
        for (int i = 0; i < divisors.size(); i++) {
            int len = divisors[i];

            int prev = -1;
            int flag = 0;

            // Process segments of size len
            for (int j = 0; j < n; j += len) {

                vector<int> temp = minMaxIfRotatedNonDecreasing(nums, j, j + len - 1);

                // Invalid segment
                if (temp[0] == -1 && temp[1] == -1) {
                    flag = 1;
                    break;
                }

                // Order violation between segments
                if (temp[0] < prev) {
                    flag = 1;
                    break;
                } else {
                    prev = temp[1];
                }
            }

            // Valid length
            if (flag == 0) {
                ans += len;
            }
        }

        return ans;
    }
};