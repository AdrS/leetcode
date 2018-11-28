class Solution {
    // Converts string to "cannonical" pattern
    // Ie: pattern where first disting char is 0, 2nd unique char is 1, ....
    void str2pat(const string &s, char pat[20]) {
        vector<int> translations(256,-1);
        int numUniqueChars = 0;
        for(int i = 0; i < s.size(); ++i) {
            int j = s[i];
            // If first time we have seen character, assing next value for translation
            if(translations[j] == -1) {
                translations[j] = numUniqueChars++;
            }
            *pat++ = translations[j];
        }
    }
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        char basePat[20];
        char wordPat[20];
        str2pat(pattern, basePat);
        vector<string> results;
        for(auto &w : words) {
            // convert both word and pattern to "standard" for and see if standard forms match
            str2pat(w, wordPat);
            if(memcmp(basePat, wordPat, w.size()) == 0) {
                results.push_back(w);
            }
        }
        return results;
    }
};
