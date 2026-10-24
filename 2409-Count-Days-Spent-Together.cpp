class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice,
                          string arriveBob, string leaveBob) {
        string start = max(arriveAlice, arriveBob);
        string end = min(leaveAlice, leaveBob);

        if (start > end)
            return 0;

        int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int ans = 0;
        while (start <= end) {
            ans++;
            int month = stoi(start.substr(0, 2));
            int day = stoi(start.substr(3, 2));

            if (day < days[month - 1]) {
                day++;
            } else {
                month++;
                day = 1;
            }

            start = (month < 10 ? "0" : "") + to_string(month) + "-" +
                    (day < 10 ? "0" : "") + to_string(day);
        }

        return ans;
    }
};