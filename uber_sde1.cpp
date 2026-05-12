#include<bits/stdc++.h>
using namespace std;

/*
At Uber, optimization problems involving state transitions, streaming DP, and bitwise operations are commonly asked in backend and systems interviews.

You are given:

An integer array A of length N
An integer X

You may perform the following operation at most once:

Select any subsequence of indices from the array.
Add X to every selected element.

A subsequence is not required to be contiguous.

After performing the operation, define the score as:

(A1 xor A2) + (A2 xor A3) + ... + (A(N-1) xor AN)

Your task is to maximize this score.

Example

Input:

A = [2, 1, 6, 3, 5]
X = 7
*/

int solve1(vector<int> v, int x, int i, int f, vector<vector<int>>& dp){
    if(i>=v.size()){
        return 0;
    }
    if(dp[i][f]!=-1){
        return dp[i][f];
    }

    int prev = v[i-1];
    if(f==1){
        prev+=x;
    }

    return dp[i][f]= max((prev^v[i])+solve1(v,x,i+1,0,dp),(prev^(v[i]+x))+solve1(v,x,i+1,1,dp));
}

int solve(vector<int> v, int x){
    vector<vector<int>> dp(v.size()+1, vector<int>(2,-1)); 
    return max(solve1(v,x,1,1,dp), solve1(v,x,1,0,dp));
}


int main(){

    int n,x;
    cin>>n>>x;

    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    cout<<solve(v,x)<<endl;
    
}

/*
Time Complexity  : O(N)
Space Complexity : O(N)
*/