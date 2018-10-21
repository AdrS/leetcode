class Solution {
public:
    int checkRecord(int n) {
        int M = 1000000007;
        // No absense used:
        // number of records n - 1 that don't end in late
        int nal0 = 1;
        // number of records n - 1 that end with single late
        int nal1 = 0;
        // number of records n - 1 that end with two consecutive lates
        int nal2 = 0;

        // Absense used:
        // number of records n - 1 that don't end in late
        int yal0 = 0;
        // number of records n - 1 that end with single late
        int yal1 = 0;
        // number of records n - 1 that end with two consecutive lates
        int yal2 = 0;
        while(n-- > 0) {
            // No absense does not end in late -> no absence || present
            int newnal0 = (((nal0 + nal1) % M) + nal2) % M;
            // No absense ends in a single late -> no absense does not end in late || late
            int newnal1 = nal0;
            // no absense ends in two lates -> no absense ends in a late single late || late
            int newnal2 = nal1;
            
            // absense used does not end in late -> absense used || present or no absense || absense
            int newyal0 = (((yal0 + yal1) % M + yal2) % M + newnal0) % M;
            // absense used ends in single late -> absense used does not end in late || late
            int newyal1 = yal0;
            // absense used ends in two lates -> absense used end in single late || late
            int newyal2 = yal1;
            nal0 = newnal0;
            nal1 = newnal1;
            nal2 = newnal2;
            yal0 = newyal0;
            yal1 = newyal1;
            yal2 = newyal2;
        }
        return (((((nal0 + nal1) % M + nal2) % M + yal0) % M + yal1) % M + yal2) % M;
    }
};
