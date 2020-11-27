class Solution {
private:
    // Basic idea: modify merge sort algorithm to track the swapped elements
    void merge_countSmaller(vector<int>& indices, int first, int last,
                            vector<int>& results, vector<int>& nums) {
        int count = last - first;
        if (count > 1) {
            int mid = first + count / 2;
            // Recursively call to merge count
            merge_countSmaller(indices, first, mid, results, nums);
            merge_countSmaller(indices, mid, last, results, nums);
            // create temporary vector
            vector<int> tmp;
            tmp.reserve(count);
            
            // Step 1 of merge sort: split vector into 2 halves
            int idx1 = first;
            int idx2 = mid;
            // record the # of swaps
            int semicount = 0;
            
            // Step 2: loop current 2 halves
            while ((idx1 < mid) || (idx2 < last)) {
                // Case 2.1: reach corners
                if ((idx2 == last) || ((idx1 < mid) && (nums[indices[idx1]] <= nums[indices[idx2]]))) {
                    tmp.push_back(indices[idx1]);
                    results[indices[idx1]] += semicount;
                    ++idx1;
                }
                // Case 2.2: not reaching corners
                else {
                    tmp.push_back(indices[idx2]);
                    ++semicount;
                    ++idx2;
                }
            }
            
            // Advanced technique to copy tmp into indices: move will delete elements in tmp
            move(tmp.begin(), tmp.end(), indices.begin()+first);
        }
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> results(nums.size());
        vector<int> indices(nums.size());
        // create increasing sequence from 0: (0, 1, 2, 3, ...)
        iota(indices.begin(), indices.end(), 0);
        // call merge_count function to create result
        merge_countSmaller(indices, 0, nums.size(), results, nums);
        // return
        return results;
    }
};