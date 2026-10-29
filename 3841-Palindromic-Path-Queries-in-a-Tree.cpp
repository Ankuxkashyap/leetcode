
class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s,
                                vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(LOG, vector<int>(n));
        vector<int> tin(n), tout(n), depth(n), bit(n + 2);
        int timer = 0;

        vector<int> parent(n, 0), visited(n, 0);
        vector<pair<int, int>> st = {{0, 0}};
        visited[0] = 1;

        while (!st.empty()) {
            int u = st.back().first;
            int &i = st.back().second;

            if (i == 0) {
                tin[u] = ++timer;
                up[0][u] = parent[u];

                for (int j = 1; j < LOG; j++)
                    up[j][u] = up[j - 1][up[j - 1][u]];
            }

            if (i < (int)adj[u].size()) {
                int v = adj[u][i++];

                if (visited[v]) continue;
                visited[v] = 1;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back({v, 0});
            } else {
                tout[u] = timer;
                st.pop_back();
            }
        }

        auto add = [&](int i, int x) {
            for (; i <= n + 1; i += i & -i)
                bit[i] ^= x;
        };

        auto sum = [&](int i) {
            int x = 0;
            for (; i > 0; i -= i & -i)
                x ^= bit[i];
            return x;
        };

        for (int i = 0; i < n; i++) {
            int x = 1 << (s[i] - 'a');
            add(tin[i], x);
            add(tout[i] + 1, x);
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            for (int j = LOG - 1; j >= 0; j--)
                if (depth[u] - (1 << j) >= depth[v])
                    u = up[j][u];

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }
            return up[0][u];
        };

        vector<bool> ans;

        for (auto &q : queries) {
            string type;
            int u;
            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int change = (1 << (s[u] - 'a')) ^
                             (1 << (c - 'a'));

                add(tin[u], change);
                add(tout[u] + 1, change);
                s[u] = c;
            } else {
                int v;
                ss >> v;

                int a = lca(u, v);
                int mask = sum(tin[u]) ^ sum(tin[v]) ^
                           (1 << (s[a] - 'a'));

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};
