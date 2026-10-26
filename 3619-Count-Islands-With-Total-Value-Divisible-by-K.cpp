class Solution {
    int ct, r, c;
    static const inline vector<int> move = {-1, 0, 1, 0, -1};

public:
    long long dfs(int i, int j, vector<vector<int>>& grid) {
        if (i < 0 || j < 0 || i >= r || j >= c || grid[i][j] <= 0)
            return 0;

        long long sum = grid[i][j];
        grid[i][j] = -1;

        for (int x = 0; x < 4; x++) {
            sum += dfs(i + move[x], j + move[x + 1], grid);
        }
        return sum;
    }
    int countIslands(vector<vector<int>> grid, int k) {
        r = grid.size(), c = grid[0].size(), ct = 0;

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] > 0 && dfs(i, j, grid) % k == 0) {
                    ct++;
                }
            }
        }
        return ct;
    }
};