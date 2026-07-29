#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> min_dist(n, 1e9);
        vector<bool> visited(n, false);
        
        // Start from point 0
        min_dist[0] = 0;
        int total_cost = 0;
        
        for (int step = 0; step < n; ++step) {
            int curr_node = -1;
            
            // Find the unvisited node with the smallest distance to the MST
            for (int i = 0; i < n; ++i) {
                if (!visited[i] && (curr_node == -1 || min_dist[i] < min_dist[curr_node])) {
                    curr_node = i;
                }
            }
            
            // Add node to MST
            visited[curr_node] = true;
            total_cost += min_dist[curr_node];
            
            // Update distances to neighboring nodes
            for (int next_node = 0; next_node < n; ++next_node) {
                if (!visited[next_node]) {
                    int dist = abs(points[curr_node][0] - points[next_node][0]) + 
                               abs(points[curr_node][1] - points[next_node][1]);
                    
                    if (dist < min_dist[next_node]) {
                        min_dist[next_node] = dist;
                    }
                }
            }
        }
        
        return total_cost;
    }
};