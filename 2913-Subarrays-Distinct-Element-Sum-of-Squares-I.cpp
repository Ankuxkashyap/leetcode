class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int sum = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            unordered_set<int> set;
            for (int j = i; j < n; j++) {
                set.insert(nums[j]);
                int count = set.size();
                sum = sum + (count * count);
            }
        }
        return sum;
    }
};