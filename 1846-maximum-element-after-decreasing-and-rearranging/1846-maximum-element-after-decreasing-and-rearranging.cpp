class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        // Step 1: Sort the array to easily manage adjacent differences
        sort(arr.begin(), arr.end());
        
        // Step 2: The first element must always be 1
        arr[0] = 1;
        
        // Step 3: Iterate through the array and ensure the difference rule is satisfied
        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] - arr[i - 1] > 1) {
                arr[i] = arr[i - 1] + 1;
            }
        }
        
        // The last element will hold the maximum possible value
        return arr.back();
    }
};