
class Solution {
public:
   int minSwaps(vector<int>& nums) {
       int n = nums.size();

        vector<pair<int, int>> arr(n);

        for (int i = 0; i < n; i++) {
            int num = nums[i];
            int sum = 0;

            while (num > 0) {
                sum += num % 10;
                num /= 10;
            }

            arr[i] = {sum, nums[i]};
        }
        
        sort(arr.begin(), arr.end());
        unordered_map<int, int> pos;

        for (int i = 0; i < n; i++) {
            pos[nums[i]] = i;
        }
        int swaps = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == arr[i].second) continue;
            int wanted = arr[i].second;
            int j = pos[wanted];
            swap(nums[i], nums[j]);
            pos[nums[j]] = j;
            pos[nums[i]] = i;
            swaps++;
        }
        return swaps;
    }
};
