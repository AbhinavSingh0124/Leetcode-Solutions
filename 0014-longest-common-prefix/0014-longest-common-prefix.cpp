class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        // If the input vector is empty, return an empty string
        if (strs.empty()) return "";
        
        // Sort the strings alphabetically
        sort(strs.begin(), strs.end());
        
        // Compare the first and the last string
        string first = strs[0];
        string last = strs[strs.size() - 1];
        string result = "";
        
        for (int i = 0; i < first.length(); i++) {
            // If characters match, add to result; otherwise, stop
            if (first[i] == last[i]) {
                result += first[i];
            } else {
                break;
            }
        }
        
        return result;
    }
};