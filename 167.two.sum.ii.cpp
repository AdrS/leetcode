class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int start = 0, end = numbers.size() - 1;
        for(;;) {
            int s = numbers[start] + numbers[end];
            if(s < target) {
                ++start;
            } else if(s > target) {
                --end;
            } else {
                break;
            }
        }
        return {start + 1, end + 1};
    }
};
