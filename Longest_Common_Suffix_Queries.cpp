/*
========================================================
Longest Common Suffix Queries
========================================================

Problem:
Given:

1. wordsContainer
2. wordsQuery

For every query word,
return the index of the word in wordsContainer
having:

1. Longest common suffix
2. If tie -> shortest length
3. If still tie -> smallest index

========================================================
Approach Used
========================================================

This solution uses a:

TRIE built on REVERSED STRINGS

--------------------------------------------------------
Why Reverse?
--------------------------------------------------------

Suffix matching becomes prefix matching
after reversing strings.

Example:

"running"
"jogging"

Reverse:
"gninnur"
"gniggoj"

Now common suffix becomes common prefix.

========================================================
Trie Node Structure
========================================================

Each Trie node stores:

1. idx
   -> best candidate index for this suffix path

2. children[26]
   -> next characters

========================================================
Key Observation
========================================================

At every Trie node,
we store the BEST possible answer index.

Best means:

1. Smaller length preferred
2. If same length,
   smaller index automatically preserved

========================================================
Functions
========================================================

1. getNode()
Creates Trie node.

--------------------------------------------------------

2. insert()
Insert reversed word into Trie.

While inserting:
Update node->idx if current word
is shorter.

--------------------------------------------------------

3. search()
Traverse reversed query.

If path breaks:
return best answer so far.

========================================================
Insertion Logic
========================================================

For every character from BACK:

word[j]

Move inside Trie.

At every node:
if current inserted word is shorter,
update idx.

========================================================
Search Logic
========================================================

For query word:

Traverse from BACK.

If child exists:
continue.

Else:
return current best answer.

========================================================
Complexity
========================================================

Let:
N = total characters in container
Q = total characters in queries

Time Complexity:
O(N + Q)

Space Complexity:
O(N)

========================================================
Dry Run
========================================================

wordsContainer =
["abcd","bcd","xbcd"]

Trie stores reversed strings:
"dcba"
"dcb"
"dcbx"

Query:
"cd"

Reverse traversal:
d -> c

Best index stored = "bcd"

Answer = index of "bcd"

========================================================
Code
========================================================
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ----------------------------------------------------
    Trie Node
    ----------------------------------------------------
    */
    struct TrieNode {

        int idx;

        TrieNode* children[26];

        /*
        Destructor
        Frees memory recursively
        */
        ~TrieNode() {

            for(int i = 0; i < 26; i++) {

                delete children[i];
            }
        }
    };

    /*
    ----------------------------------------------------
    Create Trie Node
    ----------------------------------------------------
    */
    TrieNode* getNode(int i) {

        TrieNode* node = new TrieNode();

        node->idx = i;

        for(int i = 0; i < 26; i++) {

            node->children[i] = nullptr;
        }

        return node;
    }

    /*
    ====================================================
    INSERT WORD
    ====================================================

    Insert string in reverse order
    to support suffix matching.
    */
    void insert(TrieNode* root,
                int i,
                vector<string>& wordsContainer) {

        string word = wordsContainer[i];

        int n = word.length();

        /*
        Traverse from BACK
        */
        for(int j = n - 1; j >= 0; j--) {

            int index = word[j] - 'a';

            /*
            Create child if missing
            */
            if(root->children[index] == nullptr) {

                root->children[index] = getNode(i);
            }

            root = root->children[index];

            /*
            Update best index
            Prefer shorter string
            */
            if(wordsContainer[root->idx].size() > n) {

                root->idx = i;
            }
        }
    }

    /*
    ====================================================
    SEARCH QUERY
    ====================================================
    */
    int search(TrieNode* root,
               string word) {

        int n = word.length();

        /*
        Default answer:
        shortest string overall
        */
        int ans = root->idx;

        /*
        Traverse reversed query
        */
        for(int i = n - 1; i >= 0; i--) {

            int index = word[i] - 'a';

            TrieNode* child = root->children[index];

            /*
            Path breaks
            */
            if(child == nullptr) {

                return ans;
            }

            root = child;

            ans = root->idx;
        }

        return ans;
    }

    vector<int> stringIndices(vector<string>& wordsContainer,
                              vector<string>& wordsQuery) {

        int m = wordsContainer.size();

        int n = wordsQuery.size();

        vector<int> ans(n);

        /*
        Root initially stores
        globally shortest word
        */
        TrieNode* root = getNode(0);

        /*
        Build Trie
        */
        for(int i = 0; i < m; i++) {

            /*
            Update globally shortest word
            */
            if(wordsContainer[root->idx].length() >
               wordsContainer[i].length()) {

                root->idx = i;
            }

            insert(root, i, wordsContainer);
        }

        /*
        Answer queries
        */
        for(int i = 0; i < n; i++) {

            ans[i] = search(root,
                            wordsQuery[i]);
        }

        /*
        Free memory
        */
        delete root;

        return ans;
    }
};

/*
========================================================
Why Reversed Trie Works
========================================================

Suffix matching:
abcXYZ
pqrXYZ

Reverse:
ZYXcba
ZYXrqp

Now common suffix becomes
common prefix.

Trie becomes perfect for this.

========================================================
Optimization Notes
========================================================

This avoids:
- Comparing every query with every word
- O(N * Q * L)

Instead:
Trie gives near linear complexity.

*/