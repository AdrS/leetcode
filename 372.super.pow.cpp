class Solution {
    // compute a^b mod m using square and multiply
    static int pow(int a, int b, int m) {
        int r = 1;
        // loop invariant (starting from 0): at start of ith iteration a_i = a^{2^i} and b is all but lowest i bits
        // r = a^{lowest i bits of b}
        while(b) {
            if(b & 1) {
                r = (r * a) % m;
            }
            a = (a * a) % m;
            b >>= 1;
        }
        return r;
    }
public:
    int superPow(int a, vector<int>& b) {
        const int m = 1337;
        a %= m;

        // b = b0 * 10^{n - 1} + b1 * 10^{n - 1} + ... + + b_{n - 2} * 10^1 + b_{n - 1} * 10^0
        // a^b mod M = prod for 0 <= i < n of a^{b_i*10^{n - i - 1}} mod M
        
        int r = 1;
        // like square and multiply, but base 10 instead of base 2
        // use "square and multiply" (actually raise to 10th b/c base 10) starting from lowest digit of b
        for(int i = b.size() - 1; i >= 0; --i) {
            r = (r * pow(a, b[i], m)) % m;
            a = pow(a, 10, m);
        }
        return r;
    }
};
