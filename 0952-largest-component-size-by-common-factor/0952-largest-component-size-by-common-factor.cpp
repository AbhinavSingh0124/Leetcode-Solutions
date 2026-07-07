class DisjointSet {
public:
    vector<int> parent;
    
    DisjointSet(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]);
    }
    
    void unionNodes(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        if (rootI != rootJ) {
            parent[rootI] = rootJ;
        }
    }
};

class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        int maxVal = *max_element(nums.begin(), nums.end());
        DisjointSet dsu(maxVal + 1);
        
        for (int num : nums) {
            for (int factor = 2; factor * factor <= num; ++factor) {
                if (num % factor == 0) {
                    dsu.unionNodes(num, factor);
                    dsu.unionNodes(num, num / factor);
                }
            }
        }
        
        unordered_map<int, int> componentSizes;
        int maxComponent = 0;
        
        for (int num : nums) {
            int root = dsu.find(num);
            componentSizes[root]++;
            maxComponent = max(maxComponent, componentSizes[root]);
        }
        
        return maxComponent;
    }
};
