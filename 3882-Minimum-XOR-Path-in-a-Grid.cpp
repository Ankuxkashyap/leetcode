class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        auto molqaviren = grid;

        const int X = 1024;

        vector<array<bool, X>> prev(n), curr(n);

        for (int j = 0; j < n; j++)
            prev[j].fill(false);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                curr[j].fill(false);

                if (i == 0 && j == 0) {
                    curr[j][grid[i][j]] = true;
                    continue;
                }

                int val = grid[i][j];

                if (i > 0) {
                    for (int x = 0; x < X; x++) {
                        if (prev[j][x])
                            curr[j][x ^ val] = true;
                    }
                }
                if (j > 0) {
                    for (int x = 0; x < X; x++) {
                        if (curr[j - 1][x])
                            curr[j][x ^ val] = true;
                    }
                }
            }

            swap(prev, curr);
        }
        for (int x = 0; x < X; x++) {
            if (prev[n - 1][x])
                return x;
        }
        return 0;
    }
};