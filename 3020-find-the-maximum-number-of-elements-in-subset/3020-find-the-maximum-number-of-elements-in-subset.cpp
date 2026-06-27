#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> counts;
        for (int num : nums) {
            counts[num]++;
        }
        
        int max_len = 0;
        
        // Handle the special case for 1
        if (counts.count(1)) {
            int count1 = counts[1];
            if (count1 % 2 == 0) {
                max_len = max(max_len, count1 - 1);
            } else {
                max_len = max(max_len, count1);
            }
        }
        
        // Check for other numbers > 1
        for (auto& [val, count] : counts) {
            if (val == 1) continue;
            
            long long current = val;
            int current_len = 0;
            
            // 1. Take 2 copies of each number as long as they are available
            while (counts.count(current) && counts[current] >= 2) {
                current_len += 2;
                current = current * current; // Move to the next square
            }
            
            // 2. Check if the next square can act as the single peak element
            if (counts.count(current) && counts[current] >= 1) {
                current_len += 1;
            } else {
                // If no peak element exists, the last number we took 2 copies of 
                // must turn into the peak (meaning we can only use 1 copy of it)
                current_len -= 1;
            }
            
            max_len = max(max_len, current_len);
        } // <--- This was the missing brace!
        
        return max_len;
    }
};