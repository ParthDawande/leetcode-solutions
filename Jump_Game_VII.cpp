/*
========================================================
Jump Game VII
========================================================

Problem:
You are given a binary string s.

You start at index 0.

You can jump from index i to index j if:

1. i + minJump <= j <= i + maxJump
2. s[j] == '0'

Return true if you can reach
the last index, otherwise false.

========================================================
Approach Used
========================================================

This solution uses:

1. BFS (Breadth First Search)
2. Preprocessing valid indices
3. Sliding pointer optimization

--------------------------------------------------------
Key Observation
--------------------------------------------------------

We only care about positions
where s[i] == '0'.

So first,
store all valid positions in an array.

--------------------------------------------------------
Optimization
--------------------------------------------------------

Naive BFS:
For every index,
checking all positions in range
would be O(n²).

Optimization:
Use a global pointer i
to process each valid index ONLY ONCE.

This reduces complexity to O(n).

========================================================
How It Works
========================================================

Step 1:
Store all indices having '0'
inside vector arr.

--------------------------------------------------------

Step 2:
Start BFS from index 0.

--------------------------------------------------------

Step 3:
For current position index:

Valid jump range is:
[index + minJump , index + maxJump]

Use pointer i to add all valid
positions from arr into queue.

Each position is pushed once.

========================================================
Complexity
========================================================

Time Complexity:
O(n)

Why?
- Every valid index processed once

Space Complexity:
O(n)

========================================================
Dry Run
========================================================

s = "011010"
minJump = 2
maxJump = 3

Valid positions:
arr = [0,3,5]

Start BFS:
0 -> can jump to 3
3 -> can jump to 5

Reached last index.

Answer = true

========================================================
Code
========================================================
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool canReach(string s,
                  int minJump,
                  int maxJump) {

        int n = s.length();

        // Last index must be reachable
        if(s[n - 1] == '1') {
            return false;
        }

        /*
        ------------------------------------------------
        Store all valid indices ('0')
        ------------------------------------------------
        */

        vector<int> arr;

        for(int i = 0; i < n; i++) {

            if(s[i] == '0') {
                arr.push_back(i);
            }
        }

        /*
        ------------------------------------------------
        BFS
        ------------------------------------------------
        */

        queue<int> q;

        q.push(0);

        /*
        Pointer used to avoid
        reprocessing indices
        */
        int i = 1;

        while(!q.empty()) {

            int index = q.front();
            q.pop();

            // Reached destination
            if(index == n - 1) {
                return true;
            }

            // Valid jump range
            int s = index + minJump;

            int e = min(n - 1,
                        index + maxJump);

            /*
            Skip positions before range
            */
            while(i < arr.size() &&
                  arr[i] < s) {

                i++;
            }

            /*
            Push all reachable positions
            */
            while(i < arr.size() &&
                  arr[i] <= e) {

                q.push(arr[i]);

                i++;
            }
        }

        return false;
    }
};

/*
========================================================
Why This Works
========================================================

The pointer i always moves forward.

So:
- No repeated work
- No revisiting indices
- Linear traversal

Hence overall O(n).

========================================================
*/