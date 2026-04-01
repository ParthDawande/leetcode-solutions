#include <bits/stdc++.h>
using namespace std;

/*
Problem: Survived Robots Healths
Platform: LeetCode

Approach:
1. Combine position, health, and direction into a single array:
    - Store direction using sign:
        +ve → Right (R)
        -ve → Left (L)

2. Sort robots by position:
    - So collisions can be processed in order

3. Use stack to simulate collisions:
    - Push right-moving robots
    - When a left-moving robot appears:
        → Handle collisions with stack top

4. Collision rules:
    - Smaller health robot dies
    - Larger health robot loses 1 health
    - Equal health → both die

5. Continue until no more collisions possible

6. Store surviving robots using original indices

Time Complexity: O(n log n) (sorting)
Space Complexity: O(n)

Concepts Used:
- Stack (collision simulation)
- Sorting
- Greedy simulation
*/

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {

        vector<vector<int>> arr;

        // Step 1: Combine data
        for(int i = 0; i < positions.size(); i++){
            int f = 1;
            if(directions[i] == 'L') f = -1;

            arr.push_back({positions[i], f * healths[i], i});
        }

        // Step 2: Sort by position
        sort(arr.begin(), arr.end());

        stack<vector<int>> st;

        // Step 3: Process robots
        for(int i = 0; i < arr.size(); i++){
            int num = arr[i][1];

            // Right moving robot
            if(num > 0){
                st.push({num, arr[i][0], arr[i][2]});
            }
            else {
                // Left moving robot → collision
                while(!st.empty() && st.top()[0] > 0 && st.top()[0] <= abs(num)){
                    vector<int> t = st.top();
                    st.pop();

                    if(t[0] < abs(num)){
                        num++; // left robot survives but loses 1 health
                    }
                    else{
                        num = 0; // both die or right stronger
                        break;
                    }
                }

                // No more collision
                if(st.empty() || st.top()[0] < 0){
                    if(num != 0){
                        st.push({num, arr[i][0], arr[i][2]});
                    }
                }
                else if(num != 0){
                    // Right robot survives
                    if(st.top()[0] > abs(num)){
                        st.top()[0]--;
                    }
                }
            }
        }

        // Step 4: Collect survivors
        vector<int> ans(positions.size(), 0);
        vector<int> result;

        while(!st.empty()){
            vector<int> t = st.top();
            st.pop();
            ans[t[2]] = abs(t[0]);
        }

        // Maintain original order
        for(int i = 0; i < ans.size(); i++){
            if(ans[i] != 0){
                result.push_back(ans[i]);
            }
        }

        return result;
    }
};