#include <bits/stdc++.h>
using namespace std;

/*
Problem: Walking Robot Simulation II (Optimized)
Platform: LeetCode

Approach:
- Simulate robot movement on grid with obstacles

Optimization:
- Instead of checking step-by-step ❌
- Use binary search on preprocessed obstacle positions ✅

Data Structures:
- mp1[x] → all y-coordinates where obstacle exists at column x
- mp2[y] → all x-coordinates where obstacle exists at row y

Steps:
1. Store obstacles:
    - Group by x and y
2. Sort obstacle lists (implicitly sorted due to sorting input)
3. Process commands:
    - Turn left/right
    - Move in direction using binary search to find nearest obstacle

4. Update position and track max distance

Time Complexity:
O(n log n + q log n)

Space Complexity:
O(n)

Concepts Used:
- Simulation
- Binary Search
- HashMap
*/

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {

        unordered_map<int, vector<int>> mp1; // x → list of y
        unordered_map<int, vector<int>> mp2; // y → list of x

        // Step 1: Sort obstacles
        sort(obstacles.begin(), obstacles.end());

        // Step 2: Fill maps
        for (int i = 0; i < obstacles.size(); i++) {
            int x = obstacles[i][0];
            int y = obstacles[i][1];

            mp1[x].push_back(y);
            mp2[y].push_back(x);
        }

        int maxi = 0;
        int cntx = 0, cnty = 0;

        string dir = "up";

        for (int i = 0; i < commands.size(); i++) {
            int num = commands[i];

            // Turning commands
            if (num < 0) {
                if (num == -1) { // turn right
                    if (dir == "up") dir = "right";
                    else if (dir == "right") dir = "down";
                    else if (dir == "down") dir = "left";
                    else dir = "up";
                } else { // turn left
                    if (dir == "up") dir = "left";
                    else if (dir == "right") dir = "up";
                    else if (dir == "down") dir = "right";
                    else dir = "down";
                }
            } 
            else {
                // Move forward

                if (dir == "up") {
                    vector<int> temp = mp1[cntx];
                    int index = upper_bound(temp.begin(), temp.end(), cnty) - temp.begin();

                    int limit = cnty + num;
                    if (index < temp.size()) {
                        limit = min(limit, temp[index] - 1);
                    }
                    cnty = limit;
                }

                else if (dir == "right") {
                    vector<int> temp = mp2[cnty];
                    int index = upper_bound(temp.begin(), temp.end(), cntx) - temp.begin();

                    int limit = cntx + num;
                    if (index < temp.size()) {
                        limit = min(limit, temp[index] - 1);
                    }
                    cntx = limit;
                }

                else if (dir == "down") {
                    vector<int> temp = mp1[cntx];
                    int index = lower_bound(temp.begin(), temp.end(), cnty) - temp.begin();
                    index--;

                    int limit = cnty - num;
                    if (index >= 0) {
                        limit = max(limit, temp[index] + 1);
                    }
                    cnty = limit;
                }

                else { // left
                    vector<int> temp = mp2[cnty];
                    int index = lower_bound(temp.begin(), temp.end(), cntx) - temp.begin();
                    index--;

                    int limit = cntx - num;
                    if (index >= 0) {
                        limit = max(limit, temp[index] + 1);
                    }
                    cntx = limit;
                }

                // Update max distance
                maxi = max(maxi, cntx * cntx + cnty * cnty);
            }
        }

        return maxi;
    }
};