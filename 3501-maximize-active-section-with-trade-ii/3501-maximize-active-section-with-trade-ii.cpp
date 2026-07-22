#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
    // Structure to represent a contiguous block of '1's
    struct OneSeg {
        int u, v;       // start and end indices of the '1's block
        int L, R;       // start index of the left '0's block, end index of the right '0's block
        int val;        // total potential increase if this block is traded (without query bounds)
    };

    // Segment Tree to perform Range Maximum Queries (RMQ)
    class SegmentTree {
        vector<int> tree;
        int n;
    public:
        SegmentTree(const vector<OneSeg>& ones) {
            n = ones.size();
            if (n > 0) {
                tree.assign(4 * n, 0);
                build(ones, 0, 0, n - 1);
            }
        }
        
        void build(const vector<OneSeg>& ones, int node, int start, int end) {
            if (start == end) {
                tree[node] = ones[start].val;
                return;
            }
            int mid = start + (end - start) / 2;
            build(ones, 2 * node + 1, start, mid);
            build(ones, 2 * node + 2, mid + 1, end);
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
        
        int query(int node, int start, int end, int l, int r) {
            if (r < start || end < l) return 0;
            if (l <= start && end <= r) return tree[node];
            int mid = start + (end - start) / 2;
            int p1 = query(2 * node + 1, start, mid, l, r);
            int p2 = query(2 * node + 2, mid + 1, end, l, r);
            return max(p1, p2);
        }
        
        int query(int l, int r) {
            if (l > r || n == 0) return 0;
            return query(0, 0, n - 1, l, r);
        }
    };

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int total_ones = count(s.begin(), s.end(), '1');
        
        // Group consecutive characters
        struct Group {
            char type;
            int start, end;
        };
        vector<Group> groups;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            groups.push_back({s[i], i, j - 1});
            i = j;
        }
        
        // Extract 1-segments and find their bounding 0-segments
        vector<OneSeg> ones;
        int m = groups.size();
        for (int i = 0; i < m; i++) {
            if (groups[i].type == '1') {
                int u = groups[i].start;
                int v = groups[i].end;
                
                int L = u;
                if (i > 0 && groups[i-1].type == '0') {
                    L = groups[i-1].start;
                }
                
                int R = v;
                if (i + 1 < m && groups[i+1].type == '0') {
                    R = groups[i+1].end;
                }
                
                ones.push_back({u, v, L, R, (u - L) + (R - v)});
            }
        }
        
        SegmentTree st(ones);
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            
            // Binary search to find the first 1-segment strictly bounded on the left
            int idx_start = ones.size();
            int low = 0, high = (int)ones.size() - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (ones[mid].u >= l + 1) {
                    idx_start = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            
            // Binary search to find the last 1-segment strictly bounded on the right
            int idx_end = -1;
            low = 0, high = (int)ones.size() - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (ones[mid].v <= r - 1) {
                    idx_end = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            
            int max_inc = 0;
            if (idx_start <= idx_end) {
                if (idx_start == idx_end) {
                    // Only one valid 1-segment strictly inside the query
                    int i = idx_start;
                    int cur_inc = (ones[i].u - max(l, ones[i].L)) + (min(r, ones[i].R) - ones[i].v);
                    max_inc = max(max_inc, cur_inc);
                } else {
                    // Multiple valid 1-segments
                    int first = idx_start;
                    int last = idx_end;
                    
                    // Edges might be truncated by the query boundaries l and r
                    int inc_first = (ones[first].u - max(l, ones[first].L)) + (ones[first].R - ones[first].v);
                    int inc_last = (ones[last].u - ones[last].L) + (min(r, ones[last].R) - ones[last].v);
                    max_inc = max({max_inc, inc_first, inc_last});
                    
                    // The segments strictly in the middle are fully covered, so we can use the RMQ Segment tree
                    if (first + 1 <= last - 1) {
                        max_inc = max(max_inc, st.query(first + 1, last - 1));
                    }
                }
            }
            
            ans.push_back(total_ones + max_inc);
        }
        
        return ans;
    }
};