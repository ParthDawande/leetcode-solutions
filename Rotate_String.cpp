#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ============================================================
    PROBLEM INTUITION
    ------------------------------------------------------------
    We need to check if "goal" can be obtained by rotating string s.

    Rotation means:
        Take some prefix and move it to the end.

    Example:
        s = "abcde"
        rotation at i = 2 → "cde" + "ab" = "cdeab"
    ============================================================
    */

    bool rotateString(string s, string goal) {

        /*
        Length mismatch → impossible
        */
        if(s.length() != goal.length()){
            return false;
        }

        /*
        If already equal → no rotation needed
        */
        if(s == goal){
            return true;
        }

        int n = s.length();

        /*
        Try all possible rotations
        */
        for(int i = 1; i <= n - 1; i++){

            /*
            Split into two parts
            */
            string h1 = s.substr(0, i);   // prefix
            string h2 = s.substr(i);      // suffix

            /*
            Rotate → suffix + prefix
            */
            string h3 = h2 + h1;

            /*
            Check match
            */
            if(h3 == goal){
                return true;
            }
        }

        return false;
    }
};