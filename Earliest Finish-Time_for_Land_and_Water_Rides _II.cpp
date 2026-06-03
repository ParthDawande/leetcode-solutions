#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int solve(vector<int>& v1, vector<int>& v2,
              vector<int>& v3, vector<int>& v4) {

        int n = v3.size();

        vector<pair<int,int>> rides;
        for(int i = 0; i < n; i++) {
            rides.push_back({v3[i], v4[i]});
        }

        sort(rides.begin(), rides.end());

        vector<int> starts(n);
        vector<int> prefix(n);
        vector<int> suffix(n);

        for(int i = 0; i < n; i++) {
            starts[i] = rides[i].first;
            prefix[i] = rides[i].second;
            suffix[i] = rides[i].first + rides[i].second;
        }

        for(int i = 1; i < n; i++) {
            prefix[i] = min(prefix[i], prefix[i - 1]);
        }

        for(int i = n - 2; i >= 0; i--) {
            suffix[i] = min(suffix[i], suffix[i + 1]);
        }

        int ans = INT_MAX;

        for(int i = 0; i < (int)v1.size(); i++) {
            int finishFirst = v1[i] + v2[i];

            int index = lower_bound(
                starts.begin(),
                starts.end(),
                finishFirst
            ) - starts.begin();

            // Second ride starts after first ride finishes
            if(index < n) {
                ans = min(ans, suffix[index]);
            }

            // Second ride already started before first ride finishes
            if(index > 0) {
                ans = min(ans, finishFirst + prefix[index - 1]);
            }
        }

        return ans;
    }

    int earliestFinishTime(vector<int>& landStartTime,
                           vector<int>& landDuration,
                           vector<int>& waterStartTime,
                           vector<int>& waterDuration) {

        int ans1 = solve(
            landStartTime,
            landDuration,
            waterStartTime,
            waterDuration
        );

        int ans2 = solve(
            waterStartTime,
            waterDuration,
            landStartTime,
            landDuration
        );

        return min(ans1, ans2);
    }
};