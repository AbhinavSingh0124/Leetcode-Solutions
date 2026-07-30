class Solution {
public:
    int minimumPushes(string word) {
        int n = word.length();
        int pushes = 0;
        
        if (n <= 8) {
            pushes = n * 1;
        } else if (n <= 16) {
            pushes = 8 * 1 + (n - 8) * 2;
        } else if (n <= 24) {
            pushes = 8 * 1 + 8 * 2 + (n - 16) * 3;
        } else {
            pushes = 8 * 1 + 8 * 2 + 8 * 3 + (n - 24) * 4;
        }
        
        return pushes;
    }
};