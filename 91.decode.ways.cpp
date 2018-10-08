class Solution {
public:
    int numDecodings(string s) {
        if(s[0] == '0') return 0;

        // Dynamic programing esque
        // numDecodings(s) = numDecodings(s[1:]) + numDecodings(s[2:]) if s[0] == '1' or (s[0] == '2' and s[1] < '7')
        // Loop invariant:
        // n2 = numDecodings(s[i + 2:])
        // n1 = numDecodings(s[i + 1:])
        int n2 = 1; // 1 way to decode empty string
        int n1 = s[s.size() - 1] == '0' ? 0 : 1; // 1 way to decode s[len(s) - 1:]
        for(int i = s.size() - 2; i >= 0; --i) {
            int n0 = n1;
            if(s[i] == '0') {
                if(s[i - 1] > '2' || s[i - 1] < '1') return 0;
                n1 = 0;
            } else if(s[i] == '1' || (s[i] == '2' && s[i + 1] < '7')) {
                n0 += n2;
            }
            n2 = n1;
            n1 = n0;
        }
        return n1;
    }
};

/* Test cases:
"0"
"1"
"2"
"12"
"21"
"31"
"226"
"227"
"271241"
"10"
"101"
"1001"
"100"
"20"
"202"
*/
