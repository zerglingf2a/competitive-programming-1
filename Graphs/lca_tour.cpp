// K > floor(log(2 * n - 1))
template<int K>
struct LCA {
    const vector<vector<int>>& E;
    const int n, m;
    vector<int> h, tin, tour, log;
    vector<array<int, K>> st;
    int op(int u, int v) const { return h[u] <= h[v] ? u : v; }
    void dfs(int u, int p) {
        h[u] = h[p] + 1, tin[u] = (int)size(tour);
        tour.push_back(u);
        for (auto v : E[u]) if (v != p) {
            dfs(v, u);
            tour.push_back(u);
        }
    }
    LCA(const auto& E, int root) : E(E), n((int)size(E)), m(2 * n - 1), h(n), tin(n), log(m + 1, 0), st(m) {
        dfs(root, root);
        for (int x = 2; x <= m; ++x) log[x] = 1 + log[x >> 1];
        assert(log[m] < K);
        for (int j = 0; j < m; ++j) st[j][0] = tour[j];
        for (int x = 1; x <= log[m]; ++x)
            for (int j = 0; j + (1 << x) <= m; ++j)
                st[j][x] = op(st[j][x - 1], st[j + (1 << (x - 1))][x - 1]);
    }
    int lca(int u, int v) const {
        int l = tin[u], r = tin[v];
        if (l > r) swap(l, r);
        int x = log[r - l + 1];
        return op(st[l][x], st[r - (1 << x) + 1][x]);
    }
    int distance(int u, int v) const {
        int w = query(u, v);
        return h[u] + h[v] - 2 * h[w];
    }
};
