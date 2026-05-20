/*
========================================================
Find the Prefix Common Array of Two Arrays
========================================================

Problem:
--------
Given two arrays A and B of equal size n.

For every index i:

Find how many numbers are common in:

    A[0...i]
    B[0...i]

Return the prefix common array.

--------------------------------------------------------
Example
--------------------------------------------------------

Input:
A = [1,3,2,4]
B = [3,1,2,4]

Step-by-step:

i = 0
A prefix = [1]
B prefix = [3]

Common = 0

--------------------------------

i = 1
A prefix = [1,3]
B prefix = [3,1]

Common = {1,3}
Count = 2

--------------------------------

i = 2
A prefix = [1,3,2]
B prefix = [3,1,2]

Common = {1,2,3}
Count = 3

--------------------------------

i = 3
A prefix = [1,3,2,4]
B prefix = [3,1,2,4]

Common = {1,2,3,4}
Count = 4

Answer:
[0,2,3,4]

--------------------------------------------------------
Approach — Frequency Counting
--------------------------------------------------------

We maintain:

unordered_map<int,int> mp

Meaning:
mp[x] = how many times x has appeared
across both arrays so far.

--------------------------------------------------------
Key Observation
--------------------------------------------------------

When frequency becomes exactly 2:

    mp[x] == 2

that means:
- x appeared once in A prefix
- x appeared once in B prefix

So x becomes a common element.

We increase count.

--------------------------------------------------------
Algorithm
--------------------------------------------------------

For every i:

1. Add A[i]
2. If frequency becomes 2:
       cnt++

3. Add B[i]
4. If frequency becomes 2:
       cnt++

5. Store cnt in answer

--------------------------------------------------------
Time Complexity
--------------------------------------------------------

Each element processed once.

Time:
O(n)

Space:
O(n)

--------------------------------------------------------
Dry Run
--------------------------------------------------------

A = [1,3,2]
B = [3,1,2]

Initially:
cnt = 0

--------------------------------

i = 0

Add 1:
mp[1] = 1

Add 3:
mp[3] = 1

ans = [0]

--------------------------------

i = 1

Add 3:
mp[3] = 2
cnt = 1

Add 1:
mp[1] = 2
cnt = 2

ans = [0,2]

--------------------------------

i = 2

Add 2:
mp[2] = 1

Add 2:
mp[2] = 2
cnt = 3

ans = [0,2,3]

--------------------------------------------------------
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    vector<int> findThePrefixCommonArray(vector<int>& A,
                                         vector<int>& B) {

        /*
        cnt = number of common elements
        found so far
        */
        int cnt = 0;

        /*
        Frequency map across both arrays
        */
        unordered_map<int,int> mp;

        vector<int> ans;

        for(int i = 0; i < A.size(); i++){

            //------------------------------------------------
            // Add A[i]
            //------------------------------------------------
            mp[A[i]]++;

            /*
            If frequency becomes 2,
            then element is now common
            */
            if(mp[A[i]] == 2){
                cnt++;
            }

            //------------------------------------------------
            // Add B[i]
            //------------------------------------------------
            mp[B[i]]++;

            /*
            Again check if frequency becomes 2
            */
            if(mp[B[i]] == 2){
                cnt++;
            }

            //------------------------------------------------
            // Store answer for current prefix
            //------------------------------------------------
            ans.push_back(cnt);
        }

        return ans;
    }
};
