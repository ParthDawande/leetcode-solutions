/*
========================================================
Create Binary Tree From Descriptions
LeetCode 2196

Approach: HashMap + Indegree Tracking
Time Complexity: O(N)
Space Complexity: O(N)

--------------------------------------------------------
PROBLEM
--------------------------------------------------------

Each description contains:

[parent, child, isLeft]

Meaning:

parent -> child

If isLeft = 1:
    child becomes left child

If isLeft = 0:
    child becomes right child

We need to construct the entire binary tree
and return its root.

--------------------------------------------------------
OBSERVATION
--------------------------------------------------------

Every node except the root appears
as someone's child.

Therefore:

Root = node with indegree 0

--------------------------------------------------------
APPROACH
--------------------------------------------------------

Step 1:
Create all TreeNode objects.

Use:

unordered_map<int, TreeNode*>

to map node value -> TreeNode pointer.

--------------------------------------------------------
Step 2:
Track indegree of every node.

Whenever:

u -> v

Increase:

indegree[v]++

The root will be the only node
whose indegree remains 0.

--------------------------------------------------------
Step 3:
Connect parent and child.

If isLeft == 1

    parent->left = child

Else

    parent->right = child

--------------------------------------------------------
Step 4:
Find node with indegree 0.

That node is the root.

--------------------------------------------------------
EXAMPLE
--------------------------------------------------------

descriptions =

[
 [20,15,1],
 [20,17,0],
 [15,10,1]
]

Tree:

        20
       /  \
      15  17
     /
    10

Indegree:

20 -> 0
15 -> 1
17 -> 1
10 -> 1

Root = 20

--------------------------------------------------------
WHY INDEGREE WORKS
--------------------------------------------------------

Every child gets exactly one parent.

So:

Root never appears as child.

Hence:

indegree(root) = 0

All others:

indegree >= 1

--------------------------------------------------------
COMPLEXITY
--------------------------------------------------------

Building nodes:
O(N)

Connecting nodes:
O(N)

Finding root:
O(N)

Total:
O(N)

Space:
O(N)

========================================================
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {

        unordered_map<int, TreeNode*> nodeMap;
        unordered_map<int, int> indegree;

        // Create all nodes and build indegree
        for(int i = 0; i < descriptions.size(); i++) {

            int parent = descriptions[i][0];
            int child = descriptions[i][1];

            if(nodeMap.find(parent) == nodeMap.end()) {
                nodeMap[parent] = new TreeNode(parent);
                indegree[parent] = 0;
            }

            if(nodeMap.find(child) == nodeMap.end()) {
                nodeMap[child] = new TreeNode(child);
            }

            indegree[child]++;
        }

        // Connect parent and child
        for(int i = 0; i < descriptions.size(); i++) {

            int parent = descriptions[i][0];
            int child = descriptions[i][1];

            TreeNode* parentNode = nodeMap[parent];
            TreeNode* childNode = nodeMap[child];

            if(descriptions[i][2] == 1) {
                parentNode->left = childNode;
            }
            else {
                parentNode->right = childNode;
            }
        }

        // Find root (indegree = 0)
        for(auto entry : indegree) {
            if(entry.second == 0) {
                return nodeMap[entry.first];
            }
        }

        return nullptr;
    }
};

