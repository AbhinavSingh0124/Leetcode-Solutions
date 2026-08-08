#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        // last[j] stores the largest index in word1 from which 
        // word2[j...] can be matched as a subsequence.
        vector<int> last(m + 1, -1);
        last[m] = n;
        
        int ptr = n - 1;
        for (int j = m - 1; j >= 0; --j) {
            while (ptr >= 0 && word1[ptr] != word2[j]) {
                ptr--;
            }
            last[j] = ptr;
            if (ptr >= 0) ptr--; // Move pointer left for the next character match
        }

        vector<int> ans;
        bool used_change = false;
        int j = 0;

        for (int i = 0; i < n && j < m; ++i) {
            // Option 1: Exact match
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            } 
            // Option 2: Mismatch, but we use our 1 allowed change
            else if (!used_change && last[j + 1] > i) {
                ans.push_back(i);
                used_change = true;
                j++;
            }
        }

        return (ans.size() == m) ? ans : vector<int>();
    }
};