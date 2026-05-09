/*
    LeetCode - Rotate Grid

    Approach Used:
    ----------------
    We process the matrix layer by layer (ring by ring).

    For every layer:
    1. Extract all elements of the boundary into a linear array.
    2. Rotate the array by k positions.
    3. Put rotated values back into the grid.

    ---------------------------------------------------
    Example:

    Grid:
    1 2 3 4
    5 6 7 8
    9 10 11 12
    13 14 15 16

    Outer layer extracted:
    [1,2,3,4,8,12,16,15,14,13,9,5]

    Rotate left by k:
    write values back.

    ---------------------------------------------------
    Time Complexity:
    O(n * m)

    Every element is visited once while extracting
    and once while inserting.

    Space Complexity:
    O(perimeter of layer)

*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {

        int n = grid.size();
        int m = grid[0].size();

        // Four corners of current layer
        int x0 = 0;
        int y0 = 0;

        int x1 = 0;
        int y1 = m - 1;

        int x2 = n - 1;
        int y2 = m - 1;

        int x3 = n - 1;
        int y3 = 0;

        // Process each layer
        while (x0 < x2 && y0 < y2) {

            vector<int> arr;

            int xi = x0;
            int yi = y0;

            /*
                Extract layer elements
            */

            // top row
            while (yi < y1) {
                arr.push_back(grid[xi][yi]);
                yi++;
            }

            // right column
            while (xi < x2) {
                arr.push_back(grid[xi][yi]);
                xi++;
            }

            // bottom row
            while (yi > y3) {
                arr.push_back(grid[xi][yi]);
                yi--;
            }

            // left column
            while (xi > x0) {
                arr.push_back(grid[xi][yi]);
                xi--;
            }

            int len = arr.size();

            /*
                Rotate layer by k
            */
            int t = k % len;

            xi = x0;
            yi = y0;

            /*
                Put rotated values back
            */

            // top row
            while (yi < y1) {
                grid[xi][yi] = arr[t];
                t = (t + 1) % len;
                yi++;
            }

            // right column
            while (xi < x2) {
                grid[xi][yi] = arr[t];
                t = (t + 1) % len;
                xi++;
            }

            // bottom row
            while (yi > y3) {
                grid[xi][yi] = arr[t];
                t = (t + 1) % len;
                yi--;
            }

            // left column
            while (xi > x0) {
                grid[xi][yi] = arr[t];
                t = (t + 1) % len;
                xi--;
            }

            /*
                Move to inner layer
            */
            x0++;
            y0++;

            x1++;
            y1--;

            x2--;
            y2--;

            x3--;
            y3++;
        }

        return grid;
    }
};

