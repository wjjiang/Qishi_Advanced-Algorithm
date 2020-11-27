class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        // Use multiset to save sum[i] = nums[0] + .. + nums[i]
        multiset<long long> mSet;
        // initialize result
        int res = 0;
        // initialize 3 parameters
        long long sum = 0;
        
        // loop each element
        // Step 1: insert 0 in mSet to start with lower_bound and upper_bound comparison
        mSet.emplace(0);
        // Step 2: loop all the elements in nums vector
        for (int num : nums) {
            sum += num;
            res += distance(mSet.lower_bound(sum-upper), mSet.upper_bound(sum-lower));
            mSet.emplace(sum);
        }
        
        // return
        return res;
    }
};