#include<bits/stdc++.h>
using namespace std;

/*
Problem: Max Stability (Graph + DSU + Greedy)
Platform: (Codeforces / LeetCode - update if needed)

Approach:
- Use Disjoint Set Union (DSU) to maintain connected components
- First process all mandatory edges (must = 1):
    - If they form a cycle → return -1
    - Otherwise, union them and update minimum weight

- Store optional edges separately
- Sort optional edges in descending order of weight
- Apply Kruskal-like approach:
    - Add edges that connect different components
    - Store their weights in a min-heap

- Use k operations:
    - For first k edges → consider 2 * weight
    - For remaining → consider normal weight
    - Track minimum value across all

- Finally, check if the graph is fully connected using BFS
    - If not connected → return -1

Time Complexity: O(E log E + E α(N))
Space Complexity: O(N + E)

Concepts Used:
- DSU (Union-Find)
- Greedy (Kruskal-like)
- BFS (Connectivity Check)
- Priority Queue (Min Heap)
*/

class Solution {
public:
    void insert(unordered_map<int, int>& union_mp, int u, int v) {
        int ult_parent_u = find_boss(union_mp, u);
        int ult_parent_v = find_boss(union_mp, v);

        if (ult_parent_u < ult_parent_v) {
            union_mp[ult_parent_v] = ult_parent_u;
        } else {
            union_mp[ult_parent_u] = ult_parent_v;
        }
    }

    int find_boss(unordered_map<int, int>& union_mp, int u) {
        if (union_mp[u] == u) {
            return u;
        }

        return find_boss(union_mp, union_mp[u]);
    }

    bool same_group(unordered_map<int, int>& union_mp, int u, int v) {
        int ult_parent_u = find_boss(union_mp, u);
        int ult_parent_v = find_boss(union_mp, v);

        return ult_parent_u == ult_parent_v;
    }

    bool check(unordered_map<int, vector<vector<int>>>& adj, int n) {
        vector<int> visited(n, 0);
        int cnt = 0;
        queue<vector<int>> q;
        q.push({0, -1});

        while (!q.empty()) {
            vector<int> t = q.front();
            int node = t[0];
            int parent = t[1];
            visited[node] = 1;
            cnt++;
            q.pop();
            for (auto nei : adj[node]) {
                if (nei[0] != parent) {
                    if (visited[nei[0]] == 0) {
                        q.push({nei[0], node});
                    }
                }
            }
        }

        return cnt == n;
    }

    static bool cmp(vector<int>& a, vector<int>& b) { return a[2] > b[2]; }

    int maxStability(int n, vector<vector<int>>& edges, int k) {
        unordered_map<int, vector<vector<int>>> adj;
        unordered_map<int, int> union_mp;
        vector<vector<int>> custom_edges;
        int mini = INT_MAX;
        for (int i = 0; i < n; i++) {
            union_mp[i] = i;
        }
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            int musti = edges[i][3];

            if (musti == 1) {
                if (same_group(union_mp, u, v)) {
                    return -1;
                }
                insert(union_mp, u, v);
                adj[u].push_back({v, w, musti});
                adj[v].push_back({u, w, musti});
                mini = min(mini, w);
            } else {
                custom_edges.push_back(edges[i]);
            }
        }

        sort(custom_edges.begin(), custom_edges.end(), cmp);
        priority_queue<int, vector<int>, greater<int>> pq;

        int i = 0;
        while (i < custom_edges.size()) {
            int u = custom_edges[i][0];
            int v = custom_edges[i][1];
            int w = custom_edges[i][2];

            if (!same_group(union_mp, u, v)) {
                insert(union_mp, u, v);
                adj[u].push_back({v, w, 0});
                adj[v].push_back({u, w, 0});
                pq.push(w);
            }
            i++;
        }

        while (!pq.empty()) {
            int h = pq.top();
            pq.pop();
            if (k > 0) {
                mini = min(mini, 2 * h);
                k--;
            } else {
                mini = min(mini, h);
            }
        }

        if (!check(adj, n)) {
            return -1;
        }

        return mini;
    }
};