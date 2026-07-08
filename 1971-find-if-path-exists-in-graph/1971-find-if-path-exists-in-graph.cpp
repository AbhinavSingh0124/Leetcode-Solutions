#include <vector>
#include <queue>

class Solution {
public:
    bool validPath(int n, std::vector<std::vector<int>>& edges, int source, int destination) {
        if (source == destination) return true;
        
        std::vector<std::vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        std::vector<bool> visited(n, false);
        std::queue<int> q;
        
        q.push(source);
        visited[source] = true;
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            
            for (int neighbor : adj[current]) {
                if (neighbor == destination) {
                    return true;
                }
                
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        return false;
    }
};