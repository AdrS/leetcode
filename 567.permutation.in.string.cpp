class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if(s1.size() > s2.size()) {
            return false;
        }

        // Count frequencies of each letter in s1
        vector<int> s1freq(26, 0);
        for(auto c : s1) {
            s1freq[c - 'a']++;
        }

        // Keep track of letter frequencies for a sliding window of size len(s1) in s2
        vector<int> s2windowfreq(26, 0);
        
        int right = 0;
        while(right < s1.size()) {
            s2windowfreq[s2[right++] - 'a']++;
        }
        // count number of characters that appear the same number of times
        // in s1 and the current window of s2
        int matches = 0;
        for(int i = 0; i < 26; ++i) {
            if(s1freq[i] == s2windowfreq[i]) {
                ++matches;
            }
        }

        int left = 0;
        while(matches != 26 && right < s2.size()) {
            // slide window over
            int rc = s2[right] - 'a';
            int lc = s2[left] - 'a';
            // if s2[right] == s2[left] then frequencies do not change
            if(rc != lc) {
                if(s2windowfreq[rc] == s1freq[rc]) {
                    --matches;
                }
                if(s2windowfreq[lc] == s1freq[lc]) {
                    --matches;
                }
                s2windowfreq[rc]++;
                s2windowfreq[lc]--;
                if(s2windowfreq[rc] == s1freq[rc]) {
                    ++matches;
                }
                if(s2windowfreq[lc] == s1freq[lc]) {
                    ++matches;
                }
            }

            ++left;
            ++right;
        }
        return matches == 26;
    }
};
// 4ms, 100th percentile
