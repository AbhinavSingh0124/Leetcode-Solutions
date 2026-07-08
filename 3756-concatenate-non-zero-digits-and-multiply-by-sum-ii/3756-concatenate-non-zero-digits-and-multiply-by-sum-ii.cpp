#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int m = s.length();
        long long MOD = 1e9 + 7;

        vector<int> digits;
        vector<int> original_idx;
        vector<int> next_nonzero(m, -1);
        
        for (int i = 0; i < m; ++i) {
            if (s[i] != '0') {
                digits.push_back(s[i] - '0');
                original_idx.push_back(i);
            }
        }

        int n = digits.size();
        if (n == 0) {
            return vector<int>(queries.size(), 0);
        }

        int digit_ptr = 0;
        for (int i = 0; i < m; ++i) {
            while (digit_ptr < n && original_idx[digit_ptr] < i) {
                digit_ptr++;
            }
            if (digit_ptr < n) {
                next_nonzero[i] = digit_ptr;
            } else {
                next_nonzero[i] = -1;
            }
        }

        vector<long long> prefix_sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + digits[i];
        }

        vector<long long> prefix_num(n + 1, 0);
        vector<long long> pow10(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            prefix_num[i + 1] = (prefix_num[i] * 10 + digits[i]) % MOD;
            pow10[i + 1] = (pow10[i] * 10) % MOD;
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];

            int idx_start = next_nonzero[l];
            if (idx_start == -1 || original_idx[idx_start] > r) {
                answer.push_back(0);
                continue;
            }

            int low = idx_start, high = n - 1, idx_end = idx_start;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (original_idx[mid] <= r) {
                    idx_end = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            int len = idx_end - idx_start + 1;

            long long x = (prefix_num[idx_end + 1] - (prefix_num[idx_start] * pow10[len]) % MOD + MOD) % MOD;
            long long sum = prefix_sum[idx_end + 1] - prefix_sum[idx_start];

            long long res = (x * (sum % MOD)) % MOD;
            answer.push_back(res);
        }

        return answer;
    }
};