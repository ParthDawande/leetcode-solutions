/*
===========================================================
📌 Problem: Check if There is a Valid Path in a Grid
===========================================================

🧠 Idea:
Each cell in the grid represents a street type (1 to 6).
Each type allows movement in specific directions.

Goal:
👉 Check if there exists a valid path from (0,0) to (n-1,m-1)

-----------------------------------------------------------
🚀 Approach: DFS + Street Connectivity
-----------------------------------------------------------

1️⃣ Each cell has allowed directions:

Type 1 → LEFT, RIGHT  
Type 2 → UP, DOWN  
Type 3 → LEFT, DOWN  
Type 4 → RIGHT, DOWN  
Type 5 → LEFT, UP  
Type 6 → RIGHT, UP  

-----------------------------------------------------------
2️⃣ Valid Move Condition:
We can move from (x,y) → (nx,ny) ONLY IF:
✔ Current cell allows that direction  
✔ Next cell allows reverse direction  

Example:
LEFT move → next cell must allow RIGHT

-----------------------------------------------------------
3️⃣ DFS Traversal:
- Start from (0,0)
- Mark visited
- Explore only valid connected neighbors
- Stop if we reach (n-1, m-1)

-----------------------------------------------------------
📌 Parent check:
Used to avoid going back immediately (not strictly needed with visited,
but included in your logic)

-----------------------------------------------------------
⏱ Complexity:
Time:  O(n * m)
Space: O(n * m)

-----------------------------------------------------------
📌 Key Insight:
This is NOT just DFS — it's graph traversal with constraints
(bidirectional connectivity required)
-----------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool dfs(vector<vector<int>>& grid,int x,int y,int parx,int pary,int n,int m,vector<vector<int>> &visited){
        
        // Destination reached
        if(x==n-1 && y==m-1){
            return true;
        }

        visited[x][y] = 1;

        // TYPE 1 → LEFT, RIGHT
        if(grid[x][y]==1){

            // LEFT
            if(y-1>=0){
                if((parx!=x || pary!=y-1) && visited[x][y-1]==0 &&
                   (grid[x][y-1]==1 || grid[x][y-1]==4 || grid[x][y-1]==6)){
                    if(dfs(grid,x,y-1,x,y,n,m,visited)) return true;
                }
            }

            // RIGHT
            if(y+1<m){
                if((parx!=x || pary!=y+1) && visited[x][y+1]==0 &&
                   (grid[x][y+1]==1 || grid[x][y+1]==3 || grid[x][y+1]==5)){
                    if(dfs(grid,x,y+1,x,y,n,m,visited)) return true;
                }
            }
        }

        // TYPE 2 → UP, DOWN
        else if(grid[x][y]==2){

            // UP
            if(x-1>=0){
                if((parx!=x-1 || pary!=y) && visited[x-1][y]==0 &&
                   (grid[x-1][y]==2 || grid[x-1][y]==3 || grid[x-1][y]==4)){
                    if(dfs(grid,x-1,y,x,y,n,m,visited)) return true;
                }
            }

            // DOWN
            if(x+1<n){
                if((parx!=x+1 || pary!=y) && visited[x+1][y]==0 &&
                   (grid[x+1][y]==2 || grid[x+1][y]==5 || grid[x+1][y]==6)){
                    if(dfs(grid,x+1,y,x,y,n,m,visited)) return true;
                }
            }
        }

        // TYPE 3 → LEFT, DOWN
        else if(grid[x][y]==3){

            // LEFT
            if(y-1>=0){
                if((parx!=x || pary!=y-1) && visited[x][y-1]==0 &&
                   (grid[x][y-1]==1 || grid[x][y-1]==4 || grid[x][y-1]==6)){
                    if(dfs(grid,x,y-1,x,y,n,m,visited)) return true;
                }
            }

            // DOWN
            if(x+1<n){
                if((parx!=x+1 || pary!=y) && visited[x+1][y]==0 &&
                   (grid[x+1][y]==2 || grid[x+1][y]==5 || grid[x+1][y]==6)){
                    if(dfs(grid,x+1,y,x,y,n,m,visited)) return true;
                }
            }
        }

        // TYPE 4 → RIGHT, DOWN
        else if(grid[x][y]==4){

            // RIGHT
            if(y+1<m){
                if((parx!=x || pary!=y+1) && visited[x][y+1]==0 &&
                   (grid[x][y+1]==1 || grid[x][y+1]==3 || grid[x][y+1]==5)){
                    if(dfs(grid,x,y+1,x,y,n,m,visited)) return true;
                }
            }

            // DOWN
            if(x+1<n){
                if((parx!=x+1 || pary!=y) && visited[x+1][y]==0 &&
                   (grid[x+1][y]==2 || grid[x+1][y]==5 || grid[x+1][y]==6)){
                    if(dfs(grid,x+1,y,x,y,n,m,visited)) return true;
                }
            }
        }

        // TYPE 5 → LEFT, UP
        else if(grid[x][y]==5){

            // LEFT
            if(y-1>=0){
                if((parx!=x || pary!=y-1) && visited[x][y-1]==0 &&
                   (grid[x][y-1]==1 || grid[x][y-1]==4 || grid[x][y-1]==6)){
                    if(dfs(grid,x,y-1,x,y,n,m,visited)) return true;
                }
            }

            // UP
            if(x-1>=0){
                if((parx!=x-1 || pary!=y) && visited[x-1][y]==0 &&
                   (grid[x-1][y]==2 || grid[x-1][y]==3 || grid[x-1][y]==4)){
                    if(dfs(grid,x-1,y,x,y,n,m,visited)) return true;
                }
            }
        }

        // TYPE 6 → RIGHT, UP
        else{

            // RIGHT
            if(y+1<m){
                if((parx!=x || pary!=y+1) && visited[x][y+1]==0 &&
                   (grid[x][y+1]==1 || grid[x][y+1]==3 || grid[x][y+1]==5)){
                    if(dfs(grid,x,y+1,x,y,n,m,visited)) return true;
                }
            }

            // UP
            if(x-1>=0){
                if((parx!=x-1 || pary!=y) && visited[x-1][y]==0 &&
                   (grid[x-1][y]==2 || grid[x-1][y]==3 || grid[x-1][y]==4)){
                    if(dfs(grid,x-1,y,x,y,n,m,visited)) return true;
                }
            }
        }

        return false;
    }

    bool hasValidPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> visited(n,vector<int>(m,0));

        return dfs(grid,0,0,-1,-1,n,m,visited);
    }
};