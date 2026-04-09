#include <bits/stdc++.h>
using namespace std;

/*
Problem: XOR After Queries (Optimized)
Platform: LeetCode

Approach:
We optimize brute force using sqrt decomposition.

Observation:
- For large k → few updates → process directly
- For small k → many updates → optimize using difference arrays

Steps:
1. Let blocksize = sqrt(n)

2. For each query:
   - If k >= blocksize:
        → directly update nums[j] for j = l to r with step k
   - Else:
        → group queries by k

3. For each small k:
   - Use multiplicative difference array:
        diff[i] stores multiplier effect

   - Apply range updates using:
        diff[l] *= v
        diff[next] *= inverse(v)

   - Propagate using step k:
        diff[i] *= diff[i-k]

   - Apply diff to nums

4. Finally compute XOR

Time Complexity:
O(n * sqrt(n))

Space Complexity:
O(n)

Concepts Used:
- Sqrt Decomposition
- Modular inverse (Fermat’s theorem)
- Difference array (multiplicative)
- Fast exponentiation
*/

class Solution {
public:
    int M = 1e9+7;

    // Fast exponentiation
    long long power(long long a,long long b){
        if(b==0){
            return 1LL;
        }

        long long half = power(a,b/2);
        long long res = (half*half)%M;

        if(b%2==1){
            res = (res*a)%M;
        }

        return res;
    }

    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {

        int n = nums.size();

        int blocksize = ceil(sqrt(n));

        unordered_map<int,vector<vector<int>>> smallmap;

        // Step 1: Split queries
        for(int i=0;i<queries.size();i++){
            int l = queries[i][0];
            int r = queries[i][1];
            int k = queries[i][2];
            int v = queries[i][3];

            if(k>=blocksize){
                // Direct update
                for(int j=l;j<=r;j+=k){
                    nums[j] = (1LL*nums[j]*v)%M;
                }
            }
            else{
                smallmap[k].push_back(queries[i]);
            }
        }

        // Step 2: Handle small k
        for(auto& [k,allQueries] : smallmap){

            vector<int> diff(n,1);

            // Apply range updates
            for(auto query: allQueries){
                int l = query[0];

                diff[l] = (1LL*diff[l]*query[3])%M;

                int steps = (query[1]-query[0])/k;
                int next = l+(steps+1)*k;

                if(next<n){
                    diff[next] = (1LL*diff[next] * power(query[3],M-2))%M;
                }
            }

            // Propagate
            for(int i=0;i<n;i++){
                if(i-k>=0){
                    diff[i] = (1LL*diff[i]*diff[i-k])%M;
                }
            }

            // Apply to nums
            for(int i=0;i<n;i++){
                nums[i] = (1LL*nums[i]*diff[i])%M;
            }
        }

        // Step 3: XOR
        int res = 0;
        for(int i=0;i<n;i++){
            res = res^nums[i];
        }

        return res;
    }
};