/*
========================================================
Total Waviness in a Range
LeetCode Style Problem

Approach: Brute Force Simulation
Time Complexity: O((num2 - num1 + 1) * D)
Space Complexity: O(D)

where:
D = number of digits in the number

--------------------------------------------------------
DEFINITION OF WAVINESS
--------------------------------------------------------

For a number:

A digit is considered "wavy" if it is either:

1. Strictly greater than both neighboring digits
   (local maximum)

or

2. Strictly smaller than both neighboring digits
   (local minimum)

Only middle digits can contribute because the first
and last digit do not have two neighbors.

--------------------------------------------------------
EXAMPLE
--------------------------------------------------------

Number = 121

Digit '2':

2 > 1 and 2 > 1

=> Local maximum

Waviness = 1

--------------------------------------------------------

Number = 212

Digit '1':

1 < 2 and 1 < 2

=> Local minimum

Waviness = 1

--------------------------------------------------------

Number = 12121

Digits:

2 > 1 and 2 > 1  -> +1
1 < 2 and 1 < 2  -> +1
2 > 1 and 2 > 1  -> +1

Total waviness = 3

--------------------------------------------------------
FUNCTION solve(n)
--------------------------------------------------------

1. Convert number into string.

2. If number contains fewer than 3 digits:
      return 0

3. For every middle digit:

      if digit > left and digit > right
            count++

      if digit < left and digit < right
            count++

4. Return count.

--------------------------------------------------------
FUNCTION totalWaviness(num1, num2)
--------------------------------------------------------

For every number in the range:

      total += solve(number)

Return total.

--------------------------------------------------------
EXAMPLE
--------------------------------------------------------

num1 = 120
num2 = 123

120 -> 1
121 -> 1
122 -> 0
123 -> 0

Answer = 2

--------------------------------------------------------
COMPLEXITY ANALYSIS
--------------------------------------------------------

Let:

R = num2 - num1 + 1
D = maximum digits

For each number:
    O(D)

Total:
    O(R × D)

Space:
    O(D)

--------------------------------------------------------
NOTE
--------------------------------------------------------

This brute-force solution is straightforward and works
well for small ranges.

For very large ranges (up to 10^9 or higher), a
Digit-DP solution would be required to count waviness
without iterating through every number.
========================================================
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int solve(int n) {
        string h = to_string(n);

        if (h.length() < 3) {
            return 0;
        }

        int cnt = 0;

        for (int i = 1; i < h.length() - 1; i++) {

            // Local maximum
            if (h[i] > h[i - 1] && h[i] > h[i + 1]) {
                cnt++;
            }

            // Local minimum
            if (h[i] < h[i - 1] && h[i] < h[i + 1]) {
                cnt++;
            }
        }

        return cnt;
    }

    int totalWaviness(int num1, int num2) {
        int total = 0;

        for (int i = num1; i <= num2; i++) {
            total += solve(i);
        }

        return total;
    }
};

