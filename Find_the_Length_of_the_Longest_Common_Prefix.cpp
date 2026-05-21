/*
========================================================
Longest Common Prefix Between Two Arrays
========================================================

Problem:
--------
Given two integer arrays arr1 and arr2.

A prefix of a number means removing digits
from the end.

Example:
12345 prefixes:
12345
1234
123
12
1

We need to find the maximum length
of a common numeric prefix between
any number in arr1 and any number in arr2.

--------------------------------------------------------
Example
--------------------------------------------------------

Input:
arr1 = [123, 456]
arr2 = [12, 789]

Prefixes of 123:
123
12
1

Since 12 exists as a prefix of a number in arr2,
the answer is:

Length of "12" = 2

--------------------------------------------------------
Approach — Store All Prefixes
--------------------------------------------------------

We store every possible prefix from arr1.

Example:

1234 generates:
1234
123
12
1

We insert them into a hashmap.

--------------------------------------------------------
Then Process arr2
--------------------------------------------------------

For every number in arr2:

Keep removing last digit:

Example:
1299

1299
129
12
1

As soon as we find a prefix present
in hashmap, we update answer.

--------------------------------------------------------
Key Optimization
--------------------------------------------------------

while(num > 0 && maxi < num)

If current number already has fewer digits
than current best prefix,
we stop early.

--------------------------------------------------------
Time Complexity
--------------------------------------------------------

Each number has at most 10 digits.

So:

Time:
O((n + m) * 10)

Space:
O(total prefixes)

--------------------------------------------------------
Dry Run
--------------------------------------------------------

arr1 = [1234]

Stored prefixes:
1234
123
12
1

--------------------------------

arr2 = [1299]

Check:
1299 -> not found
129  -> not found
12   -> found

Longest prefix = 12
Length = 2

--------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int longestCommonPrefix(vector<int>& arr1,
                            vector<int>& arr2) {

        /*
        Store all prefixes from arr1
        */
        unordered_map<int,int> mp;

        //------------------------------------------------
        // Generate prefixes from arr1
        //------------------------------------------------
        for(int i = 0; i < arr1.size(); i++) {

            int num = arr1[i];

            while(num > 0) {

                /*
                Avoid duplicate work
                */
                if(mp.find(num) != mp.end()) {
                    break;
                }

                mp[num]++;

                /*
                Remove last digit
                */
                num = num / 10;
            }
        }

        //------------------------------------------------
        // Find longest matching prefix in arr2
        //------------------------------------------------
        int maxi = 0;

        for(int i = 0; i < arr2.size(); i++) {

            int num = arr2[i];

            /*
            Keep shortening number
            until prefix found
            */
            while(num > 0 && maxi < num) {

                if(mp.find(num) != mp.end()) {

                    maxi = max(maxi, num);

                    break;
                }

                num = num / 10;
            }
        }

        //------------------------------------------------
        // Count digits in maximum prefix
        //------------------------------------------------
        int len = 0;

        while(maxi > 0) {

            len++;

            maxi = maxi / 10;
        }

        return len;
    }
};
