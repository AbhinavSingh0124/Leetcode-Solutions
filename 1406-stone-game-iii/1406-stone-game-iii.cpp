#include <vector>
#include <string>
#include <algorithm>
#include <climits>

class Solution {
public:
    std::string stoneGameIII(std::vector<int>& stoneValue) {
        int n = stoneValue.size();
        // dp[i] stores the score difference for the player whose turn it is at index i
        // We only need the last 3 computed states to optimize space.
        std::vector<int> dp(4, 0); 

        for (int i = n - 1; i >= 0; --i) {
            int maxDiff = INT_MIN;
            int takeSum = 0;

            for (int k = 0; k < 3 && i + k < n; ++k) {
                takeSum += stoneValue[i + k];
                int nextDiff = dp[(i + k + 1) % 4];
                maxDiff = std::max(maxDiff, takeSum - nextDiff);
            }

            dp[i % 4] = maxDiff;
        }

        int scoreDiff = dp[0];
        if (scoreDiff > 0) return "Alice";
        if (scoreDiff < 0) return "Bob";
        return "Tie";
    }
};