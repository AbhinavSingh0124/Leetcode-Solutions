#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    long long lcm(long long a, long long b) {
        return (a / std::gcd(a, b)) * b;
    }

    long long countValid(long long x, const std::vector<int>& coins) {
        int n = coins.size();
        long long count = 0;

        for (int mask = 1; mask < (1 << n); ++mask) {
            long long currentLcm = 1;
            int bitsSet = 0;

            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    bitsSet++;
                    currentLcm = lcm(currentLcm, coins[i]);
                    if (currentLcm > x) break;
                }
            }

            if (bitsSet % 2 == 1) {
                count += x / currentLcm;
            } else {
                count -= x / currentLcm;
            }
        }

        return count;
    }

    long long findKthSmallest(std::vector<int>& coins, int k) {
        long long low = 1;
        long long high = (long long)*std::min_element(coins.begin(), coins.end()) * k;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (countValid(mid, coins) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};