/*
========================================================
Count Special Characters II
========================================================

Problem:
A character is considered SPECIAL if:

1. Both lowercase and uppercase versions exist
2. The lowercase character appears BEFORE
   the uppercase character in the string

Return the number of special characters.

========================================================
Approach Used
========================================================

This solution uses:

1. Frequency maps
2. First occurrence tracking
3. Last occurrence tracking

--------------------------------------------------------
Key Observation
--------------------------------------------------------

For a character c to be special:

1. lowercase c must exist
2. uppercase C must exist
3. last occurrence of lowercase
   must be BEFORE
   first occurrence of uppercase

Example:

word = "aaAbcBC"

'a' last index = 1
'A' first index = 2

Since 1 < 2,
'a' is special.

========================================================
Maps Used
========================================================

mp1:
Stores lowercase frequencies

mp2:
Stores uppercase frequencies

mp3:
Stores LAST occurrence of lowercase chars

mp4:
Stores FIRST occurrence of uppercase chars

========================================================
How It Works
========================================================

Traverse the string:

--------------------------------------------------------
If uppercase:
--------------------------------------------------------

- Store frequency in mp2
- Store first occurrence in mp4

--------------------------------------------------------
If lowercase:
--------------------------------------------------------

- Store frequency in mp1
- Update last occurrence in mp3

========================================================
Final Check
========================================================

For every lowercase character:

Convert to uppercase using toupper()

Check:
1. uppercase exists
2. first uppercase index >
   last lowercase index

If true:
increment answer.

========================================================
Complexity
========================================================

Time Complexity:
O(n)

Space Complexity:
O(1)

(At most 52 English letters)

========================================================
Dry Run
========================================================

word = "aaAbBcC"

Lowercase:
a -> last = 1
b -> last = 3
c -> last = 5

Uppercase:
A -> first = 2
B -> first = 4
C -> first = 6

All satisfy:
lowercase before uppercase

Answer = 3

========================================================
Code
========================================================
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int numberOfSpecialChars(string word) {

        /*
        ------------------------------------------------
        mp1 -> lowercase frequency
        mp2 -> uppercase frequency
        mp3 -> last lowercase position
        mp4 -> first uppercase position
        ------------------------------------------------
        */

        unordered_map<char, int> mp1;
        unordered_map<char, int> mp2;

        unordered_map<char, int> mp3;
        unordered_map<char, int> mp4;

        /*
        ------------------------------------------------
        Traverse string
        ------------------------------------------------
        */

        for(int i = 0; i < word.length(); i++) {

            // Uppercase character
            if(word[i] < 'a') {

                mp2[word[i]]++;

                // Store FIRST occurrence only
                if(mp2[word[i]] == 1) {

                    mp4[word[i]] = i;
                }
            }

            // Lowercase character
            else {

                mp1[word[i]]++;

                // Store LAST occurrence
                mp3[word[i]] = i;
            }
        }

        int cnt = 0;

        /*
        ------------------------------------------------
        Check valid special characters
        ------------------------------------------------
        */

        for(auto i : mp1) {

            char d = i.first;

            // Convert lowercase to uppercase
            char d1 = toupper(d);

            /*
            Conditions:
            1. Uppercase exists
            2. Uppercase appears after lowercase
            */

            if(mp2[d1] > 0 &&
               mp4[d1] > mp3[d]) {

                cnt++;
            }
        }

        return cnt;
    }
};

/*
========================================================
Why This Works
========================================================

We only count characters where:

last lowercase occurrence
<
first uppercase occurrence

This guarantees ALL lowercase letters
appear before uppercase letters.

========================================================
Alternative Optimization
========================================================

Instead of unordered_map,
arrays of size 26 can also be used
for better performance.

*/