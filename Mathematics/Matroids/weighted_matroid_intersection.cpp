template<typename X, typename Y>
pair<X, Y> neg(pair<X, Y> p) {
    return {-p.first, -p.second};
}
// assumes w >= 0 (modify to SPFA otherwise)
template<typename T, typename Matroid1, typename Matroid2>
vector<int> weighted_matroid_intersection(int N, vector<T> w, Matroid1& M1, Matroid2& M2) {
    vector<bool> b(N), target(N);
    vector<int> I[2], from(N);
    vector<array<T, 2>> p(N);
    vector<pair<T, int>> d(N);
    vector<pair<pair<T, int>, int>> heap;
    auto check_edge = [&](int u, int v) {
        return (b[u] && M1.oracle(u, v)) || (b[v] && M2.oracle(v, u));
    };
    while (true) {
        I[0].clear(), I[1].clear();
        for (int u = 0; u < N; ++u) {
            I[b[u]].push_back(u);
        }
        M1.build(I[1]), M2.build(I[1]);
        fill(d.begin(), d.end(), pair(numeric_limits<T>::max(), numeric_limits<int>::max()));
        fill(target.begin(), target.end(), false);
        fill(from.begin(), from.end(), -1);
        for (auto u : I[0]) {
            target[u] = M2.oracle(u);
            if (M1.oracle(u)) {
                d[u] = {w[u] + p[u][0] - p[u][1], 0};
                heap.emplace_back(neg(d[u]), u);
            }
        }
        make_heap(heap.begin(), heap.end());
        bool converged = true;
        while (!heap.empty()) {
            auto [du, u] = heap[0];
            pop_heap(heap.begin(), heap.end());
            heap.pop_back();
            if (neg(du) != d[u]) continue;
            if (target[u]) {
                converged = false;
                heap.clear();
                for (int v = 0; v < N; ++v) {
                    T cost = w[v] + p[v][b[v]] - p[v][!b[v]];
                    //assert(cost >= 0);
                    //assert(d[v].first - cost >= 0);
                    p[v][b[v]] += min(d[v].first - cost, d[u].first);
                    p[v][!b[v]] += min(d[v].first, d[u].first);
                }
                for (int v = u; v != -1; v = from[v]) {
                    b[v] = !b[v];
                    w[v] *= -1;
                }
                break;
            }
            for (auto v : I[!b[u]]) {
                if (!check_edge(u, v)) continue;
                //assert(p[u][!b[u]] - p[v][!b[u]] >= 0);
                //assert(w[v] + p[v][!b[u]] - p[v][b[u]] >= 0);
                pair<T, int> nd(d[u].first + w[v] + p[u][!b[u]] - p[v][b[u]], d[u].second + 1);
                if (nd < d[v]) {
                    from[v] = u;
                    d[v] = nd;
                    heap.emplace_back(neg(d[v]), v);
                    push_heap(heap.begin(), heap.end());
                }
            }
        }
        if (converged) break;
    }
    return I[1];
}