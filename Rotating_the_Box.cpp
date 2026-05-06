/*
===========================================================
Problem: Rotate the Box
===========================================================

Goal:
-----
Given a box represented as a grid:
    '#' → stone
    '*' → obstacle
    '.' → empty

Simulate gravity (stones fall to the right),
then rotate the box 90° clockwise.

-----------------------------------------------------------
Key Idea:
-----------------------------------------------------------

Instead of simulating gravity cell-by-cell,
we process each row in segments separated by '*'.

For each segment:
- Count number of stones '#'
- Place them at the RIGHTMOST positions of that segment

-----------------------------------------------------------
Steps:
-----------------------------------------------------------

1. For each row:
   - Break into segments (split by '*')
   - For each segment:
       store:
           {ending_position, number_of_stones}

2. Build rotated grid:
   - size becomes (m x n)
   - Initialize with '.'

3. Fill rotated grid:
   - For each segment:
       - place '*' at correct position
       - fill stones '#' from right to left

-----------------------------------------------------------
Why this works:
-----------------------------------------------------------
- We simulate gravity implicitly (by packing stones right)
- Rotation is handled during placement into new grid

-----------------------------------------------------------
Time Complexity:
-----------------------------------------------------------
O(n * m)

-----------------------------------------------------------
Space Complexity:
-----------------------------------------------------------
O(n * m)

-----------------------------------------------------------
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int n = boxGrid.size();
        int m = boxGrid[0].size();

        // Step 1: Store segments info for each row
        vector<vector<vector<int>>> arr;
        
        for(int i = 0; i < n; i++) {
            vector<vector<int>> temp;

            int i1 = 0;
            while(i1 < m) {
                int j = i1;
                int cnt = 0;

                // Count stones in segment until obstacle '*'
                while(j < m && boxGrid[i][j] != '*') {
                    if(boxGrid[i][j] == '#') {
                        cnt++;
                    }
                    j++;
                }

                // Store: {ending index of segment, number of stones}
                temp.push_back({j, cnt});

                // Move to next segment
                i1 = j + 1;
            }

            arr.push_back(temp);
        }

        // Step 2: Prepare rotated grid
        vector<vector<char>> ans(m, vector<char>(n, '.'));

        // Step 3: Fill rotated grid
        int col = n - 1;

        for(int i = 0; i < arr.size(); i++) {

            for(int k = 0; k < arr[i].size(); k++) {

                int pos = arr[i][k][0];   // segment end
                int stones = arr[i][k][1];

                // Place obstacle
                if(pos < m) {
                    ans[pos][col] = '*';
                }

                // Place stones from right to left
                int l = pos - 1;
                while(stones--) {
                    ans[l][col] = '#';
                    l--;
                }
            }

            col--;
        }

        return ans;
    }
};