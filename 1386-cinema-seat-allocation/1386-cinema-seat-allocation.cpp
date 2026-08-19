#include <unordered_map>
#include <vector>

class Solution {
public:
    int maxNumberOfFamilies(int n, std::vector<std::vector<int>>& reservedSeats) {
        std::unordered_map<int, int> rowMasks;
        
        // Build bitmask for each modified row
        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];
            if (col >= 2 && col <= 9) {
                rowMasks[row] |= (1 << (col - 2));
            }
        }
        
        // Start by assuming all rows are completely empty (2 families per row)
        int totalGroups = (n - rowMasks.size()) * 2;
        
        // Check rows that have reserved seats
        for (const auto& [row, mask] : rowMasks) {
            bool left = (mask & 0b00001111) == 0;   // seats 2, 3, 4, 5 free
            bool right = (mask & 0b11110000) == 0;  // seats 6, 7, 8, 9 free
            bool middle = (mask & 0b00111100) == 0; // seats 4, 5, 6, 7 free
            
            if (left && right) {
                totalGroups += 2;
            } else if (left || right || middle) {
                totalGroups += 1;
            }
        }
        
        return totalGroups;
    }
};