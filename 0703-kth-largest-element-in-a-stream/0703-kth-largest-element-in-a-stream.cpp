#include <vector>
#include <queue>

class KthLargest {
private:
    int k;
    // Min-heap to store the k largest elements
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

public:
    KthLargest(int k, std::vector<int>& nums) : k(k) {
        for (int num : nums) {
            add(num);
        }
    }
    
    int add(int val) {
        minHeap.push(val);
        
        // Keep only the k largest elements in the heap
        if (minHeap.size() > k) {
            minHeap.pop();
        }
        
        return minHeap.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */