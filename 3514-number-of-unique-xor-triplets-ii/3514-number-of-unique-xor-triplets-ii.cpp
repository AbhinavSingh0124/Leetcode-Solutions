class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        // Step 1: Extract unique numbers
        vector<int> u;
        {
            unordered_set<int> unique_set(nums.begin(), nums.end());
            u.assign(unique_set.begin(), unique_set.end());
        }
        
        int n = u.size();
        vector<bool> seen(2048, false);
        
        // Mark all single unique elements as reachable
        for (int x : u) {
            seen[x] = true;
        }
        
        // Step 2: Compute x ^ y ^ z for all triples x < y < z
        // Optimize by collecting pair XORs (x ^ y) as we iterate y
        vector<bool> pair_xors(2048, false);
        
        for (int y = 0; y < n; ++y) {
            // For the current y, pair it with all z > y
            for (int z = y + 1; z < n; ++z) {
                // Combine existing pair XORs (x ^ y) with z
                // We only do this if pair_xors has entries from x < y
            }
        }
        
        // A cleaner standard loop structure:
        // Collect pair XORs for all x < y:
        vector<vector<int>> pairs_with_max_index(n);
        for (int x = 0; x < n; ++x) {
            for (int y = x + 1; y < n; ++y) {
                pairs_with_max_index[y].push_back(u[x] ^ u[y]);
            }
        }
        
        // For each z, XOR u[z] with all (x ^ y) where y < z
        vector<bool> valid_pair_xor(2048, false);
        for (int z = 0; z < n; ++z) {
            for (int px : pairs_with_max_index[z]) {
                valid_pair_xor[px] = true;
            }
            for (int val = 0; val < 2048; ++val) {
                if (valid_pair_xor[val]) {
                    seen[val ^ u[z]] = true;
                }
            }
        }
        
        // Step 3: Count total unique reachable values
        int count = 0;
        for (bool b : seen) {
            if (b) count++;
        }
        
        return count;
    }
};