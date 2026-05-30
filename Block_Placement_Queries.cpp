/*
========================================================
Block Placement Queries
========================================================

Problem:
We process two types of queries:

Type 1:
[1, x]

Insert a barrier at position x.

--------------------------------------------------------

Type 2:
[2, x, sz]

Determine whether a block of size sz
can fit somewhere in the interval [0, x].

Return answers for all type-2 queries.

========================================================
Approach Used
========================================================

This solution combines:

1. Ordered Set
2. Segment Tree

--------------------------------------------------------
Why Ordered Set?
--------------------------------------------------------

The set stores all barrier positions.

It helps quickly find:

- Previous barrier
- Next barrier

using:

upper_bound()

in O(log n)

--------------------------------------------------------
Why Segment Tree?
--------------------------------------------------------

After inserting barriers,
we need to know:

Maximum free segment length
inside a prefix [0 ... x].

Segment Tree supports:

1. Point Update
2. Range Maximum Query

in O(log n)

========================================================
Core Idea
========================================================

Suppose barriers are:

0 ----- 5 ----- 12 ----- 20

Free segments:

5 - 0   = 5
12 - 5  = 7
20 - 12 = 8

Store these gaps in Segment Tree.

Then:

Query [0 ... x]

returns the largest free interval
available before x.

========================================================
Data Structures
========================================================

set<int> st

Stores barrier positions.

--------------------------------------------------------

segmentTree[pos]

Stores:

gap between current barrier
and previous barrier.

========================================================
Functions
========================================================

1. constructSegmentTree()

Creates tree.

--------------------------------------------------------

2. updateSegmentTree()

Point update.

Updates gap length.

--------------------------------------------------------

3. querySegTree()

Range maximum query.

Returns largest gap
inside requested interval.

========================================================
Insertion Query
========================================================

Query:

[1, x]

--------------------------------------------------------

Find:

pre = previous barrier

nxt = next barrier

--------------------------------------------------------

Before insertion:

pre -------- nxt

gap = nxt - pre

--------------------------------------------------------

After insertion:

pre ---- x ---- nxt

new gaps:

x - pre
nxt - x

Update both in segment tree.

========================================================
Check Query
========================================================

Query:

[2, x, sz]

--------------------------------------------------------

Find:

pre = largest barrier <= x

--------------------------------------------------------

Maximum block size can come from:

1. Any complete gap before pre
2. Partial segment (pre → x)

--------------------------------------------------------

Compute:

m = maximum gap in [0, pre]

maxi =
max(
    m,
    x - pre
)

If:

maxi >= sz

Answer = true

Else false

========================================================
Complexity
========================================================

Let Q = number of queries.

Type 1:
O(log N)

Type 2:
O(log N)

Overall:
O(Q log N)

Space:
O(N)

========================================================
Dry Run
========================================================

Initially:

Barriers:
{0}

--------------------------------------------------------

Insert 8

Gap:
8 - 0 = 8

--------------------------------------------------------

Insert 15

Gaps:

8
7

--------------------------------------------------------

Query:

[2,15,6]

Largest gap = 8

8 >= 6

Answer = true

========================================================
Code
========================================================
*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> segmentTree;

    /*
    Maximum coordinate constraint
    */
    int n = 50000;

    /*
    ----------------------------------------------------
    Build Segment Tree
    ----------------------------------------------------
    */
    void constructSegmentTree()
    {

        segmentTree.resize(4 * n, 0);
    }

    /*
    ----------------------------------------------------
    Point Update
    ----------------------------------------------------
    */
    void updateSegmentTree(int x,
                           int gap,
                           int index,
                           int l,
                           int r)
    {

        if (l == r)
        {

            segmentTree[index] = gap;

            return;
        }

        int m = l + (r - l) / 2;

        if (x <= m)
        {

            updateSegmentTree(
                x,
                gap,
                2 * index + 1,
                l,
                m);
        }
        else
        {

            updateSegmentTree(
                x,
                gap,
                2 * index + 2,
                m + 1,
                r);
        }

        segmentTree[index] =
            max(segmentTree[2 * index + 1],
                segmentTree[2 * index + 2]);

        return;
    }

    /*
    ----------------------------------------------------
    Range Maximum Query
    ----------------------------------------------------
    */
    int querySegTree(int s,
                     int e,
                     int index,
                     int l,
                     int r)
    {

        if (l > e || s > r)
        {

            return 0;
        }

        if (s <= l && r <= e)
        {

            return segmentTree[index];
        }

        int m = l + (r - l) / 2;

        return max(
            querySegTree(
                s,
                e,
                2 * index + 1,
                l,
                m),

            querySegTree(
                s,
                e,
                2 * index + 2,
                m + 1,
                r));
    }

    vector<bool> getResults(vector<vector<int>> &queries)
    {

        constructSegmentTree();

        /*
        Stores barrier positions
        */
        set<int> st;

        st.insert(0);

        vector<bool> ans;

        for (auto &query : queries)
        {

            /*
            =================================================
            Type 1
            Insert Barrier
            =================================================
            */
            if (query[0] == 1)
            {

                int x = query[1];

                auto it = st.upper_bound(x);

                int nxt =
                    (it != st.end())
                        ? *it
                        : -1;

                int pre = *prev(it);

                /*
                Gap:
                pre -> x
                */
                updateSegmentTree(
                    x,
                    x - pre,
                    0,
                    0,
                    n - 1);

                /*
                Gap:
                x -> nxt
                */
                updateSegmentTree(
                    nxt,
                    nxt - x,
                    0,
                    0,
                    n - 1);

                st.insert(x);
            }

            /*
            =================================================
            Type 2
            Check Block Placement
            =================================================
            */
            else
            {

                int x = query[1];

                int sz = query[2];

                auto it = st.upper_bound(x);

                int pre = *prev(it);

                /*
                Largest complete gap
                */
                int m =
                    querySegTree(
                        0,
                        pre,
                        0,
                        0,
                        n - 1);

                /*
                Consider partial segment
                */
                int maxi =
                    max(
                        m,
                        x - pre);

                ans.push_back(
                    maxi >= sz);
            }
        }

        return ans;
    }
};

/*
========================================================
Why Segment Tree Works
========================================================

Each barrier position stores:

gap from previous barrier.

Example:

0 --- 5 --- 12 --- 20

Store:

pos=5  -> 5
pos=12 -> 7
pos=20 -> 8

Range max query instantly gives
largest free segment.

========================================================
Why Set Works
========================================================

Insertion requires:

previous barrier
next barrier

set + upper_bound()

provides both in O(log n).

========================================================
Overall Complexity
========================================================

Insertion:
O(log N)

Check Query:
O(log N)

Total:
O(Q log N)


*/