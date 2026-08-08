#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        long long MOD = 1e9 + 7;
        
        // Helper Kadane's algorithm to find max subarray sum for a given array
        auto kadane = [](const vector<int>& v) {
            long long max_so_far = 0, current_max = 0;
            for (int x : v) {
                current_max = max((long long)x, current_max + x);
                max_so_far = max(max_so_far, current_max);
            }
            return max_so_far;
        };

        if (k == 1) {
            return kadane(arr) % MOD;
        }

        // Create arr concatenated twice
        vector<int> double_arr = arr;
        double_arr.insert(double_arr.end(), arr.begin(), arr.end());
        
        long long max_two_sum = kadane(double_arr);
        long long total_sum = accumulate(arr.begin(), arr.end(), 0LL);

        if (total_sum > 0) {
            return (max_two_sum + (k - 2) * total_sum) % MOD;
        } else {
            return max_two_sum % MOD;
        }
    }
};