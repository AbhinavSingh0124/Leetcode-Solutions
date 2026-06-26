#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Standard Fenwick Tree (Binary Indexed Tree) implementation
    void update(vector<int>& bit, int idx, int val, int n) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] += val;
        }
    }

    int query(vector<int>& bit, int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += bit[idx];
        }
        return sum;
    }

public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        
        // 1. Generate prefix sums
        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + (nums[i] == target ? 1 : -1);
        }

        // 2. Coordinate Compression for Fenwick Tree indices
        vector<int> ranks = pref;
        sort(ranks.begin(), ranks.end());
        ranks.erase(unique(ranks.begin(), ranks.end()), ranks.end());

        auto get_rank = [&](int val) {
            return lower_bound(ranks.begin(), ranks.end(), val) - ranks.begin() + 1;
        };

        // 3. Count pairs using Fenwick Tree
        long long total_subarrays = 0;
        int m = ranks.size();
        vector<int> bit(m + 1, 0);

        for (int x : pref) {
            int rank = get_rank(x);
            // Query how many previous elements have a strictly smaller prefix sum
            total_subarrays += query(bit, rank - 1);
            // Add current prefix sum to the Fenwick tree
            update(bit, rank, 1, m);
        }

        return total_subarrays;
    }
};