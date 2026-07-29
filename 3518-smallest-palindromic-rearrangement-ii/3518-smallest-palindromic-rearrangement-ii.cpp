#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function to calculate nCr capped at 'cap'
    long long nCr(int n, int r, long long cap) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n - r) r = n - r;
        
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            res = res * (n - r + i) / i;
            if (res > cap) return cap;
        }
        return res;
    }

    // Computes multinomial permutations of remaining character counts
    long long countPermutations(const vector<int>& cnt, long long cap) {
        long long total_perms = 1;
        int rem = 0;
        for (int c : cnt) rem += c;

        for (int c : cnt) {
            if (c > 0) {
                long long ways = nCr(rem, c, cap);
                if (total_perms == 0 || cap / total_perms < ways) {
                    return cap;
                }
                total_perms *= ways;
                rem -= c;
            }
        }
        return total_perms;
    }

public:
    string smallestPalindrome(string s, int k) {
        int n = s.length();
        int m = n / 2;

        // Count frequencies of the first half of the palindrome
        vector<int> cnt(26, 0);
        for (int i = 0; i < m; ++i) {
            cnt[s[i] - 'a']++;
        }

        // Check if total possible permutations is less than k
        long long total = countPermutations(cnt, k);
        if (total < k) return "";

        string half = "";
        long long current_k = k;

        // Build the first half character by character
        for (int i = 0; i < m; ++i) {
            for (int c = 0; c < 26; ++c) {
                if (cnt[c] == 0) continue;

                // Try placing character 'a' + c
                cnt[c]--;
                long long perms = countPermutations(cnt, current_k);

                if (perms >= current_k) {
                    half += (char)('a' + c);
                    break; // Position i fixed, move to position i + 1
                } else {
                    current_k -= perms;
                    cnt[c]++; // Backtrack and try next character
                }
            }
        }

        // Reconstruct full palindrome
        string res = half;
        if (n % 2 != 0) {
            res += s[m]; // Add middle character
        }
        string rev_half = half;
        reverse(rev_half.begin(), rev_half.end());
        res += rev_half;

        return res;
    }
};