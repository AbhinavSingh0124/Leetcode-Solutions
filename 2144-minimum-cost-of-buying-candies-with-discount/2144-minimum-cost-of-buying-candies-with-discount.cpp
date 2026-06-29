#include <vector>
#include <algorithm>

class Solution {
public:
    int minimumCost(std::vector<int>& cost) {
        // Sort the candies in descending order
        std::sort(cost.rbegin(), cost.rend());
        
        int totalCost = 0;
        
        // Loop through the sorted array
        for (int i = 0; i < cost.size(); i++) {
            // Every 3rd candy (index 2, 5, 8, etc.) is free!
            // So we only pay if (i + 1) % 3 != 0
            if ((i + 1) % 3 != 0) {
                totalCost += cost[i];
            }
        }
        
        return totalCost;
    }
};