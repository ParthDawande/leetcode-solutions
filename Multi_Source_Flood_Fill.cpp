#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem: Color Grid Using Multiple Sources
===========================================================

Given:
- Grid of size n x m
- Multiple source cells: [x, y, color]

Goal:
- Spread colors from all sources simultaneously
- Each step spreads to 4 directions (up, down, left, right)
- Final grid should reflect:
    1. Minimum distance coloring (closest source wins)
    2. If same distance → higher color value wins

-----------------------------------------------------------
Core Idea: Multi-Source BFS
-----------------------------------------------------------

We push ALL sources into the queue initially.

Each element in queue:
    {x, y, color, time}

-----------------------------------------------------------
Data Structures:
-----------------------------------------------------------

grid[][]:
    → Stores final color of each cell

visited[][]:
    → Stores minimum time (distance) to reach each cell

-----------------------------------------------------------
Transition Rules:
-----------------------------------------------------------

From cell (x, y), we try 4 directions.

We update neighbor (nx, ny) IF:

1. It is not yet colored:
    grid[nx][ny] == 0

OR

2. We found a better path:
    visited[nx][ny] >= current_time + 1
    AND current color is greater

This ensures:
- Minimum distance is always preferred
- If tie → higher color wins

-----------------------------------------------------------
Why BFS?
-----------------------------------------------------------

- BFS ensures shortest distance (level by level expansion)
- Multi-source BFS ensures simultaneous spreading

-----------------------------------------------------------
Time Complexity:
-----------------------------------------------------------

O(n * m)

Each cell is processed at most a few times

-----------------------------------------------------------
Space Complexity:
-----------------------------------------------------------

O(n * m)

-----------------------------------------------------------
*/


class Solution {
public:
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {

        vector<vector<int>> visited(n, vector<int>(m, 1000000));
        vector<vector<int>> grid(n, vector<int>(m, 0));

        // queue: {x, y, color, time}
        queue<vector<int>> q;

        // Initialize with all sources
        for(int i = 0; i < sources.size(); i++){
            int x = sources[i][0];
            int y = sources[i][1];
            int color = sources[i][2];

            q.push({x, y, color, 0});
            grid[x][y] = color;
            visited[x][y] = 0;
        }

        // BFS
        while(!q.empty()){
            vector<int> temp = q.front();
            q.pop();

            int x = temp[0];
            int y = temp[1];
            int color = temp[2];
            int t = temp[3];

            // DOWN
            if(x + 1 < n){
                if(grid[x+1][y] == 0 || (visited[x+1][y] >= t+1 && grid[x+1][y] < color)){
                    grid[x+1][y] = color;
                    visited[x+1][y] = t + 1;
                    q.push({x+1, y, color, t+1});
                }
            }

            // RIGHT
            if(y + 1 < m){
                if(grid[x][y+1] == 0 || (visited[x][y+1] >= t+1 && grid[x][y+1] < color)){
                    grid[x][y+1] = color;
                    visited[x][y+1] = t + 1;
                    q.push({x, y+1, color, t+1});
                }
            }

            // UP
            if(x - 1 >= 0){
                if(grid[x-1][y] == 0 || (visited[x-1][y] >= t+1 && grid[x-1][y] < color)){
                    grid[x-1][y] = color;
                    visited[x-1][y] = t + 1;
                    q.push({x-1, y, color, t+1});
                }
            }

            // LEFT
            if(y - 1 >= 0){
                if(grid[x][y-1] == 0 || (visited[x][y-1] >= t+1 && grid[x][y-1] < color)){
                    grid[x][y-1] = color;
                    visited[x][y-1] = t + 1;
                    q.push({x, y-1, color, t+1});
                }
            }
        }

        return grid;
    }
};


/*
===========================================================
Example:
-----------------------------------------------------------

n = 3, m = 3
sources = [[0,0,1], [2,2,2]]

Step 0:
1 . .
. . .
. . 2

Step 1:
1 1 .
1 . 2
. 2 2

Step 2:
1 1 2
1 2 2
2 2 2

-----------------------------------------------------------
Conflict Rule:
If two colors reach same cell at same time:
→ higher color wins

===========================================================
*/