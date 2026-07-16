#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    long long gcdSum(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> prefixGcd(n);
        
        int current_max = 0;
        for (int i = 0; i < n; ++i) {
            current_max = std::max(current_max, nums[i]);
            prefixGcd[i] = std::gcd(nums[i], current_max);
        }
        
        std::sort(prefixGcd.begin(), prefixGcd.end());
        
        long long total_sum = 0;
        int left = 0;
        int right = n - 1;
        
        while (left < right) {
            total_sum += std::gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }
        
        return total_sum;
    }
};