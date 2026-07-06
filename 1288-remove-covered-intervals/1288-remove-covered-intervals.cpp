class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1];
            }
            return a[0] < b[0]; 
        });

        int remaining = 0;
        int maxEnd = 0;

        for (const auto& curr : intervals) {
            if (curr[1] > maxEnd) {
                remaining++;
                maxEnd = curr[1];
            }
        }

        return remaining;
    }
};