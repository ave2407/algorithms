#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <queue>
#include <random>
#include "cmath"
#include "set"
#include "map"
#include "chrono"
#include "bitset"

#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GNU optimize("O3")
//#pragma G++ optimize("O3")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma G++ optimize("no-stack-protection")

using namespace std;
typedef unsigned long long ull;
typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;

template<class T>
void print(T &v) {
    for (auto el: v) { cout << el << " "; }
    cout << "\n";
}

template<class T>
void print_2d(T &vv) {
    for (auto v: vv) {
        for (auto el: v) {cout << el << " "; }
        cout << "\n";
    }
    cout << "\n";
}

template<class T>
void print_pairs(T &v) {
    for (auto el: v) { cout << el.first << " " << el.second << "\n"; }
    cout << "\n";
}

#define readArr(arr) {for (auto & x: arr) cin >>x;}
#define fore(i, l, r) for(int i = int(l); i < int(r); i++)
#define fori(n) for (size_t i = 0; i < n; i++)
#define all(a) (a).begin(), (a).end()
#define fi first
#define se second
#define Fastio() {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
#define eol '\n'

//______________________________________________________________

int main() {
    Fastio();
    //freopen("dijkstra.in", "r", stdin);
    //freopen("dijkstra.out", "w", stdout);
    int INF = INT32_MAX;
    int n, m, s = 0, f;
    cin >> n >> s >> f;
    s--; f--;
    vector<vector<pair<int, int>>> g(n);

    fore(i, 0, n) {
        fore(j, 0, n){
            int v; cin >> v;
            if (v <= 0) continue;
            g[i].push_back({j, v});
            //g[j].push_back({i, v});
        }
    }
    vector<ll> dist(n, INF);
    dist[s] = 0;
    vector<int> p(n);
    set<pair<int, int>> q;
    q.insert({0, s});

    while (!q.empty()) {
        auto x = *q.begin();
        if (x.first != dist[x.second]) continue;
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto e: g[v]) {
            int to = e.first, w = e.second;

            if (dist[v] + w < dist[to]) {
                q.erase(make_pair(dist[to], to));
                dist[to] = dist[v] + w;
                p[to] = v;
                q.insert(make_pair(dist[to], to));
            }
        }
    }
    if (dist[f] == INF) cout << -1;
    else cout << dist[f];
}