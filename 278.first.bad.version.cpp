// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int low = 1, high = n;
        // invariant: first bad version in range [low, high]
        while(low < high) {
            int mid = low + (high - low)/2;
            // [low, ... mid ... high]
            if(isBadVersion(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};
