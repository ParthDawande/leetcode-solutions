/*
===========================================================
📌 Problem: Count Subgraphs with Even Sum
===========================================================

🧠 Idea:
We are given:
- A graph with `n` nodes
- Each node has a value
- We need to count subgraphs such that:
   ✔ Subgraph is connected
   ✔ Sum of node values is EVEN

-----------------------------------------------------------
🚀 Approach: Bitmask + BFS (Brute Force)
-----------------------------------------------------------

1️⃣ Generate all possible subsets using bitmask:
   Range: 1 → (2^n - 1)

Each subset represents a possible subgraph.

-----------------------------------------------------------
2️⃣ For each subset:
   ✔ Extract nodes in subset
   ✔ Compute sum of their values
   ✔ Check if sum is EVEN

-----------------------------------------------------------
3️⃣ Connectivity Check (Important ⚠️):
Use BFS:
   - Start from any node in subset
   - Traverse only nodes present in subset
   - Count reachable nodes

If:
   reachable_nodes == total_nodes_in_subset
👉 Then it is CONNECTED

-----------------------------------------------------------
4️⃣ Count valid subsets

-----------------------------------------------------------
⏱ Complexity:
Time:  O(2^n * (n + m))
Space: O(n + m)

👉 Works because constraints are small

-----------------------------------------------------------
📌 Key Insight:
Brute force all subsets + filter using:
   ✔ Even sum
   ✔ Connected graph
-----------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Check if subset (bitmask) is valid
    bool check(vector<int>& nums, unordered_map<int,vector<int>> &adj, int nodes){

        int sum = 0;
        int i = 0;
        int start = -1;
        int total = 0;

        // Extract nodes from bitmask
        while((1<<i) <= nodes){
            if((nodes & (1<<i)) != 0){
                sum += nums[i];
                start = i;
                total++;
            }
            i++;
        }

        // Condition 1: sum must be even
        if(sum % 2 != 0){
            return false;
        }

        // Condition 2: must be connected (BFS)
        queue<int> q;
        int cnt = 0;

        q.push(start);

        int n = nums.size();
        vector<int> visited(n, 0);
        visited[start] = 1;

        while(!q.empty()){
            int t = q.front();
            q.pop();

            cnt++;

            for(auto nei : adj[t]){
                // Check if neighbor is in subset
                if((nodes & (1<<nei)) != 0 && visited[nei] == 0){
                    visited[nei] = 1;
                    q.push(nei);
                }
            }
        }

        // If all nodes in subset are reachable → connected
        return cnt == total;
    }

    int evenSumSubgraphs(vector<int>& nums, vector<vector<int>>& edges) {

        int n = nums.size();
        int m = edges.size();

        unordered_map<int,vector<int>> adj;

        // Build graph
        for(int i = 0; i < m; i++){
            int u = edges[i][0];
            int v = edges[i][1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int limit = (1 << n) - 1;
        int ans = 0;

        // Try all subsets
        for(int mask = 1; mask <= limit; mask++){
            if(check(nums, adj, mask)){
                ans++;
            }
        }

        return ans;
    }
};