class Solution {
public:
    int lastRemaining(int n) {
        int a = 1, b = 0;
        
        // invariant: T(n_origional) = a*T(n_current) + b;
        while(n > 4) {
            switch (n % 4) {
                case 0:
                case 1:                    
                    b -= (a << 1);
            }
            a <<= 2;
            n >>= 2;
        }
        int base[5] = {-1, 1, 2, 2, 2};
        return a*base[n] + b;
    }
    /*
    int lastRemaining(int n) {
        // base cases
        // n = 1, 2, 3, 4 -> 1, 2, 2, 2
        if(n <= 4) {
            if(n == 1) {
                return 1;
            } else {
                return 2;
            }
        }
        switch (n % 4) {
            case 0:
            case 1:
                return 4*lastRemaining(n/4) - 2;                
            default:
                return 4*lastRemaining(n/4);
        }
    }*/
};
// my solution 84 ms
/*
16 ms
    int lastRemaining(int n) {
        if (n == 1) return 1;
        return ((n >> 1) + 1 - lastRemaining(n >> 1)) << 1;
    }
*/
