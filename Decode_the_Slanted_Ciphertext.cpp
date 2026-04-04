#include <bits/stdc++.h>
using namespace std;

/*
Problem: Decode the Slanted Ciphertext
Platform: LeetCode

Approach:
1. Compute number of columns:
    cols = encodedText.length() / rows

2. Fill matrix row-wise:
    - Convert string into 2D grid

3. Traverse diagonally:
    - Start from each column of first row
    - Move diagonally (i++, j++)

4. Build result string

5. Remove trailing spaces

Time Complexity: O(n)
Space Complexity: O(rows * cols)

Concepts Used:
- Matrix construction
- Diagonal traversal
- String manipulation
*/

class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {

        int cols = encodedText.length() / rows;

        vector<vector<char>> arr(rows, vector<char>(cols));

        int k = 0;

        // Step 1: Fill matrix row-wise
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                arr[i][j] = encodedText[k];
                k++;
            }
        }

        string ans = "";

        // Step 2: Traverse diagonals
        for (int i = 0; i < cols; i++) {
            int x = 0;
            int y = i;

            while (x < rows && y < cols) {
                ans += arr[x][y];
                x++;
                y++;
            }
        }

        // Step 3: Remove trailing spaces
        while (ans.length() > 0 && ans.back() == ' ') {
            ans.pop_back();
        }

        return ans;
    }
};