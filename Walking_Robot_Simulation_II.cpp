#include <bits/stdc++.h>
using namespace std;

/*
Problem: Walking Robot Simulation on Perimeter
Platform: LeetCode

Approach:
- Robot moves only along the boundary of a rectangle
- Movement follows directions in order:
    East → North → West → South → repeat

Key Observations:
1. Robot movement is cyclic along the perimeter
2. Total cycle length = perimeter = 2 * (width + height - 2)
3. Reduce steps using modulo

Steps:
1. Maintain:
    - current position (currx, curry)
    - current direction

2. On step(num):
    - Reduce num using modulo perimeter
    - Move in current direction
    - If boundary reached:
        → Change direction
        → Continue remaining steps recursively

3. Special Case:
    - If num % perimeter == 0:
        → Direction depends on corner position

Time Complexity:
O(num) worst-case (due to recursion splits)
Amortized efficient due to modulo

Space Complexity:
O(1)

Concepts Used:
- Simulation
- Circular movement
- Recursion
*/

class Robot {
public:
    int currx;
    int curry;
    int width;
    int height;
    string dir;
    int perimeter;

    Robot(int width, int height) {
        currx = 0;
        curry = 0;

        this->width = width;
        this->height = height;

        dir = "East";

        // Total cycle length
        perimeter = 2 * (width + height - 2);
    }
    
    void step(int num) {

        num = (num % perimeter);

        // Special case: full cycle
        if (num == 0) {
            if (currx == 0 && curry == 0) dir = "South";
            else if (currx == 0 && curry == width - 1) dir = "East";
            else if (currx == height - 1 && curry == width - 1) dir = "North";
            else if (currx == height - 1 && curry == 0) dir = "West";
            return;
        }

        // EAST
        if (dir == "East") {
            if (curry + num <= width - 1) {
                curry += num;
            } else {
                num -= (width - 1 - curry);
                curry = width - 1;
                dir = "North";
                step(num);
            }
        }

        // NORTH
        else if (dir == "North") {
            if (currx + num <= height - 1) {
                currx += num;
            } else {
                num -= (height - 1 - currx);
                currx = height - 1;
                dir = "West";
                step(num);
            }
        }

        // WEST
        else if (dir == "West") {
            if (curry - num >= 0) {
                curry -= num;
            } else {
                num -= curry;
                curry = 0;
                dir = "South";
                step(num);
            }
        }

        // SOUTH
        else {
            if (currx - num >= 0) {
                currx -= num;
            } else {
                num -= currx;
                currx = 0;
                dir = "East";
                step(num);
            }
        }
    }
    
    vector<int> getPos() {
        return {curry, currx};
    }
    
    string getDir() {
        return dir;
    }
};

/*
Usage:
Robot* obj = new Robot(width, height);
obj->step(num);
vector<int> pos = obj->getPos();
string direction = obj->getDir();
*/