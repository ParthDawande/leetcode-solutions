/*
===========================================================
Problem: Minimum Jumps with Prime Teleportation
===========================================================

Goal:
-----
Find the minimum number of jumps needed to reach the
last index.

Allowed moves:
---------------
1. Move to index - 1
2. Move to index + 1
3. Prime Jump:
   If nums[i] is PRIME,
   jump to ANY index j such that:
       nums[j] % nums[i] == 0

-----------------------------------------------------------
Key Observation:
-----------------------------------------------------------

Normal BFS works for:
- left move
- right move

But prime jumps can be expensive if processed repeatedly.

-----------------------------------------------------------
Optimization:
-----------------------------------------------------------

For every PRIME p:
Store all indices whose value is divisible by p.

Example:
---------
nums = [2,4,6,9]

Prime 2:
    reachable indices = [0,1,2]

Prime 3:
    reachable indices = [2,3]

-----------------------------------------------------------
Preprocessing:
-----------------------------------------------------------

1. Store indices of every value:
       mp[value] -> list of indices

2. Use Sieve of Eratosthenes to find primes.

3. Build:
       primeBranch[p]
   containing all indices whose values are divisible by p.

-----------------------------------------------------------
Why "used[p]" is important:
-----------------------------------------------------------

Without it:
- Same prime transitions get processed repeatedly
- Complexity becomes huge

So each prime teleportation is used only ONCE.

-----------------------------------------------------------
BFS State:
-----------------------------------------------------------

Queue stores:
    {steps, value, index}

-----------------------------------------------------------
Algorithm:
-----------------------------------------------------------

1. Build divisor-based teleport graph
2. Start BFS from index 0
3. Explore:
    - left
    - right
    - prime teleport
4. First time reaching n-1 gives minimum jumps

-----------------------------------------------------------
Time Complexity:
-----------------------------------------------------------

Sieve + preprocessing:
    ~O(maxVal log log maxVal)

BFS:
    O(n)

Overall:
    Efficient for large constraints

-----------------------------------------------------------
Space Complexity:
-----------------------------------------------------------
O(n + maxVal)

-----------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minJumps(vector<int>& nums) {

        int n = nums.size();

        unordered_map<int, vector<int>> mp;

        int maxi = 0;

        // Store indices for every value
        for(int i = 0; i < n; i++) {

            mp[nums[i]].push_back(i);

            maxi = max(maxi, nums[i]);
        }

        /*
        ---------------------------------------------------
        Sieve of Eratosthenes
        ---------------------------------------------------
        prime[i] = 1 if i is prime
        ---------------------------------------------------
        */
        vector<int> prime(maxi + 1, 1);

        if(maxi >= 0) prime[0] = 0;
        if(maxi >= 1) prime[1] = 0;

        /*
        ---------------------------------------------------
        primeBranch[p]
        -> all indices whose value is divisible by p
        ---------------------------------------------------
        */
        vector<vector<int>> primeBranch(maxi + 1);

        for(int i = 2; i <= maxi; i++) {

            if(prime[i]) {

                // mark multiples as non-prime
                for(int j = i * 2; j <= maxi; j += i) {
                    prime[j] = 0;
                }

                // collect all reachable indices
                for(int j = i; j <= maxi; j += i) {

                    if(mp.find(j) != mp.end()) {

                        for(auto ind : mp[j]) {
                            primeBranch[i].push_back(ind);
                        }
                    }
                }
            }
        }

        /*
        ---------------------------------------------------
        BFS
        ---------------------------------------------------
        Queue stores:
            {steps, value, index}
        ---------------------------------------------------
        */
        queue<vector<int>> q;

        q.push({0, nums[0], 0});

        vector<int> visited(n, 0);

        visited[0] = 1;

        /*
        ---------------------------------------------------
        used[p]
        prevents reprocessing same prime teleport
        ---------------------------------------------------
        */
        vector<int> used(maxi + 1, 0);

        while(!q.empty()) {

            vector<int> temp = q.front();

            q.pop();

            int steps = temp[0];
            int num = temp[1];
            int index = temp[2];

            // reached destination
            if(index == n - 1) {
                return steps;
            }

            /*
            ------------------------------------------------
            Move Left
            ------------------------------------------------
            */
            if(index - 1 >= 0 && !visited[index - 1]) {

                visited[index - 1] = 1;

                q.push({steps + 1, nums[index - 1], index - 1});
            }

            /*
            ------------------------------------------------
            Move Right
            ------------------------------------------------
            */
            if(index + 1 < n && !visited[index + 1]) {

                visited[index + 1] = 1;

                q.push({steps + 1, nums[index + 1], index + 1});
            }

            /*
            ------------------------------------------------
            Prime Teleport
            ------------------------------------------------
            Allowed only if current number is prime
            ------------------------------------------------
            */
            if(num >= 2 && prime[num] && !used[num]) {

                used[num] = 1;

                for(auto newIndex : primeBranch[num]) {

                    if(!visited[newIndex]) {

                        visited[newIndex] = 1;

                        q.push({steps + 1, nums[newIndex], newIndex});
                    }
                }
            }
        }

        return -1;
    }
};