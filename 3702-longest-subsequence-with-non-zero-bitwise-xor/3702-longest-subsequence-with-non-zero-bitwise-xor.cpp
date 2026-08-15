class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int totalXor = 0;
        bool hasNonZero = false;

        for (int x : nums) {
            totalXor ^= x;
            if (x != 0) {
                hasNonZero = true;
            }
        }

        if (totalXor != 0) {
            return nums.size();
        }

        return hasNonZero ? nums.size() - 1 : 0;
    }
};