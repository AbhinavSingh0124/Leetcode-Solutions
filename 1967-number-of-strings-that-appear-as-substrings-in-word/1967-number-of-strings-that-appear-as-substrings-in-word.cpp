class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int count = 0;
        
        for (const string& p : patterns) {
            // std::string::find returns std::string::npos if the substring is not found
            if (word.find(p) != string::npos) {
                count++;
            }
        }
        
        return count;
    }
};