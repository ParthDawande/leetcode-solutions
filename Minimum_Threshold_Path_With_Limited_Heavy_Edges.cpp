/*
    Problem:
    --------
    Find the minimum threshold such that we can travel
    from source to target using at most k expensive edges.

    Edge Rule:
    ----------
    If edge weight <= threshold:
        edge is FREE

    Else:
        edge consumes 1 special allowance.

    We can use at most k such expensive edges.

    ------------------------------------------------------

    Approach:
    ----------
    Binary Search + BFS

    Why Binary Search?
    ------------------
    If a threshold works,
    then every larger threshold will also work.

    This monotonic property allows binary search.

    ------------------------------------------------------

    BFS State:
    ----------
    {node, remaining_expensive_edges}

    visited[node]
    stores maximum remaining k seen for that node.

    Why?
    ----
    Reaching same node with more remaining operations
    is always better.

    ------------------------------------------------------

    Binary Search:
    --------------
    low = 0
    high = 1e9 + 1

    For every mid:
        check if path exists using BFS.

    ------------------------------------------------------

    Time Complexity:
    ----------------
    BFS  -> O(V + E)

    Binary Search over weights:
    O(log(1e9))

    Total:
    O((V + E) * log(1e9))

    ------------------------------------------------------

    Space Complexity:
    -----------------
    O(V + E)

*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
        BFS Check Function

        Returns true if target can be reached
        using threshold = limit
    */
    bool check(int n,
               unordered_map<int, vector<vector<int>>>& adj,
               int source,
               int target,
               int k,
               int limit) {

        /*
            visited[node]
            = maximum remaining expensive edges
              available when reaching this node
        */
        vector<int> visited(n, -1);

        visited[source] = k;

        queue<vector<int>> q;

        /*
            {node, remaining_k}
        */
        q.push({source, k});

        while (!q.empty()) {

            vector<int> temp = q.front();
            q.pop();

            int node = temp[0];
            int r = temp[1];

            /*
                Reached destination
            */
            if (node == target) {
                return true;
            }

            /*
                Explore neighbours
            */
            for (auto i : adj[node]) {

                int nei = i[0];
                int w = i[1];

                /*
                    Cheap edge
                    No special usage needed
                */
                if (w <= limit) {

                    if (visited[nei] < r) {

                        visited[nei] = r;

                        q.push({nei, r});
                    }
                }

                /*
                    Expensive edge
                    Uses one special allowance
                */
                else {

                    if (r > 0) {

                        if (visited[nei] < r - 1) {

                            visited[nei] = r - 1;

                            q.push({nei, r - 1});
                        }
                    }
                }
            }
        }

        return false;
    }

    int minimumThreshold(int n,
                         vector<vector<int>>& edges,
                         int source,
                         int target,
                         int k) {

        /*
            Build Graph
        */
        unordered_map<int, vector<vector<int>>> adj;

        for (int i = 0; i < edges.size(); i++) {

            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        /*
            Binary Search on threshold
        */
        int l = 0;
        int r = 1e9 + 1;

        int ans = INT_MAX;

        while (l <= r) {

            int m = l + (r - l) / 2;

            /*
                Check if threshold works
            */
            if (check(n, adj, source, target, k, m)) {

                ans = m;

                r = m - 1;
            }

            else {
                l = m + 1;
            }
        }

        /*
            No valid threshold found
        */
        if (ans == INT_MAX) {
            return -1;
        }

        return ans;
    }
};

/*

------------------------------------------------------
Example
------------------------------------------------------

n = 5

Edges:
0-1 (4)
1-2 (8)
2-3 (2)
3-4 (10)

source = 0
target = 4
k = 1

Suppose threshold = 5

Cheap edges:
4,2

Expensive edges:
8,10

We can use only one expensive edge.

Path:
0 -> 1 -> 2 -> 3 -> 4

Needs 2 expensive edges.

Not possible.

Increase threshold.

------------------------------------------------------
Why Binary Search Works
------------------------------------------------------

If threshold = X works,
then threshold > X also works because
more edges become cheap.

Monotonic property:
false false false true true true

Hence binary search.

------------------------------------------------------
Time Complexity
------------------------------------------------------

BFS:
O(V + E)

Binary Search:
O(log(1e9))

Total:
O((V + E) * log(1e9))

------------------------------------------------------
Space Complexity
------------------------------------------------------

O(V + E)

------------------------------------------------------
Git Commit Message
------------------------------------------------------

Added binary search + BFS solution for minimum threshold path problem


*/