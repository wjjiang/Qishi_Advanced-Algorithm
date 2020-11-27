class Solution {
public:
    string shortestPalindrome(string s) {
        // step 1. generate reversed string
        string s_rev = s;
        reverse(s_rev.begin(), s_rev.end());
        // step 2. combine s w/ reversed s, adding a separate character in between
        string target = s + '#' + s_rev;
        // step 3. initialize partial-match table
        vector<int> pmt(target.size());
        // step 4. loop to update based on KMT algorithm
        for (int i = 1; i < target.size(); i++) {
            int j = pmt[i - 1];
            while (j && target[i] != target[j])
                j = pmt[j - 1];
            if (target[i] == target[j])
                j++;
            pmt[i] = j;
        }
        // step 5. return truncated string
        return s_rev.substr(0, s.size() - pmt[target.size() - 1]) + s;
    }
};