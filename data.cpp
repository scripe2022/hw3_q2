// compile: g++ -o data data.cpp -O3 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2 -DLOCAL
// run: ./data < data.in
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
#define MAXN 1010

set<pair<int, int>> T, E, U;
int weights[MAXN][MAXN], toll[MAXN][MAXN];
int n, m;
struct node {
    int v, w;
};
vector<vector<node>> e;

void dijkstra(int s, vector<int> &dis, vector<int> &vis) {
    dis[s] = 0;
    for (int i = 0; i < 3*n; ++i) {
        int u = 0, mind = INTINF;
        for (int j = 0; j < 3*n; ++j) {
            if (!vis[j] && dis[j]<mind) u = j, mind = dis[j];
        }
        vis[u] = 1;
        for (auto ed: e[u]) {
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w) dis[v] = dis[u] + w;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w, t; cin >> u >> v >> w >> t;
        E.insert(make_pair(u, v));
        if (t) T.insert(make_pair(u, v));
        else U.insert(make_pair(u, v));
        weights[u][v] = weights[v][u] = w;
        toll[u][v] = toll[v][u] = t;
    }
    // map (u, i) to u + i*n
    e.resize(3*n);
    auto add_edge = [&](pair<int, int> u, pair<int, int> v, int w) {
        e[u.first + u.second*n].push_back({v.first + v.second*n, w});
    };
    // U = E - T
    for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
        if (T.find({u, v}) != T.end() || T.find({v, u}) != T.end()) {
            add_edge(make_pair(u, 0), make_pair(v, 1), weights[u][v]);
            add_edge(make_pair(u, 1), make_pair(v, 2), weights[u][v]);
        }
        if (U.find({u, v}) != U.end() || U.find({v, u}) != U.end()) {
            add_edge(make_pair(u, 0), make_pair(v, 0), weights[u][v]);
            add_edge(make_pair(u, 1), make_pair(v, 1), weights[u][v]);
            add_edge(make_pair(u, 2), make_pair(v, 2), weights[u][v]);
        }
    }
    // equivalent construction:
    // for (auto it = T.begin(); it != T.end(); ++it) {
    //     int u = it->first, v = it->second;
    //     add_edge(make_pair(u, 0), make_pair(v, 1), weights[u][v]);
    //     add_edge(make_pair(u, 1), make_pair(v, 2), weights[u][v]);
    //     add_edge(make_pair(v, 0), make_pair(u, 1), weights[u][v]);
    //     add_edge(make_pair(v, 1), make_pair(u, 2), weights[u][v]);
    // }
    // for (auto it = U.begin(); it != U.end(); ++it) {
    //     int u = it->first, v = it->second;
    //     add_edge(make_pair(u, 0), make_pair(v, 0), weights[u][v]);
    //     add_edge(make_pair(u, 1), make_pair(v, 1), weights[u][v]);
    //     add_edge(make_pair(u, 2), make_pair(v, 2), weights[u][v]);
    //     add_edge(make_pair(v, 0), make_pair(u, 0), weights[u][v]);
    //     add_edge(make_pair(v, 1), make_pair(u, 1), weights[u][v]);
    //     add_edge(make_pair(v, 2), make_pair(u, 2), weights[u][v]);
    // }

    vector<int> dis(3*n, INTINF), vis(3*n, 0);
    dijkstra(0, dis, vis);
    debug(dis)
    int ans = min({dis[n - 1], dis[2*n - 1], dis[3*n - 1]});
    cout << (ans==INTINF ? -1 : ans) << endl;

    return 0;
}