#include <vector>
#include <map>

class SummaryRanges {
private:
    std::map<int, int> intervals; // key: start, value: end

public:
    SummaryRanges() {}
    
    void addNum(int value) {
        auto it = intervals.upper_bound(value);
        bool hasPrev = (it != intervals.begin());
        auto prev_it = hasPrev ? std::prev(it) : intervals.end();
        
        // Case 1: value is already covered by the previous interval
        if (hasPrev && prev_it->second >= value) {
            return;
        }
        
        bool connectPrev = hasPrev && (prev_it->second + 1 == value);
        bool connectNext = (it != intervals.end()) && (it->first == value + 1);
        
        // Case 2: value bridges prev_it and it
        if (connectPrev && connectNext) {
            prev_it->second = it->second;
            intervals.erase(it);
        }
        // Case 3: value extends prev_it to the right
        else if (connectPrev) {
            prev_it->second = value;
        }
        // Case 4: value extends it to the left
        else if (connectNext) {
            int right = it->second;
            intervals.erase(it);
            intervals[value] = right;
        }
        // Case 5: value creates a new isolated interval
        else {
            intervals[value] = value;
        }
    }
    
    std::vector<std::vector<int>> getIntervals() {
        std::vector<std::vector<int>> result;
        result.reserve(intervals.size());
        for (const auto& [start, end] : intervals) {
            result.push_back({start, end});
        }
        return result;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * std::vector<std::vector<int>> param_2 = obj->getIntervals();
 */