#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> num_map;
        
        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            
            // Check if complement exists in the map
            if (num_map.find(complement) != num_map.end()) {
                return {num_map[complement], i};
            }
            
            // Store the index of the current number
            num_map[nums[i]] = i;
        }
        
        return {}; // Default fallback
    }
};