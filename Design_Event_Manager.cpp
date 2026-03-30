#include <bits/stdc++.h>
using namespace std;

/*
Problem: Event Manager (Design Data Structure)

Approach:
- Use a max-heap (priority_queue) to always get highest priority event
- Store (priority, -eventId) so:
    - Higher priority comes first
    - Smaller eventId comes first if priorities equal

- Use a hashmap (mp) to store latest priority of each event

Key Idea: Lazy Deletion
- When updating priority:
    → Do NOT remove old entry from heap
    → Just push new entry
- While polling:
    → Keep removing invalid entries from heap
    → Valid entry = matches current value in map

Operations:
1. Constructor:
    - Insert all events into heap
    - Store in map

2. updatePriority(eventId, newPriority):
    - Update map
    - Push new entry into heap

3. pollHighest():
    - Pop until top is valid
    - Remove from map and return eventId

Time Complexity:
- updatePriority: O(log n)
- pollHighest: amortized O(log n)

Space Complexity:
O(n)

Concepts Used:
- Heap (Priority Queue)
- HashMap
- Lazy Deletion
*/

class EventManager {
public:
    priority_queue<vector<int>> pq;
    unordered_map<int,int> mp;

    EventManager(vector<vector<int>>& events) {
        for(int i = 0; i < events.size(); i++){
            pq.push({events[i][1], -events[i][0]});
            mp[events[i][0]] = events[i][1];
        }
    }
    
    void updatePriority(int eventId, int newPriority) {
        mp[eventId] = newPriority;
        pq.push({newPriority, -eventId});
    }
    
    int pollHighest() {
        while(!pq.empty()){
            vector<int> temp = pq.top();
            int id = -temp[1];

            // Check if this entry is still valid
            if(mp.count(id) && mp[id] == temp[0]){
                pq.pop();
                mp.erase(id);
                return id;
            }

            // Remove outdated entry
            pq.pop();
        }
        return -1;
    }
};

/*
Usage:
EventManager* obj = new EventManager(events);
obj->updatePriority(eventId, newPriority);
int result = obj->pollHighest();
*/