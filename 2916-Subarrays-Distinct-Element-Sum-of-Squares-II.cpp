
class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const long long MOD = 1000000007;
        int n = nums.size();

        vector<long long> sum(4 * n, 0);
        vector<long long> sq(4 * n, 0);
        vector<long long> lazy(4 * n, 0);

        auto update = [&](auto&& self, int node, int l, int r, int ql,
                          int qr) -> void {
            if (ql > r || qr < l || ql > qr)
                return;

            if (ql <= l && r <= qr) {
                long long len = r - l + 1;
                long long v = 1;

                sq[node] = (sq[node] + 2 * v * sum[node] + len * v * v) % MOD;
                sum[node] = (sum[node] + len * v) % MOD;
                lazy[node] = (lazy[node] + v) % MOD;
                return;
            }

            int mid = (l + r) / 2;

            if (lazy[node] != 0) {
                long long v = lazy[node];

                for (int child = 0; child < 2; child++) {
                    int c = node * 2 + 1 + child;
                    int left = (child == 0) ? l : mid + 1;
                    int right = (child == 0) ? mid : r;
                    long long len = right - left + 1;

                    sq[c] = (sq[c] + 2 * v * sum[c] + len * v % MOD * v) % MOD;
                    sum[c] = (sum[c] + len * v) % MOD;
                    lazy[c] = (lazy[c] + v) % MOD;
                }

                lazy[node] = 0;
            }

            self(self, node * 2 + 1, l, mid, ql, qr);
            self(self, node * 2 + 2, mid + 1, r, ql, qr);

            sum[node] = (sum[node * 2 + 1] + sum[node * 2 + 2]) % MOD;

            sq[node] = (sq[node * 2 + 1] + sq[node * 2 + 2]) % MOD;
        };

        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int prev = -1;

            if (last.count(nums[i]))
                prev = last[nums[i]];

            update(update, 0, 0, n - 1, prev + 1, i);
            ans = (ans + sq[0]) % MOD;

            last[nums[i]] = i;
        }

        return (int)ans;
    }
};
