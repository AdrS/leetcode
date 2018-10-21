class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // opt[i] = minimum number of coins required to make change for i
        vector<int> opt;
        opt.push_back(0);
        for(int i = 1; i <= amount; ++i) {
            int best = INT_MAX;
            for(auto c : coins) {
                if(c < i) {
                    if(opt[i - c] != INT_MAX && opt[i - c] + 1 < best) {
                        best = opt[i - c] + 1;
                    }
                } else if(c == i) {
                    best = 1;
                    break;
                }
            }
            opt.push_back(best);
        }
        int best = opt.back();
        if(best == INT_MAX) return -1;
        return best;
    }
};

// TODO: DFS is faster than DP because ammount might be large
/*
static int fast = []() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); return 0;}();


class Solution {
public:
	void DFS(int &Ans, vector<int> &Coin, int Target, int i, int Count) {
		if (i < 0) return;
		if (Target % Coin[i] == 0) {
			Ans = min(Ans, Count + Target / Coin[i]);
			return;
		}
		if (Count + Target / Coin[i] < Ans - 1) { // Pruing
			for (int k = Target / Coin[i]; k >= 0; k--) {
				DFS(Ans, Coin, Target - k * Coin[i], i - 1, Count + k);
			}
		} 
	}
	int coinChange(vector<int>&Coin, int N) {
		int Ans = INT_MAX;
		sort(Coin.begin(), Coin.end());
		DFS(Ans, Coin, N, Coin.size() - 1, 0);
		return (Ans == INT_MAX) ? -1 : Ans;
	}
};
*/
