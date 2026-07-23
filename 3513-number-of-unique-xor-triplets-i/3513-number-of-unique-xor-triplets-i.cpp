class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n;
        
        int k = std::__lg(n) + 1; // Number of bits to represent n
        return 1 << k;
    }
};