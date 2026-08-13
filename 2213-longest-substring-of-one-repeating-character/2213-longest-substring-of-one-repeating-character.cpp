#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int max_len = 0;
    int prefix_len = 0;
    int suffix_len = 0;
    char left_char = 0;
    char right_char = 0;
    int seg_len = 0;
};

class Solution {
private:
    vector<Node> tree;

    Node merge(const Node& left, const Node& right) {
        Node res;
        res.seg_len = left.seg_len + right.seg_len;
        res.left_char = left.left_char;
        res.right_char = right.right_char;

        // Base max length from children
        res.max_len = max(left.max_len, right.max_len);

        // Check if prefix extends into right child
        res.prefix_len = left.prefix_len;
        if (left.prefix_len == left.seg_len && left.right_char == right.left_char) {
            res.prefix_len = left.seg_len + right.prefix_len;
        }

        // Check if suffix extends into left child
        res.suffix_len = right.suffix_len;
        if (right.suffix_len == right.seg_len && left.right_char == right.left_char) {
            res.suffix_len = right.seg_len + left.suffix_len;
        }

        // Check boundary bridge across the middle
        if (left.right_char == right.left_char) {
            res.max_len = max(res.max_len, left.suffix_len + right.prefix_len);
        }

        return res;
    }

    void build(int node, int start, int end, const string& s) {
        if (start == end) {
            tree[node] = {1, 1, 1, s[start], s[start], 1};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid, s);
        build(2 * node + 1, mid + 1, end, s);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, char ch) {
        if (start == end) {
            tree[node] = {1, 1, 1, ch, ch, 1};
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, ch);
        } else {
            update(2 * node + 1, mid + 1, end, idx, ch);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        int k = queryIndices.size();
        tree.resize(4 * n);

        build(1, 0, n - 1, s);

        vector<int> result(k);
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            result[i] = tree[1].max_len;
        }

        return result;
    }
};