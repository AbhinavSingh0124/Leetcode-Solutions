class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        unordered_set<int> present(nums.begin(), nums.end());
        int min_val = *min_element(nums.begin(), nums.end());
        int max_val = *max_element(nums.begin(), nums.end());
        
        vector<int> result;
        for (int i = min_val; i <= max_val; ++i) {
            if (!present.count(i)) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};