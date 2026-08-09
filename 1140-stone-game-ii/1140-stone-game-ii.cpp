#include <vector>
#include <algorithm>
#include <numeric>

class Solution {
public:
    int stoneGameII(std::vector<int>& piles) {
        int n = piles.size();
        std::vector<int> suffixSum(n);
        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        // dp[i][M] stores max stones starting at index i with current M
        std::vector<std::vector<int>> memo(n, std::vector<int>(n + 1, 0));

        auto dp = [&](auto& self, int i, int M) -> int {
            if (i >= n) return 0;
            // If current player can take all remaining piles
            if (i + 2 * M >= n) return suffixSum[i];
            if (memo[i][M] != 0) return memo[i][M];

            int maxStones = 0;
            for (int X = 1; X <= 2 * M; ++X) {
                int nextM = std::max(M, X);
                int opponentStones = self(self, i + X, nextM);
                maxStones = std::max(maxStones, suffixSum[i] - opponentStones);
            }

            return memo[i][M] = maxStones;
        };

        return dp(dp, 0, 1);
    }
};