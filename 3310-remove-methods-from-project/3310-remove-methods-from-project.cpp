#include <vector>
#include <queue>
#include <numeric>

class Solution {
public:
    std::vector<int> remainingMethods(int n, int k, std::vector<std::vector<int>>& invocations) {
        // Step 1: Build the adjacency list graph
        std::vector<std::vector<int>> adj(n);
        for (const auto& edge : invocations) {
            adj[edge[0]].push_back(edge[1]);
        }

        // Step 2: BFS/DFS to find all suspicious methods reachable from k
        std::vector<bool> is_suspicious(n, false);
        std::queue<int> q;
        
        q.push(k);
        is_suspicious[k] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : adj[curr]) {
                if (!is_suspicious[neighbor]) {
                    is_suspicious[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // Step 3: Check if any non-suspicious method invokes a suspicious method
        for (const auto& edge : invocations) {
            int u = edge[0];
            int v = edge[1];
            if (!is_suspicious[u] && is_suspicious[v]) {
                // Cannot remove suspicious methods; return all methods [0, n - 1]
                std::vector<int> all_methods(n);
                std::iota(all_methods.begin(), all_methods.end(), 0);
                return all_methods;
            }
        }

        // Step 4: Collect all remaining non-suspicious methods
        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (!is_suspicious[i]) {
                result.push_back(i);
            }
        }

        return result;
    }
};