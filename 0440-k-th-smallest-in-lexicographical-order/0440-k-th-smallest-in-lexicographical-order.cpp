#include <algorithm>

using namespace std;

class Solution {
private:
    // Counts how many numbers exist in the range [curr, curr + 1) up to n
    long countSteps(long curr, long next, long n) {
        long steps = 0;
        while (curr <= n) {
            steps += min(n + 1, next) - curr;
            curr *= 10;
            next *= 10;
        }
        return steps;
    }

public:
    int findKthNumber(int n, int k) {
        long curr = 1;
        k--; // We start at 1, so we need k - 1 more steps

        while (k > 0) {
            long steps = countSteps(curr, curr + 1, n);
            
            if (steps <= k) {
                // Move to the next right sibling
                k -= steps;
                curr++;
            } else {
                // Go deeper into the first child
                k--;
                curr *= 10;
            }
        }

        return curr;
    }
};