#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_val = *max_element(nums.begin(), nums.end());
        vector<long long> count(max_val + 1, 0);
        
        for (int num : nums) {
            count[num]++;
        }
        
        vector<long long> gcd_pairs(max_val + 1, 0);
        
        for (int i = max_val; i >= 1; --i) {
            long long multiples = 0;
            for (int j = i; j <= max_val; j += i) {
                multiples += count[j];
            }
            
            long long total_pairs = (multiples * (multiples - 1)) / 2;
            
            for (int j = 2 * i; j <= max_val; j += i) {
                total_pairs -= gcd_pairs[j];
            }
            
            gcd_pairs[i] = total_pairs;
        }
        
        vector<long long> prefix_sums(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            prefix_sums[i] = prefix_sums[i - 1] + gcd_pairs[i];
        }
        
        vector<int> answer;
        answer.reserve(queries.size());
        
        for (long long q : queries) {
            auto it = upper_bound(prefix_sums.begin(), prefix_sums.end(), q);
            answer.push_back(distance(prefix_sums.begin(), it));
        }
        
        return answer;
    }
};