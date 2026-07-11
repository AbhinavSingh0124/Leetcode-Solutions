#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            dist[u][v] = w;
            dist[v][u] = w;
        }
        
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        
        int minCityCount = n;
        int resultCity = -1;
        
        for (int i = 0; i < n; ++i) {
            int reachableCount = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j && dist[i][j] <= distanceThreshold) {
                    reachableCount++;
                }
            }
            
            if (reachableCount <= minCityCount) {
                minCityCount = reachableCount;
                resultCity = i;
            }
        }
        
        return resultCity;
    }
};