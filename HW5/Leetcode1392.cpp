class Solution {
public:
    string longestPrefix(string s) {
        // step 1. define partial match table
        vector<int> pmt(s.size());
        // step 2. loop i based on j
        int j = 0;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[j])
                pmt[i] = ++j;
            else if (j > 0) {
                j = pmt[j - 1];
                i--;
            }
        }
        // step 3. truncate string
        return s.substr(0, j);
    }
};