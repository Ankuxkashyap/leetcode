
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;

        vector<long long> diff(n);
        long long total = 0, maxDiff = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total += diff[i];
            maxDiff = max(maxDiff, diff[i]);
        }

        if (k >= total) return 0;

        long long left = 0, right = maxDiff;

        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long needed = 0;

            for (long long d : diff) {
                if (d > mid) needed += d - mid;
                if (needed > k) break;
            }

            if (needed <= k)
                right = mid;
            else
                left = mid + 1;
        }

        long long threshold = left;
        long long remaining = k;
        long long ans = 0;

        for (long long& d : diff) {
            if (d > threshold) {
                remaining -= d - threshold;
                d = threshold;
            }
            ans += d * d;
        }

        for (long long& d : diff) {
            if (remaining == 0) break;

            if (d == threshold && d > 0) {
                ans -= d * d;
                d--;
                ans += d * d;
                remaining--;
            }
        }

        return ans;
    }
};
