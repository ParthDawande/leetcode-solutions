#include <bits/stdc++.h>
using namespace std;

/*
Problem: Minimum Mirror Pair Distance
-------------------------------------
Find minimum |i - j| such that:
nums[i] == reverse(nums[j])

Return -1 if no such pair exists.

--------------------------------------------------
APPROACH 1: Binary Search + Map (O(n log n))
--------------------------------------------------

Idea:
- Store indices of each value in a map
- For each index i:
    - Compute reverse(nums[i])
    - Find nearest index of that value using binary search

Steps:
1. mp[value] → sorted indices
2. For each i:
    - Get list of reverse(nums[i])
    - Use lower_bound to find closest index
    - Check both left and right neighbors

Time Complexity: O(n log n)
Space Complexity: O(n)

--------------------------------------------------
APPROACH 2: Optimized Hashing (O(n))
--------------------------------------------------

Idea:
- Traverse from right → left
- Maintain map: value → nearest index on right
- For each i:
    - Compute reverse(nums[i])
    - If exists → update answer

Why it works:
- We always store the closest future index
- So distance is minimized automatically

Time Complexity: O(n)
Space Complexity: O(n)

--------------------------------------------------
*/

class Solution {
public:

    // Reverse digits of a number
    int rev(int num){
        int ans = 0;
        while(num > 0){
            int x = num % 10;
            num /= 10;
            ans = ans * 10 + x;
        }
        return ans;
    }

    // -------------------------------
    // Approach 1: O(n log n)
    // -------------------------------
    int approach1(vector<int>& nums){
        unordered_map<int, vector<int>> mp;

        for(int i = 0; i < nums.size(); i++){
            mp[nums[i]].push_back(i);
        }

        int ans = INT_MAX;

        for(int i = 0; i < nums.size(); i++){
            int target = rev(nums[i]);

            if(mp.find(target) == mp.end()) continue;

            vector<int>& temp = mp[target];

            int index = lower_bound(temp.begin(), temp.end(), i) - temp.begin();

            // check next
            if(index < temp.size()){
                if(temp[index] != i){
                    ans = min(ans, abs(temp[index] - i));
                }
                else if(index + 1 < temp.size()){
                    ans = min(ans, abs(temp[index + 1] - i));
                }
            }

            // check previous
            if(index - 1 >= 0){
                if(temp[index - 1] != i){
                    ans = min(ans, abs(temp[index - 1] - i));
                }
            }
        }

        return (ans == INT_MAX) ? -1 : ans;
    }

    // -------------------------------
    // Approach 2: O(n)
    // -------------------------------
    int approach2(vector<int>& nums){
        int ans = INT_MAX;
        unordered_map<int, int> mp;

        for(int i = nums.size() - 1; i >= 0; i--){
            int target = rev(nums[i]);

            if(mp.find(target) != mp.end()){
                ans = min(ans, mp[target] - i);
            }

            mp[nums[i]] = i;
        }

        return (ans == INT_MAX) ? -1 : ans;
    }

    // Final function (uses optimized)
    int minMirrorPairDistance(vector<int>& nums) {
        return approach2(nums); // switch to approach1(nums) if needed
    }
};