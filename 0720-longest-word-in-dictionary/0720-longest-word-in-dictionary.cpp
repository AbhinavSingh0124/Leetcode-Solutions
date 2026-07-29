#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestWord(vector<string>& words) {
        unordered_set<string> dict(words.begin(), words.end());
        
        // Sort words:
        // 1. By length in descending order
        // 2. Lexicographically in ascending order if lengths are equal
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            if (a.length() != b.length()) {
                return a.length() > b.length();
            }
            return a < b;
        });
        
        for (const string& word : words) {
            bool valid = true;
            string prefix = "";
            
            // Check if all prefixes exist in the dictionary
            for (int i = 0; i < word.length() - 1; ++i) {
                prefix += word[i];
                if (!dict.count(prefix)) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                return word;
            }
        }
        
        return "";
    }
};