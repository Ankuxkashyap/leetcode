class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        vector<long long> arr;

        for (int i = 0; i < nums.size(); i++) {
            long long square = 1LL * nums[i] * nums[i];
            arr.push_back(square);
        }

        sort(arr.begin(), arr.end());

        long long ans = 0;
        int n = arr.size();

        for (int i = 0; i < n / 2; i++) {
            ans -= arr[i];
        }

        for (int i = n / 2; i < n; i++) {
            ans += arr[i];
        }

        return ans;
    }
};