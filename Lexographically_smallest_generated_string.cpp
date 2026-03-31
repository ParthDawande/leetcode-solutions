#include <bits/stdc++.h>
using namespace std;

/*
Problem: Generate String Based on Constraints
Platform: LeetCode

Approach:
- We are given:
    str1 → constraints ('T' or 'F')
    str2 → pattern string

- Goal:
    Construct a string such that:
    - If str1[i] == 'T':
        substring starting at i must exactly match str2
    - If str1[i] == 'F':
        substring starting at i must NOT match str2

Steps:
1. Initialize result array with 'a'
2. Maintain a 'fixed' array to track forced assignments

3. Handle 'T' constraints:
    - Force substring = str2
    - If conflict occurs → return ""

4. Handle 'F' constraints:
    - Check if substring currently equals str2
    - If yes:
        - Try modifying one unfixed position
        - If not possible → return ""

5. Build final string and return

Time Complexity: O(n * m)
Space Complexity: O(n + m)

Concepts Used:
- String Construction
- Greedy Assignment
- Constraint Satisfaction
*/

class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.length();
        int m = str2.length();

        vector<char> arr(n + m - 1, 'a');
        vector<int> fixed(n + m - 1, 0);

        // Step 1: Handle 'T' constraints
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = i; j < i + m; j++) {
                    if (fixed[j] && arr[j] != str2[j - i]) {
                        return "";
                    } else {
                        arr[j] = str2[j - i];
                        fixed[j] = 1;
                    }
                }
            }
        }

        // Step 2: Handle 'F' constraints
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'F') {

                int match = 1;
                int changeIndex = -1;

                for (int j = i + m - 1; j >= i; j--) {

                    // Check mismatch
                    if (arr[j] != str2[j - i]) {
                        match = 0;
                    }

                    // Find a position we can modify
                    if (changeIndex == -1 && !fixed[j]) {
                        changeIndex = j;
                    }
                }

                // If already not matching → OK
                if (match == 0) {
                    continue;
                }

                // Try to break match
                else if (changeIndex != -1) {
                    arr[changeIndex] = 'b';
                }

                // No way to break match
                else {
                    return "";
                }
            }
        }

        // Step 3: Build result string
        string ans = "";
        for (char c : arr) {
            ans += c;
        }

        return ans;
    }
};