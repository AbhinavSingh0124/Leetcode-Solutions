class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int sum = nums[0];
        
        // Step 1: Find the longest sequential prefix sum
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break;
            }
        }
        
        // Step 2: Store elements in a hash set for O(1) lookups
        unordered_set<int> st(nums.begin(), nums.end());
        
        // Step 3: Find the smallest missing integer >= sum
        while (st.count(sum)) {
            sum++;
        }
        
        return sum;
    }
};