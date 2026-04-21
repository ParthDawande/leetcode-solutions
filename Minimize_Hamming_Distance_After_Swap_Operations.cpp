#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem: Minimum Hamming Distance After Swap Operations
===========================================================

Given:
- Two arrays: source and target
- allowedSwaps: pairs of indices that can be swapped

Goal:
Minimize Hamming Distance:
    count of indices i where source[i] != target[i]

-----------------------------------------------------------
Key Observation:
-----------------------------------------------------------

If indices are connected via allowedSwaps,
they form a "connected component".

Within a component:
    → we can rearrange elements freely

So:
    Instead of positions → think of MULTISET matching

-----------------------------------------------------------
Approach:
-----------------------------------------------------------

1. Build Graph:
   - Nodes = indices
   - Edges = allowed swaps

2. Find Connected Components:
   - Use BFS

3. For each component:
   - Collect all indices in that component

4. Matching Logic:
   - Count frequency of source values in component
   - Try to match with target values

-----------------------------------------------------------
Function: cal(component, source, target)
-----------------------------------------------------------

Step 1:
    Count frequency of source values in component

Step 2:
    For each index:
        If target value exists in map → match it

Step 3:
    Remaining unmatched = Hamming contribution

-----------------------------------------------------------
Why This Works:
-----------------------------------------------------------

Inside a component:
    → we can permute source arbitrarily

So:
    Best strategy = maximize matches with target

-----------------------------------------------------------
Time Complexity:
-----------------------------------------------------------

Graph build: O(E)
BFS: O(N + E)
Matching: O(N)

Total: O(N + E)

-----------------------------------------------------------
Space Complexity:
-----------------------------------------------------------

O(N + E)

-----------------------------------------------------------
*/


class Solution {
public:

    // Calculate mismatch in one connected component
    int cal(vector<int>& component, vector<int>& source, vector<int>& target) {
        unordered_map<int, int> mp;

        // Count frequency of source values
        for (int idx : component) {
            mp[source[idx]]++;
        }

        int match = 0;

        // Try to match target values
        for (int idx : component) {
            if (mp[target[idx]] > 0) {
                match++;
                mp[target[idx]]--;
            }
        }

        // Unmatched = contribution to Hamming distance
        return component.size() - match;
    }

    int minimumHammingDistance(vector<int>& source, vector<int>& target,
                               vector<vector<int>>& allowedSwaps) {

        unordered_map<int, vector<int>> adj;

        // Build graph
        for (int i = 0; i < allowedSwaps.size(); i++) {
            int u = allowedSwaps[i][0];
            int v = allowedSwaps[i][1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int total = 0;
        int n = source.size();

        vector<int> visited(n, 0);

        // Traverse all components
        for (int i = 0; i < n; i++) {
            if (visited[i] == 0) {

                vector<int> component;

                queue<int> q;
                q.push(i);
                visited[i] = 1;

                // BFS to collect component
                while (!q.empty()) {
                    int t = q.front();
                    q.pop();

                    component.push_back(t);

                    for (auto nei : adj[t]) {
                        if (visited[nei] == 0) {
                            visited[nei] = 1;
                            q.push(nei);
                        }
                    }
                }

                // Add mismatch for this component
                total += cal(component, source, target);
            }
        }

        return total;
    }
};


/*
===========================================================
Example:
-----------------------------------------------------------

source = [1,2,3,4]
target = [2,1,4,5]
allowedSwaps = [[0,1],[2,3]]

Components:
[0,1] → source = {1,2}, target = {2,1} → perfect match → 0
[2,3] → source = {3,4}, target = {4,5}

Matching:
4 matches → 1 mismatch (3 vs 5)

Answer = 1

-----------------------------------------------------------
Key Insight:
-----------------------------------------------------------

Connected Component = Free rearrangement

So:
Problem reduces to:
    Maximum matching of values in each component

===========================================================
*/