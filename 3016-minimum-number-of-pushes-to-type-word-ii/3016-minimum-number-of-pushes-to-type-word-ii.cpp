class Solution {
public:
    int minimumPushes(string word) {
        vector<int> freq(26, 0);
        for (char c : word) {
            freq[c - 'a']++;
        }
        
        // Sort frequencies in descending order
        sort(freq.rbegin(), freq.rend());
        
        int totalPushes = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] == 0) break;
            
            // i / 8 determines the press cost:
            // 0..7   -> 1 push
            // 8..15  -> 2 pushes
            // 16..23 -> 3 pushes
            // 24..25 -> 4 pushes
            int pushesPerChar = (i / 8) + 1;
            totalPushes += freq[i] * pushesPerChar;
        }
        
        return totalPushes;
    }
};