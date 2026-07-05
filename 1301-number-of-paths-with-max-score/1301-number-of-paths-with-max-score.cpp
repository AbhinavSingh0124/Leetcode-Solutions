#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;
        
        // dp[r][c] will store a pair: {max_score, path_count}
        // Initialize with {-1, 0} to represent unreachable cells
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {-1, 0}));
        
        // Base case: The starting point 'E' at (0, 0)
        dp[0][0] = {0, 1};
        
        // Directions to look back: Up, Left, Up-Left Diagonal
        int dirs[3][2] = {{-1, 0}, {0, -1}, {-1, -1}};
        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                // Skip the starting point or obstacles
                if ((r == 0 && c == 0) || board[r][c] == 'X') {
                    continue;
                }
                
                // Determine current cell's numeric value
                int current_val = 0;
                if (isdigit(board[r][c])) {
                    current_val = board[r][c] - '0';
                }
                
                int max_prev_score = -1;
                int total_paths = 0;
                
                // Check the three potential incoming directions
                for (int i = 0; i < 3; ++i) {
                    int prev_r = r + dirs[i][0];
                    int prev_c = c + dirs[i][1];
                    
                    if (prev_r >= 0 && prev_r < n && prev_c >= 0 && prev_c < n) {
                        int prev_score = dp[prev_r][prev_c].first;
                        int prev_paths = dp[prev_r][prev_c].second;
                        
                        // If the neighbor is reachable
                        if (prev_score != -1) {
                            if (prev_score > max_prev_score) {
                                max_prev_score = prev_score;
                                total_paths = prev_paths;
                            } else if (prev_score == max_prev_score) {
                                total_paths = (total_paths + prev_paths) % MOD;
                            }
                        }
                    }
                }
                
                // If at least one valid incoming path exists
                if (max_prev_score != -1) {
                    dp[r][c] = {max_prev_score + current_val, total_paths};
                }
            }
        }
        
        // The result is stored at the bottom-right corner 'S' at (n-1, n-1)
        int final_score = dp[n - 1][n - 1].first;
        int final_paths = dp[n - 1][n - 1].second;
        
        if (final_score == -1) {
            return {0, 0};
        }
        return {final_score, final_paths};
    }
    
};