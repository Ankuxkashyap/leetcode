class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int left = 0, right = 0;

        for (char c : s) {
            if (c == '(') {
                left++;
            } else if (c == ')') {
                if (left > 0) {
                    left--;
                } else {
                    right++;
                }
            }
        }

        set<string> ans;

        function<void(int, int, int, int, string)> solve =
            [&](int i, int l, int r, int balance, string curr) {
                if (balance < 0 || l < 0 || r < 0)
                    return;

                if (i == s.size()) {
                    if (balance == 0 && l == 0 && r == 0)
                        ans.insert(curr);
                    return;
                }

                if (s[i] == '(') {
                    if (l > 0)
                        solve(i + 1, l - 1, r, balance, curr);

                    solve(i + 1, l, r, balance + 1, curr + s[i]);
                } else if (s[i] == ')') {
                    if (r > 0)
                        solve(i + 1, l, r - 1, balance, curr);

                    if (balance > 0)
                        solve(i + 1, l, r, balance - 1, curr + s[i]);
                } else {
                    solve(i + 1, l, r, balance, curr + s[i]);
                }
            };

        solve(0, left, right, 0, "");

        return vector<string>(ans.begin(), ans.end());
    }
};