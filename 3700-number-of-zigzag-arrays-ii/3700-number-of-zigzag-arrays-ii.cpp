#include <vector>
#include <numeric>

using namespace std;

class Solution {
    long long MOD = 1e9 + 7;

    // Helper function to multiply two matrices
    vector<vector<long long>> multiply(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
        int size = A.size();
        vector<vector<long long>> C(size, vector<long long>(size, 0));
        for (int i = 0; i < size; ++i) {
            for (int k = 0; k < size; ++k) {
                if (A[i][k] == 0) continue;
                for (int j = 0; j < size; ++j) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    // Helper function for fast matrix exponentiation
    vector<vector<long long>> power(vector<vector<long long>> A, long long p) {
        int size = A.size();
        vector<vector<long long>> res(size, vector<long long>(size, 0));
        for (int i = 0; i < size; ++i) res[i][i] = 1; // Identity matrix

        while (p > 0) {
            if (p & 1) res = multiply(res, A);
            A = multiply(A, A);
            p >>= 1;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        int size = 2 * m;

        // Transition matrix T
        vector<vector<long long>> T(size, vector<long long>(size, 0));

        // States 0 to m-1: (UP, x)
        // States m to 2m-1: (DOWN, x)
        for (int x = 0; x < m; ++x) {
            // From (UP, x) -> can transition to (DOWN, y) where y > x
            for (int y = x + 1; y < m; ++y) {
                T[m + y][x] = 1;
            }
            // From (DOWN, x) -> can transition to (UP, y) where y < x
            for (int y = 0; y < x; ++y) {
                T[y][m + x] = 1;
            }
        }

        // Exponentiate transition matrix to power (n - 1)
        vector<vector<long long>> Tn = power(T, n - 1);

        // Initial vector V1 filled with 1s
        long long total_arrays = 0;
        for (int i = 0; i < size; ++i) {
            long long row_sum = 0;
            for (int j = 0; j < size; ++j) {
                row_sum = (row_sum + Tn[i][j]) % MOD;
            }
            total_arrays = (total_arrays + row_sum) % MOD;
        }

        return total_arrays;
    }
};