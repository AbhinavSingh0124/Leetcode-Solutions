#include <vector>
#include <algorithm>

using namespace std;

class MyCalendarTwo {
private:
    vector<pair<int, int>> bookings;
    vector<pair<int, int>> overlaps;

public:
    MyCalendarTwo() {
        
    }
    
    bool book(int startTime, int endTime) {
        // 1. Check if the new event conflicts with any double-booked region
        for (const auto& [s, e] : overlaps) {
            if (max(startTime, s) < min(endTime, e)) {
                return false; // Cause a triple booking
            }
        }
        
        // 2. Add new overlap regions created with existing single bookings
        for (const auto& [s, e] : bookings) {
            int overlapStart = max(startTime, s);
            int overlapEnd = min(endTime, e);
            if (overlapStart < overlapEnd) {
                overlaps.push_back({overlapStart, overlapEnd});
            }
        }
        
        // 3. Add the event to single bookings
        bookings.push_back({startTime, endTime});
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(startTime,endTime);
 */