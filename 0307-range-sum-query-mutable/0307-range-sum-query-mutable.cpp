#include <vector>

class NumArray {
private:
    std::vector<int> tree;
    std::vector<int> nums;
    int n;

    // Helper: Adds delta to the element at 1-based index `i`
    void add(int i, int delta) {
        for (; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }

    // Helper: Returns prefix sum from index 1 to 1-based index `i`
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }

public:
    NumArray(std::vector<int>& nums) : nums(nums), n(nums.size()) {
        tree.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            add(i + 1, nums[i]);
        }
    }
    
    void update(int index, int val) {
        int delta = val - nums[index];
        nums[index] = val; // Keep track of current array values
        add(index + 1, delta);
    }
    
    int sumRange(int left, int right) {
        return query(right + 1) - query(left);
    }
};
