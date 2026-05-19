/*
========================================================
Count Numbers Having Integer K-th Root in Range [l, r]
========================================================

Problem:
--------
Given:
- l
- r
- k

Count how many integers x exist such that:

    l <= x^k <= r

In other words,
count all perfect k-th powers inside [l, r].

--------------------------------------------------------
Example
--------------------------------------------------------

Input:
l = 1
r = 27
k = 3

Perfect cubes:
1  = 1^3
8  = 2^3
27 = 3^3

Answer = 3

--------------------------------------------------------
Approach — Binary Search
--------------------------------------------------------

We need to find:

1. Smallest integer x such that:
        x^k >= l

2. Largest integer x such that:
        x^k <= r

Then answer becomes:

    rightIndex - leftIndex + 1

--------------------------------------------------------
Why Binary Search Works
--------------------------------------------------------

The function:

    f(x) = x^k

is monotonic increasing.

So we can binary search on x.

--------------------------------------------------------
Two Binary Searches
--------------------------------------------------------

Case 1:
--------
Find first x where:

    x^k >= target

(lower bound)

--------------------------------------------------------

Case 2:
--------
Find last x where:

    x^k <= target

(upper bound)

--------------------------------------------------------
Time Complexity
--------------------------------------------------------

Binary search range:
0 → 1e9

Each search:
O(log(1e9))

Total:
O(log(1e9))

--------------------------------------------------------
Important Note
--------------------------------------------------------

Using:

    pow(m, k)

may cause floating-point precision issues
for very large values.

For competitive programming constraints,
this often works.

For safer implementation,
integer fast exponentiation can be used.

--------------------------------------------------------
Dry Run
--------------------------------------------------------

l = 10
r = 100
k = 2

Find smallest x:
x² >= 10

x = 4

Find largest x:
x² <= 100

x = 10

Answer:
10 - 4 + 1 = 7

Numbers:
16,25,36,49,64,81,100

--------------------------------------------------------
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ----------------------------------------------------
    solve(end, k, f)

    f == 0:
        Find smallest x such that:
            x^k >= end

    f == 1:
        Find largest x such that:
            x^k <= end
    ----------------------------------------------------
    */
    int solve(int end, int k, int f){

        // Lower Bound Search
        if(f == 0){

            int ans = -1;

            int l = 0;
            int r = 1e9;

            while(l <= r){

                int m = l + (r - l) / 2;

                if(pow(m, k) >= end){

                    ans = m;

                    r = m - 1;
                }
                else{
                    l = m + 1;
                }
            }

            return ans;
        }

        // Upper Bound Search
        else{

            int ans = -1;

            int l = 0;
            int r = 1e9;

            while(l <= r){

                int m = l + (r - l) / 2;

                if(pow(m, k) <= end){

                    ans = m;

                    l = m + 1;
                }
                else{
                    r = m - 1;
                }
            }

            return ans;
        }
    }

    int countKthRoots(int l, int r, int k) {

        /*
        First integer whose k-th power
        is >= l
        */
        int lIndex = solve(l, k, 0);

        /*
        Last integer whose k-th power
        is <= r
        */
        int rIndex = solve(r, k, 1);

        /*
        Total count
        */
        return max(0, rIndex - lIndex + 1);
    }
};

