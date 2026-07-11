#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<long long> dijkstra(int start, int n, const vector<vector<pair<int, int>>>& adj) {
        vector<long long> dist(n, LLONG_MAX);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        vector<vector<pair<int, int>>> adj(n);
        vector<vector<pair<int, int>>> revAdj(n);
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
            revAdj[v].push_back({u, w});
        }
        
        vector<long long> distFromSrc1 = dijkstra(src1, n, adj);
        vector<long long> distFromSrc2 = dijkstra(src2, n, adj);
        vector<long long> distToDest = dijkstra(dest, n, revAdj);
        
        long long minWeight = LLONG_MAX;
        
        for (int i = 0; i < n; ++i) {
            if (distFromSrc1[i] == LLONG_MAX || distFromSrc2[i] == LLONG_MAX || distToDest[i] == LLONG_MAX) {
                continue;
            }
            long long currentWeight = distFromSrc1[i] + distFromSrc2[i] + distToDest[i];
            minWeight = min(minWeight, currentWeight);
        }
        
        return minWeight == LLONG_MAX ? -1 : minWeight;
    }
};