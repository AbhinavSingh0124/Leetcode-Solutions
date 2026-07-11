#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& edge : times) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }
        
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, k});
        
        while (!pq.empty()) {
            auto [currentTime, u] = pq.top();
            pq.pop();
            
            if (currentTime > dist[u]) continue;
            
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int time = neighbor.second;
                
                if (dist[u] + time < dist[v]) {
                    dist[v] = dist[u] + time;
                    pq.push({dist[v], v});
                }
            }
        }
        
        int maxDelay = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) return -1;
            maxDelay = max(maxDelay, dist[i]);
        }
        
        return maxDelay;
    }
};