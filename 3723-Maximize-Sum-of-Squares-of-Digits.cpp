class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum == 0 || sum > 9 * num) {
            return "";
        }
        string ans = "";

        int number;
        for (int i = 0; i < num; i++) {
            if (sum >= 9) {
                number = 9;
            } else {
                number = sum;
            }
            ans += ('0' + number);
            sum -= number;
        }
        return ans;
    }
};