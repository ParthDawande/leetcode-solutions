/*
    LeetCode - Find Champion II

    ---------------------------------------------------------
    Problem:
    ---------------------------------------------------------

    We are given:
        n nodes
        directed edges

    Edge:
        u -> v

    means:
        u is stronger than v

    Champion:
        node with NO incoming edges.

    Why?
    ----
    Nobody defeats that node.

    ---------------------------------------------------------
    Key Observation
    ---------------------------------------------------------

    A champion must have:

        indegree = 0

    because no node points to it.

    ---------------------------------------------------------
    Important Condition
    ---------------------------------------------------------

    If MORE THAN ONE node has indegree 0:
        no unique champion exists.

    If NO node has indegree 0:
        no champion exists.

    Only ONE node with indegree 0:
        answer.

    ---------------------------------------------------------
    Approach
    ---------------------------------------------------------

    1. Compute indegree of every node.
    2. Count nodes with indegree 0.
    3. If count == 1:
            return that node
       else:
            return -1

    ---------------------------------------------------------
    Time Complexity
    ---------------------------------------------------------

    O(E + N)

    ---------------------------------------------------------
    Space Complexity
    ---------------------------------------------------------

    O(N)

*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int findChampion(int n,
                     vector<vector<int>>& edges) {

        /*
            indegree[i]
            = number of incoming edges
        */
        vector<int> indegree(n, 0);

        /*
            Build indegree array
        */
        for (int i = 0; i < edges.size(); i++) {

            int u = edges[i][0];
            int v = edges[i][1];

            indegree[v]++;
        }

        int cnt = 0;
        int ans = -1;

        /*
            Find nodes with indegree 0
        */
        for (int i = 0; i < n; i++) {

            if (indegree[i] == 0) {

                cnt++;
                ans = i;
            }
        }

        /*
            Unique champion required
        */
        if (cnt != 1) {
            return -1;
        }

        return ans;
    }
};

/*

=========================================================
Example 1
=========================================================

n = 3

edges:
0 -> 1
1 -> 2

Indegree:

0 = 0
1 = 1
2 = 1

Only node 0 has indegree 0.

Answer = 0

=========================================================
Example 2
=========================================================

n = 4

edges:
0 -> 2
1 -> 2
3 -> 2

Indegree:

0 = 0
1 = 0
2 = 3
3 = 0

Multiple nodes have indegree 0.

Answer = -1

=========================================================
Why Indegree Works
=========================================================

If a node has incoming edge:

    someone defeats it

So champion must never lose.

Meaning:

    indegree = 0

=========================================================
Time Complexity
=========================================================

Building indegree:
O(E)

Scanning nodes:
O(N)

Total:
O(E + N)

=========================================================
Space Complexity
=========================================================

O(N)

=========================================================
Git Commit Message
=========================================================

Added indegree based solution for finding graph champion

*/