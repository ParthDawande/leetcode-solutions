/*
========================================================
Total Waviness in a Range
Digit DP Solution

Approach: Digit DP + Peak/Valley Contribution Counting
Time Complexity: O(D * 2 * 3 * 10 * 10 * 10)
Space Complexity: O(D * 2 * 3 * 10 * 10)

where:
D = number of digits (<= 19 for long long)

--------------------------------------------------------
PROBLEM IDEA
--------------------------------------------------------

A digit contributes +1 to waviness if it is:

1. Strictly greater than both neighbors
   (Peak)

      a < b > c

or

2. Strictly smaller than both neighbors
   (Valley)

      a > b < c

We need:

    Total waviness of every number
    in range [num1, num2].

Brute force would iterate through all numbers,
which becomes too slow for large ranges.

Therefore we use Digit DP.

--------------------------------------------------------
DIGIT DP STATE
--------------------------------------------------------

helper(
    index,
    f,
    s,
    last,
    secondLast
)

index
-------
Current digit position.

f (tight flag)
--------------
0 = still matching prefix of bound

1 = already smaller than bound
    so remaining digits can be anything.

s (state)
---------
0 = no non-zero digit started yet

1 = exactly one significant digit chosen

2 = at least two significant digits chosen

last
----
Previous digit.

secondLast
----------
Digit before previous digit.

--------------------------------------------------------
KEY OBSERVATION
--------------------------------------------------------

Whenever we choose a new digit:

    secondLast -> last -> currentDigit

we can immediately determine whether
"last" becomes:

    Peak
or
    Valley

because both neighbors are now known.

Example:

    1 5 2

When 2 is chosen:

    1 < 5 > 2

Digit 5 contributes +1.

--------------------------------------------------------
countCompletions()
--------------------------------------------------------

Once a peak/valley is detected:

Current contribution is fixed.

Every possible completion of remaining digits
will keep this contribution.

Therefore instead of exploring all suffixes,
we directly count how many valid suffixes exist.

Case 1:
--------
f = 1

Already smaller than bound.

Remaining positions:

    rem

Ways:

    10^rem

Case 2:
--------
f = 0

Still tight.

Remaining suffix must stay <= bound suffix.

Count:

    suffixValue + 1

--------------------------------------------------------
TRANSITIONS
--------------------------------------------------------

STATE 0
--------

Still leading zeros.

Choose next digit:

digit == 0
    remain in state 0

digit > 0
    move to state 1

--------------------------------------------------------
STATE 1
--------

One significant digit exists.

Choose second significant digit.

Move to state 2.

--------------------------------------------------------
STATE 2
--------

We already have:

secondLast
last

Try every next digit i.

Check:

Peak:
    secondLast < last > i

Valley:
    secondLast > last < i

If found:

    add countCompletions()

Then continue DP.

--------------------------------------------------------
RANGE QUERY
--------------------------------------------------------

solve(x)
=
total waviness of all numbers
from 0 to x

Answer:

    solve(num2)
  - solve(num1 - 1)

--------------------------------------------------------
EXAMPLE
--------------------------------------------------------

Number:

121

When processing:

1 -> 2 -> 1

We detect:

1 < 2 > 1

Peak found.

Contribution = 1.

--------------------------------------------------------
COMPLEXITY
--------------------------------------------------------

States:

index      -> D
tight      -> 2
started    -> 3
last       -> 10
secondLast -> 10

Total:

O(D * 2 * 3 * 10 * 10)

Each state tries 10 digits.

Overall:

O(D * 6000)

Very fast.

Space:

O(D * 2 * 3 * 10 * 10)

--------------------------------------------------------
ADVANTAGE OVER BRUTE FORCE
--------------------------------------------------------

Brute Force:
    O(Range Size × Digits)

Digit DP:
    O(Digits)

Works even when:

num2 ≈ 10^18

========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    long long countCompletions(const string& h, int index, int f) {

        if(index >= (int)h.length()) {
            return 1LL;
        }

        // Already smaller than bound
        if(f == 1) {

            long long count = 1;

            for(int i = index; i < (int)h.length(); i++) {
                count *= 10;
            }

            return count;
        }

        // Still tight with bound
        long long value = 0;

        for(int i = index; i < (int)h.length(); i++) {
            value = value * 10 + (h[i] - '0');
        }

        return value + 1;
    }

    long long helper(
        string h,
        int index,
        int f,
        int s,
        int last,
        int secondLast,
        vector<vector<vector<vector<vector<long long>>>>>& dp
    ) {

        if(index >= (int)h.length()) {
            return 0LL;
        }

        if(dp[index][f][s][last][secondLast] != -1LL) {
            return dp[index][f][s][last][secondLast];
        }

        long long answer = 0;

        // Leading zeros state
        if(s == 0) {

            int limit = (f == 1) ? 9 : h[index] - '0';

            for(int digit = 0; digit <= limit; digit++) {

                int nextTight = f;

                if(digit < limit) {
                    nextTight = 1;
                }

                if(digit == 0) {
                    answer += helper(
                        h,
                        index + 1,
                        nextTight,
                        0,
                        digit,
                        last,
                        dp
                    );
                }
                else {
                    answer += helper(
                        h,
                        index + 1,
                        nextTight,
                        1,
                        digit,
                        last,
                        dp
                    );
                }
            }
        }

        // Exactly one significant digit
        else if(s == 1) {

            int limit = (f == 1) ? 9 : h[index] - '0';

            for(int digit = 0; digit <= limit; digit++) {

                int nextTight = f;

                if(digit < limit) {
                    nextTight = 1;
                }

                answer += helper(
                    h,
                    index + 1,
                    nextTight,
                    2,
                    digit,
                    last,
                    dp
                );
            }
        }

        // At least two digits available
        else {

            int limit = (f == 1) ? 9 : h[index] - '0';

            for(int digit = 0; digit <= limit; digit++) {

                int nextTight = f;

                if(digit < limit) {
                    nextTight = 1;
                }

                // Peak
                if(last > digit && secondLast < last) {

                    answer += countCompletions(
                        h,
                        index + 1,
                        nextTight
                    );
                }

                // Valley
                if(last < digit && secondLast > last) {

                    answer += countCompletions(
                        h,
                        index + 1,
                        nextTight
                    );
                }

                answer += helper(
                    h,
                    index + 1,
                    nextTight,
                    2,
                    digit,
                    last,
                    dp
                );
            }
        }

        return dp[index][f][s][last][secondLast] = answer;
    }

    long long solve(long long number) {

        if(number < 0) {
            return 0;
        }

        string h = to_string(number);

        if(h.length() < 3) {
            return 0;
        }

        long long answer = 0;

        vector<vector<vector<vector<vector<long long>>>>> dp(
            h.length() + 1,
            vector<vector<vector<vector<long long>>>>(
                2,
                vector<vector<vector<long long>>>(
                    3,
                    vector<vector<long long>>(
                        10,
                        vector<long long>(10, -1)
                    )
                )
            )
        );

        for(int firstDigit = 0; firstDigit <= h[0] - '0'; firstDigit++) {

            int tight1 = 0;

            if(firstDigit < h[0] - '0') {
                tight1 = 1;
            }

            int limit =
                (tight1 == 1)
                ? 9
                : h[1] - '0';

            for(int secondDigit = 0; secondDigit <= limit; secondDigit++) {

                int tight2 = tight1;

                if(tight1 == 0 && secondDigit < limit) {
                    tight2 = 1;
                }

                if(firstDigit == 0 && secondDigit == 0) {

                    answer += helper(
                        h,
                        2,
                        tight2,
                        0,
                        secondDigit,
                        firstDigit,
                        dp
                    );
                }
                else if(firstDigit == 0) {

                    answer += helper(
                        h,
                        2,
                        tight2,
                        1,
                        secondDigit,
                        firstDigit,
                        dp
                    );
                }
                else {

                    answer += helper(
                        h,
                        2,
                        tight2,
                        2,
                        secondDigit,
                        firstDigit,
                        dp
                    );
                }
            }
        }

        return answer;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};

