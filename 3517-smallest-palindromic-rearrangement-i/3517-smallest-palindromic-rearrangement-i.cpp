class Solution {
public:
    string smallestPalindrome(string s) {
        int n = s.length();
        int half_len = n / 2;
        
        // Extract and sort the first half
        string half = s.substr(0, half_len);
        sort(half.begin(), half.end());
        
        // Reconstruct the palindrome
        string result = half;
        if (n % 2 != 0) {
            result += s[half_len]; // Append middle character for odd lengths
        }
        
        // Append the reversed first half
        string right_half = half;
        reverse(right_half.begin(), right_half.end());
        result += right_half;
        
        return result;
    }
};