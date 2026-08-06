class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        // Target is unreachable or sum cannot be split evenly
        if (abs(target) > totalSum || (target + totalSum) % 2 != 0) {
            return 0;
        }

        int subsetSum = (target + totalSum) / 2;

        // DP array to store subset sum counts
        vector<int> dp(subsetSum + 1, 0);
        dp[0] = 1; // 1 way to make sum 0 (empty subset)

        for (int num : nums) {
            for (int j = subsetSum; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }

        return dp[subsetSum];
    }
};