#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    long long solveOneWay(const vector<int>& firstStart, const vector<int>& firstDuration,
                          const vector<int>& secondStart, const vector<int>& secondDuration) {
        int n = firstStart.size();
        int m = secondStart.size();
        
        // Pair up second rides and sort them by start time
        vector<pair<int, int>> secondRides(m);
        for (int i = 0; i < m; ++i) {
            secondRides[i] = {secondStart[i], secondDuration[i]};
        }
        sort(secondRides.begin(), secondRides.end());
        
        // prefMinDur[i] = min duration among secondRides[0...i]
        vector<int> prefMinDur(m);
        prefMinDur[0] = secondRides[0].second;
        for (int i = 1; i < m; ++i) {
            prefMinDur[i] = min(prefMinDur[i - 1], secondRides[i].second);
        }
        
        // suffMinFinish[i] = min (start + duration) among secondRides[i...m-1]
        vector<long long> suffMinFinish(m);
        suffMinFinish[m - 1] = (long long)secondRides[m - 1].first + secondRides[m - 1].second;
        for (int i = m - 2; i >= 0; --i) {
            suffMinFinish[i] = min(suffMinFinish[i + 1], (long long)secondRides[i].first + secondRides[i].second);
        }
        
        long long minTotalFinish = LLONG_MAX;
        
        // For each ride in the first category
        for (int i = 0; i < n; ++i) {
            long long finish1 = (long long)firstStart[i] + firstDuration[i];
            
            // Binary search to find the first second-category ride that opens STRICTLY AFTER finish1
            auto it = upper_bound(secondRides.begin(), secondRides.end(), make_pair((int)finish1, INT_MAX));
            int idx = distance(secondRides.begin(), it);
            
            // Case 1: Rides in second category that open at or before finish1 (indices 0 to idx-1)
            if (idx > 0) {
                long long currentFinish = finish1 + prefMinDur[idx - 1];
                minTotalFinish = min(minTotalFinish, currentFinish);
            }
            
            // Case 2: Rides in second category that open after finish1 (indices idx to m-1)
            if (idx < m) {
                long long currentFinish = suffMinFinish[idx];
                minTotalFinish = min(minTotalFinish, currentFinish);
            }
        }
        
        return minTotalFinish;
    }

public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, 
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        
        // Strategy 1: Land ride first, then Water ride
        long long opt1 = solveOneWay(landStartTime, landDuration, waterStartTime, waterDuration);
        
        // Strategy 2: Water ride first, then Land ride
        long long opt2 = solveOneWay(waterStartTime, waterDuration, landStartTime, landDuration);
        
        return min(opt1, opt2);
    }
};