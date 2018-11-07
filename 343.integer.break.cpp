class Solution {
public:
    int integerBreak(int n) {
        vector<int> best(2);
        best[1] = 1;
        for(int i = 2; i < n; ++i) {
            int bestSoFar = i;
            for(int j = 1; j < i; ++j) {
                int score = best[i - j]*j;
                if(score > bestSoFar) {
                    bestSoFar = score;
                }
            }
            best.push_back(bestSoFar);
        }
        int bestSoFar = 1;
        for(int j = 1; j < n; ++j) {
            int score = best[n - j]*j;
            if(score > bestSoFar) {
                bestSoFar = score;
            }
        }
        return bestSoFar;
    }
};
