#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int n = heights.size();
        int q = queries.size();
        vector<int> ans(q, -1);
        
        // Group unresolved queries by index b
        // stored_queries[b] = list of {required_height, query_index}
        vector<vector<pair<int, int>>> stored_queries(n);
        
        for (int i = 0; i < q; ++i) {
            int a = queries[i][0];
            int b = queries[i][1];
            
            // Ensure a <= b
            if (a > b) swap(a, b);
            
            // Direct meeting conditions
            if (a == b || heights[a] < heights[b]) {
                ans[i] = b;
            } else {
                // Needs building t > b with heights[t] > heights[a]
                stored_queries[b].push_back({heights[a], i});
            }
        }
        
        // Min-heap storing {required_height, query_index}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
        
        for (int i = 0; i < n; ++i) {
            // Process all pending queries that can be satisfied by building i
            while (!min_heap.empty() && min_heap.top().first < heights[i]) {
                ans[min_heap.top().second] = i;
                min_heap.pop();
            }
            
            // Add queries starting after index i
            for (const auto& query : stored_queries[i]) {
                min_heap.push(query);
            }
        }
        
        return ans;
    }
};