class Solution {
private:
    int res = 0;
    array<int, 2> bit = array<int, 2>{0, 0};
    
public:
    int totalHammingDistance(vector<int>& nums) {
        // corner case
        if (nums.size() < 2)
            return res;
        // normal case
        else {
            for (int zeros; zeros != nums.size(); bit[0] = 0, bit[1] = 0) {
                zeros = 0;
                for (int& num : nums) {
                    if (!num)
                        zeros++;
                    bit[num % 2]++;
                    num >>= 1;
                }
                res += bit[0] * bit[1];
            }
            return res;
        }
    }
};