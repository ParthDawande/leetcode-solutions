/*
    LeetCode - Regular Expression Matching

    ---------------------------------------------------------
    Problem:
    ---------------------------------------------------------

    We are given:

        s -> input string
        p -> pattern

    Pattern supports:

        '.'  -> matches any single character
        '*'  -> matches zero or more of previous character

    We must determine:
        does pattern completely match the string?

    ---------------------------------------------------------
    Examples
    ---------------------------------------------------------

    s = "aa"
    p = "a*"

    '*' means:
        zero or more 'a'

    So:
        "aa" matches.

    ---------------------------------------------------------

    s = "ab"
    p = ".*"

    '.' -> any character
    '*' -> repeat infinitely

    So:
        matches everything.

    ---------------------------------------------------------
    Approach:
    ---------------------------------------------------------

    Recursion + Memoization (Top Down DP)

    State:
    -------
    solve(index1, index2)

    means:

        Can s[index1 ... end]
        match p[index2 ... end] ?

    ---------------------------------------------------------
    Transition
    ---------------------------------------------------------

    Case 1:
    --------
    Current characters match.

    match =
        s[index1] == p[index2]
        OR
        p[index2] == '.'

    ---------------------------------------------------------

    Case 2:
    --------
    Next character in pattern is '*'

    Two possibilities:

    1. Ignore character + '*'
            solve(i, j+2)

    2. Use current match
            solve(i+1, j)

    ---------------------------------------------------------

    Case 3:
    --------
    Normal character match

            solve(i+1, j+1)

    ---------------------------------------------------------
    Time Complexity:
    ---------------------------------------------------------

    O(n * m)

    ---------------------------------------------------------
    Space Complexity:
    ---------------------------------------------------------

    O(n * m)

*/
#include<bits/stdc++.h> 
using namespace std;    

class Solution {
public:

    bool solve(string s,
               string p,
               int index1,
               int index2,
               vector<vector<int>>& dp) {

        /*
            Both string and pattern finished
        */
        if (index1 >= s.length() &&
            index2 >= p.length()) {

            return true;
        }

        /*
            Pattern finished but string remains
        */
        else if (index2 >= p.length()) {

            return false;
        }

        /*
            Memoization
        */
        if (dp[index1][index2] != -1) {

            return dp[index1][index2];
        }

        /*
            Current characters match?
        */
        bool match =
            (index1 < s.length()) &&
            (s[index1] == p[index2] ||
             p[index2] == '.');

        /*
            Handle '*'
        */
        if (index2 + 1 < p.length() &&
            p[index2 + 1] == '*') {

            /*
                Two choices:

                1. Skip x*
                2. Use x*
            */
            return dp[index1][index2] =

                solve(s, p,
                      index1,
                      index2 + 2,
                      dp)

                ||

                (match &&
                 solve(s, p,
                       index1 + 1,
                       index2,
                       dp));
        }

        /*
            Normal match
        */
        if (match) {

            return dp[index1][index2] =

                solve(s, p,
                      index1 + 1,
                      index2 + 1,
                      dp);
        }

        /*
            No match possible
        */
        return dp[index1][index2] = false;
    }

    bool isMatch(string s, string p) {

        /*
            DP table

            dp[i][j]
            = answer for suffixes
        */
        vector<vector<int>> dp(
            21,
            vector<int>(21, -1));

        return solve(s, p, 0, 0, dp);
    }
};

/*

=========================================================
Example 1
=========================================================

s = "aa"
p = "a*"

"a*" can generate:
"", "a", "aa", "aaa" ...

So answer = true

=========================================================
Example 2
=========================================================

s = "ab"
p = ".*"

'.' matches any character
'*' repeats infinitely

Matches entire string.

Answer = true

=========================================================
Why '*' Needs Two Choices
=========================================================

Pattern:
    a*

Can represent:

1. Empty string
2. One 'a'
3. Multiple 'a'

So:

Skip:
    solve(i, j+2)

Use:
    solve(i+1, j)

=========================================================
DP State Meaning
=========================================================

dp[i][j]

means:

Can:

    s[i...]
match:
    p[j...]

=========================================================
Time Complexity
=========================================================

States:
O(n * m)

Each state solved once.

Total:
O(n * m)

=========================================================
Space Complexity
=========================================================

O(n * m)

=========================================================
Git Commit Message
=========================================================

Added recursive DP solution for regex matching problem


*/