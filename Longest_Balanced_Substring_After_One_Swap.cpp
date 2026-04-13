#include <bits/stdc++.h>
using namespace std;

/*
Problem: Longest Balanced Substring (Extended Condition)
Platform: LeetCode

Approach:
- Convert string into prefix difference:
    diff = (#0 - #1)

- Use hashmap to store first occurrence of each diff

- For each index:
    Case 1:
        diff repeats → equal number of 0 and 1

    Case 2:
        diff differs by ±2:
        → allows imbalance but must satisfy global constraint

- Also check reversed string to cover both directions

Steps:
1. Count total 0s and 1s
2. Traverse string:
    - Maintain prefix diff
    - Check:
        diff
        diff-2
        diff+2
3. Update maximum length
4. Repeat for reversed string

Time Complexity:
O(n)

Space Complexity:
O(n)

Concepts Used:
- Prefix sum
- Hashmap
- Sliding logic
*/

class Solution {
public:

    int solve(string s) {

        int f0 = 0, f1 = 0;

        // Count total zeros and ones
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '0') f0++;
            else f1++;
        }

        int cnt0 = 0, cnt1 = 0;

        unordered_map<int, int> mp;

        // Base case
        mp[0] = -1;

        int maxi = 0;

        for (int i = 0; i < s.length(); i++) {

            if (s[i] == '0') cnt0++;
            else cnt1++;

            int diff = cnt0 - cnt1;

            // Case 1: equal 0 and 1
            if (mp.find(diff) != mp.end()) {
                maxi = max(maxi, i - mp[diff]);
            }

            // Case 2: diff - 2
            if (mp.find(diff - 2) != mp.end()) {
                int len = i - mp[diff - 2];

                if (f1 >= len / 2) {
                    maxi = max(maxi, len);
                }
            }

            // Case 3: diff + 2
            if (mp.find(diff + 2) != mp.end()) {
                int len = i - mp[diff + 2];

                if (f0 >= len / 2) {
                    maxi = max(maxi, len);
                }
            }

            // Store first occurrence
            if (mp.find(diff) == mp.end()) {
                mp[diff] = i;
            }
        }

        return maxi;
    }

    int longestBalanced(string s) {

        int maxi = 0;

        // Original
        maxi = max(maxi, solve(s));

        // Reverse to handle symmetry
        reverse(s.begin(), s.end());

        maxi = max(maxi, solve(s));

        return maxi;
    }
};