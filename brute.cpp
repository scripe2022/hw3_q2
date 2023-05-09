// compile: g++ -o brute brute.cpp -O3 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2 -DLOCAL
// run: ./brute < data.in
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#ifdef LOCAL
#include <debug/codeforces.h>
#define debug(x...) {_variables(#x);_print(x);}
#else
#define debug(x...)
#endif
template<typename...Args> void print_(Args...args){((cout<<args<<" "),...)<<endl;}
#define rep(i,a,b) for(int i=(a);i<(int)(b);++i)
#define sz(v) ((int)(v).size())
#define print(...) print_(__VA_ARGS__);
#define INTMAX (int)(9223372036854775807)
#define INTINF (int)(1152921504606846976)
#define int long long
#define MAXN 200010

struct node {
    int v, w, t;
};
int n, m, S, T;
vector<vector<node>> e;
vector<int> vis;
int ans = INTINF;

void dfs(int u, int sum, int cost) {
    if (u == T) {
        ans = min(ans, sum);
        return;
    }
    for (auto edge: e[u]) {
        int v = edge.v, w = edge.w, t = edge.t;
        if (vis[v] || cost+t > 2) continue;
        vis[v] = 1;
        dfs(v, sum + w, cost + t);
        vis[v] = 0;
    }
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> m;
    S = 0, T = n-1;
    e.resize(n), vis.assign(n, 0);
    rep(i, 0, m) {
        int u, v, w, t; cin >> u >> v >> w >> t;
        e[u].push_back({v, w, t});
        e[v].push_back({u, w, t});
    }
    dfs(0, 0, 0);
    cout << (ans==INTINF ? -1 : ans) << endl;

    return 0;
}