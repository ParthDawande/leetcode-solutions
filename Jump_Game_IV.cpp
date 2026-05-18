/*
========================================================
Jump Game IV — BFS Solution
========================================================

Problem:
--------
You are given an array nums.

From index i, you can jump to:

1. i + 1
2. i - 1
3. Any index j where nums[i] == nums[j]

Return the minimum number of jumps required
to reach the last index.

--------------------------------------------------------
Approach — BFS on Graph
--------------------------------------------------------

We can think of every index as a node in a graph.

From every index we have edges to:
- index - 1
- index + 1
- all indices having the same value

Since every move costs exactly 1 jump,
BFS gives the shortest path.

--------------------------------------------------------
Key Optimization
--------------------------------------------------------

Without optimization, same-value jumps can
cause O(n²) complexity.

Example:
nums = [7,7,7,7,7,7]

Every index would repeatedly process all
other equal-value indices.

To avoid this:

    mp[nums[index]].clear();

After processing a value once,
we clear its vector.

This ensures:
- every same-value group processed once
- total complexity becomes nearly O(n)

--------------------------------------------------------
Time Complexity
--------------------------------------------------------

Building hashmap:
O(n)

BFS traversal:
O(n)

Total:
O(n)

Space:
O(n)

--------------------------------------------------------
Dry Run
--------------------------------------------------------

nums = [100,-23,-23,404,100,23,23,23,3,404]

Start:
index = 0

Possible jumps:
1
4 (same value 100)

Path:
0 → 4 → 3 → 9

Answer = 3

--------------------------------------------------------
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minJumps(vector<int>& nums) {

        int n = nums.size();

        // Already at destination
        if(n == 1){
            return 0;
        }

        /*
        Store all indices for every value

        Example:
        nums = [7,6,9,6,9,6]

        mp[6] = [1,3,5]
        mp[9] = [2,4]
        */
        unordered_map<int, vector<int>> mp;

        for(int i = 0; i < n; i++){
            mp[nums[i]].push_back(i);
        }

        /*
        visited[i] stores minimum steps
        used to reach index i
        */
        vector<int> visited(n, INT_MAX);

        visited[0] = 0;

        /*
        Queue stores:
        {steps, index}
        */
        queue<vector<int>> q;

        q.push({0, 0});

        while(!q.empty()){

            vector<int> temp = q.front();
            q.pop();

            int steps = temp[0];
            int index = temp[1];

            // Reached destination
            if(index == n - 1){
                return steps;
            }

            //------------------------------------------------
            // Move Left
            //------------------------------------------------
            if(index - 1 >= 0 &&
               visited[index - 1] > steps + 1){

                visited[index - 1] = steps + 1;

                q.push({steps + 1, index - 1});
            }

            //------------------------------------------------
            // Move Right
            //------------------------------------------------
            if(index + 1 < n &&
               visited[index + 1] > steps + 1){

                visited[index + 1] = steps + 1;

                q.push({steps + 1, index + 1});
            }

            //------------------------------------------------
            // Same Value Jumps
            //------------------------------------------------
            for(auto ind : mp[nums[index]]){

                if(ind != index &&
                   visited[ind] > steps + 1){

                    visited[ind] = steps + 1;

                    q.push({steps + 1, ind});
                }
            }

            /*
            IMPORTANT OPTIMIZATION

            Once processed,
            clear same-value indices.

            Prevents repeated processing
            and avoids O(n²).
            */
            mp[nums[index]].clear();
        }

        return n - 1;
    }
};

