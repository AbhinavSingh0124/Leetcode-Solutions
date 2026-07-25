#include <string>
#include <algorithm>

class Solution {
public:
    int maxProduct(int n) {
        std::string s = std::to_string(n);
        std::sort(s.rbegin(), s.rend()); // Sort digits in descending order
        
        int first_max = s[0] - '0';
        int second_max = s[1] - '0';
        
        return first_max * second_max;
    }
};