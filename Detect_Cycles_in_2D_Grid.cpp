/*
===========================================================
📌 Problem: Detect Cycles in 2D Grid
===========================================================

🧠 Idea:
We are given a 2D grid of characters.

We need to check if there exists a cycle such that:
👉 All cells in the cycle have the SAME character
👉 Cycle length ≥ 4
👉 Movement allowed in 4 directions (up, down, left, right)

-----------------------------------------------------------
🚀 Approach: DFS + Parent Tracking
-----------------------------------------------------------

1️⃣ Traverse every cell in the grid

2️⃣ If a cell is not visited:
   → Start DFS from that cell

3️⃣ During DFS:
   - Move only to neighbors with SAME character
   - Keep track of parent cell (parx, pary)

4️⃣ Cycle condition:
   👉 If we visit a cell that is already visited
   👉 AND it is NOT the parent → cycle exists

-----------------------------------------------------------
📌 Why Parent Check?
Without parent check, every back-edge will look like a cycle.
We must ignore the edge going back to parent.

-----------------------------------------------------------
⏱ Complexity:
Time:  O(n * m)
Space: O(n * m) (visited + recursion stack)

-----------------------------------------------------------
📌 Key Insight:
Cycle detection in grid = same as cycle detection in graph
(using DFS with parent tracking)
-----------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool check(vector<vector<char>>& grid, int x, int y, int parx, int pary, vector<vector<int>> &visited) {
        visited[x][y] = 1;

        // DOWN
        if (x + 1 < grid.size()) {
            if (grid[x + 1][y] == grid[x][y]) {
                if (!(parx == x + 1 && pary == y)) {
                    if (visited[x + 1][y] == 1) {
                        return true;
                    } else {
                        if (check(grid, x + 1, y, x, y, visited)) return true;
                    }
                }
            }
        }

        // UP
        if (x - 1 >= 0) {
            if (grid[x - 1][y] == grid[x][y]) {
                if (!(parx == x - 1 && pary == y)) {
                    if (visited[x - 1][y] == 1) {
                        return true;
                    } else {
                        if (check(grid, x - 1, y, x, y, visited)) return true;
                    }
                }
            }
        }

        // RIGHT
        if (y + 1 < grid[0].size()) {
            if (grid[x][y + 1] == grid[x][y]) {
                if (!(parx == x && pary == y + 1)) {
                    if (visited[x][y + 1] == 1) {
                        return true;
                    } else {
                        if (check(grid, x, y + 1, x, y, visited)) return true;
                    }
                }
            }
        }

        // LEFT
        if (y - 1 >= 0) {
            if (grid[x][y - 1] == grid[x][y]) {
                if (!(parx == x && pary == y - 1)) {
                    if (visited[x][y - 1] == 1) {
                        return true;
                    } else {
                        if (check(grid, x, y - 1, x, y, visited)) return true;
                    }
                }
            }
        }

        return false;
    }

    bool containsCycle(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> visited(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (visited[i][j] == 0) {
                    if (check(grid, i, j, -1, -1, visited)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};