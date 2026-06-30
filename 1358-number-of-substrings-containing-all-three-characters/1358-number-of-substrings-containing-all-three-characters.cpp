class Solution {
public:
    int numberOfSubstrings(string s) {
        // Track the last seen index of each character
        int lastPos[3] = {-1, -1, -1};
        int count = 0;
        int n = s.length();
        
        for (int i = 0; i < n; ++i) {
            // Update the position of the current character
            lastPos[s[i] - 'a'] = i;
            
            // If we have seen all three characters at least once
            if (lastPos[0] != -1 && lastPos[1] != -1 && lastPos[2] != -1) {
                // The smallest index among the last seen positions of 'a', 'b', 'c'
                // marks the end of the shortest valid prefix ending at i.
                int minIdx = min({lastPos[0], lastPos[1], lastPos[2]});
                
                // Any substring starting from index 0 up to minIdx and ending at i is valid.
                count += (minIdx + 1);
            }
        }
        
        return count;
    }
};