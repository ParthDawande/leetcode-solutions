#include<bits/stdc++.h>
using namespace std;    

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();

        vector<int> visited(n,0);

        queue<int> q;
        q.push(start);
        visited[start]++;

        while(!q.empty()){
            int t = q.front();
            q.pop();

            if(arr[t]==0){
                return true;
            }

            int d = arr[t];

            // Forward jump
            if(t+d<n && visited[t+d]==0){
                visited[t+d]++;
                q.push(t+d);
            }

            // Backward jump
            if(t-d>=0 && visited[t-d]==0){
                visited[t-d]++;
                q.push(t-d);
            }
        }

        return false;
    }
};