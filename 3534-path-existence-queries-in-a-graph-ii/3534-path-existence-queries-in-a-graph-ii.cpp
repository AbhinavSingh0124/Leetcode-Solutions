#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int, int>> sorted_nodes(n);
        for (int i = 0; i < n; ++i) {
            sorted_nodes[i] = {nums[i], i};
        }
        sort(sorted_nodes.begin(), sorted_nodes.end());

        vector<int> orig_to_sorted(n);
        for (int i = 0; i < n; ++i) {
            orig_to_sorted[sorted_nodes[i].second] = i;
        }

        int LOG = 18;
        vector<vector<int>> up(n, vector<int>(LOG));

        for (int i = 0; i < n; ++i) {
            auto it = upper_bound(sorted_nodes.begin(), sorted_nodes.end(), 
                                  make_pair(sorted_nodes[i].first + maxDiff, n));
            int furthest_idx = distance(sorted_nodes.begin(), it) - 1;
            up[i][0] = furthest_idx; 
        }

        for (int k = 1; k < LOG; ++k) {
            for (int i = 0; i < n; ++i) {
                up[i][k] = up[up[i][k - 1]][k - 1];
            }
        }

        vector<int> answer;
        for (const auto& q : queries) {
            int u = orig_to_sorted[q[0]];
            int v = orig_to_sorted[q[1]];

            if (u == v) {
                answer.push_back(0);
                continue;
            }
            if (u > v) swap(u, v);

            if (up[u][0] == u && sorted_nodes[v].first - sorted_nodes[u].first > maxDiff) {
                answer.push_back(-1);
                continue;
            }

            int steps = 0;
            int curr = u;

            for (int k = LOG - 1; k >= 0; --k) {
                if (up[curr][k] < v) {
                    steps += (1 << k);
                    curr = up[curr][k];
                }
            }

            if (up[curr][0] >= v && sorted_nodes[v].first - sorted_nodes[curr].first <= maxDiff) {
                answer.push_back(steps + 1);
            } else {
                answer.push_back(-1);
            }
        }

        return answer;
    }
};