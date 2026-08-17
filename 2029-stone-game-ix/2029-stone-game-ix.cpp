class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        vector<int> cnt(3, 0);
        for (int stone : stones) {
            cnt[stone % 3]++;
        }

        if (cnt[0] % 2 == 0) {
            // Even zeros: Alice needs both remainder 1 and 2 to be available
            return cnt[1] >= 1 && cnt[2] >= 1;
        } else {
            // Odd zeros: Alice wins if the difference between count of 1s and 2s is > 2
            return abs(cnt[1] - cnt[2]) > 2;
        }
    }
};