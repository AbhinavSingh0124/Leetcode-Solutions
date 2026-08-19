#include <vector>
#include <unordered_map>
#include <cstdlib>

class RandomizedSet {
private:
    std::vector<int> nums;
    std::unordered_map<int, int> valToIdx;

public:
    RandomizedSet() {}
    
    bool insert(int val) {
        if (valToIdx.count(val)) {
            return false;
        }
        valToIdx[val] = nums.size();
        nums.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if (!valToIdx.count(val)) {
            return false;
        }
        
        int idx = valToIdx[val];
        int lastVal = nums.back();
        
        // Move the last element to the index of the element to delete
        nums[idx] = lastVal;
        valToIdx[lastVal] = idx;
        
        // Remove the last element
        nums.pop_back();
        valToIdx.erase(val);
        
        return true;
    }
    
    int getRandom() {
        int randomIndex = std::rand() % nums.size();
        return nums[randomIndex];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */