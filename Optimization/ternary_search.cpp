#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
using namespace __gnu_pbds;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) X.begin(), X.end()
#define sz(X) (int)X.size()

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// xz

template<typename F, typename T>
pair<F, T> ternary_search(T L, T R, function<F(T)> f)
{
    T l = L, r = R, eps = 2;
    while (r - l > eps)
    {
        T m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        T f1 = f(m1), f2 = f(m2);
        if (f1 > f2) l = m1;
        else r = m2;
    }
    T c = l;
    for (T x = c + 1; x <= r; ++x)
        if (f(x) > f(c)) c = x;
    return {f(c), c};
}

int main()
{ _
    int n = 231;
    auto f = [&](int x) { return n * x * (10 - x); };
    int x = ternary_search<int, int>(0, 10, f).first;
    debug(x);
    exit(0);
}
