class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        if(nums.size() < 2) return 0;

        // last number could be super large => Omega(n)
        int largest, secondLargest;
        if(nums[0] > nums[1]) {
            largest = 0;
            secondLargest = 1;
        } else {
            largest = 1;
            secondLargest = 0;
        }
        for(int i = 2; i < nums.size(); ++i) {
            if(nums[i] > nums[secondLargest]) {
                if(nums[i] < nums[largest]) {
                    secondLargest = i;
                } else {
                    secondLargest = largest;
                    largest = i;
                }
            }
        }
        if(nums[largest] >= 2*nums[secondLargest]) {
            return largest;
        } else {
            return -1;
        }
    }
};
