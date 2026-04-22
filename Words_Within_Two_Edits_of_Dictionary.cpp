#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem: Words Within Two Edits of Dictionary
===========================================================

Given:
- queries: list of words
- dictionary: list of valid words

Goal:
Return all words from queries such that:
    → They differ from ANY dictionary word by at most 2 characters

-----------------------------------------------------------
Definition:
-----------------------------------------------------------

Edit distance here = number of positions where characters differ
(Hamming Distance, since lengths are equal)

-----------------------------------------------------------
Approach:
-----------------------------------------------------------

For each query word:
    → Compare it with every dictionary word
    → Count mismatches

If any dictionary word has:
    mismatches <= 2
    → include query in answer

-----------------------------------------------------------
Function: cal(w1, w2)
-----------------------------------------------------------

Counts number of mismatched characters

Optimization:
- Stop early if mismatches exceed 2

-----------------------------------------------------------
Why Early Exit?
-----------------------------------------------------------

If mismatch > 2:
    → No need to continue comparison
    → Saves time

-----------------------------------------------------------
Algorithm Flow:
-----------------------------------------------------------

For each query:
    mini = INF

    For each dictionary word:
        compute mismatch
        update mini

        If mini <= 2:
            break early

    If mini <= 2:
        add query to result

-----------------------------------------------------------
Time Complexity:
-----------------------------------------------------------

Let:
n = number of queries
m = number of dictionary words
k = length of each word

Worst Case:
O(n * m * k)

Early stopping helps in practice

-----------------------------------------------------------
Space Complexity:
-----------------------------------------------------------

O(1) extra (excluding output)

-----------------------------------------------------------
*/


class Solution {
public:

    // Count mismatches (Hamming distance)
    int cal(string w1, string w2){
        int cnt = 0;

        for(int i = 0; i < w1.length(); i++){
            if(w1[i] != w2[i]){
                cnt++;

                // Early exit
                if(cnt > 2){
                    return cnt;
                }
            }
        }

        return cnt;
    }

    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {

        vector<string> ans;

        int n = queries.size();
        int m = dictionary.size();

        for(int i = 0; i < n; i++){

            int mini = 200; // large value

            for(int j = 0; j < m; j++){

                mini = min(mini, cal(queries[i], dictionary[j]));

                // If already valid, stop checking further
                if(mini <= 2){
                    break;
                }
            }

            if(mini <= 2){
                ans.push_back(queries[i]);
            }
        }

        return ans;
    }
};


/*
===========================================================
Example:
-----------------------------------------------------------

queries = ["word","note","ants"]
dictionary = ["wood","joke","moat"]

Check:
"word" vs "wood" → mismatch = 1 → valid
"note" vs "moat" → mismatch = 2 → valid
"ants" vs all → mismatch > 2 → invalid

Answer:
["word","note"]

-----------------------------------------------------------
Key Insight:
-----------------------------------------------------------

We only need:
    mismatch <= 2

So:
    brute force + pruning works well

===========================================================
*/