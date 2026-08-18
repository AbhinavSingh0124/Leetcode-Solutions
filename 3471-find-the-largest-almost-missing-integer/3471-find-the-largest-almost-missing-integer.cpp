class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        // Case 1: k = 1 -> Largest element with frequency 1
        if (k == 1) {
            int ans = -1;
            for (auto& [val, count] : freq) {
                if (count == 1) {
                    ans = max(ans, val);
                }
            }
            return ans;
        }

        // Case 2: k = n -> Largest element in the array
        if (k == n) {
            int ans = -1;
            for (int num : nums) {
                ans = max(ans, num);
            }
            return ans;
        }

        // Case 3: 1 < k < n -> Only endpoints nums[0] or nums[n-1] can be valid
        int ans = -1;
        if (freq[nums[0]] == 1) {
            ans = max(ans, nums[0]);
        }
        if (freq[nums[n - 1]] == 1) {
            ans = max(ans, nums[n - 1]);
        }

        return ans;
    }
};