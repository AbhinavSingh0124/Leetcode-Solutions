class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        int n = nums.size();
        int max_val = 0;
        for (int num : nums) max_val = max(max_val, num);
        
        long long MOD = 1e9 + 7;
        
        vector<vector<long long>> dp(max_val + 1, vector<long long>(max_val + 1, 0));
        dp[0][0] = 1;
        
        for (int num : nums) {
            vector<vector<long long>> next_dp = dp;
            
            for (int g1 = 0; g1 <= max_val; ++g1) {
                for (int g2 = 0; g2 <= max_val; ++g2) {
                    if (dp[g1][g2] == 0) continue;
                    
                    int new_g1 = std::gcd(g1, num);
                    next_dp[new_g1][g2] = (next_dp[new_g1][g2] + dp[g1][g2]) % MOD;
                    
                    int new_g2 = std::gcd(g2, num);
                    next_dp[g1][new_g2] = (next_dp[g1][new_g2] + dp[g1][g2]) % MOD;
                }
            }
            dp = std::move(next_dp);
        }
        
        long long total_pairs = 0;
        for (int g = 1; g <= max_val; ++g) {
            total_pairs = (total_pairs + dp[g][g]) % MOD;
        }
        
        return total_pairs;
    }
};