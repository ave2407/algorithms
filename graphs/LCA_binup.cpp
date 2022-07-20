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

#pragma GCC optimize("Ofast")

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
        for (auto el: v) { cout << el << " "; }
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
struct req{
    int x, y;
};

int n, l;
vvi g;

int timer;
vi tin, tout;
vvi up;

void dfs(int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;
    fore(i, 1, l + 1)
        up[v][i] = up[up[v][i - 1]][i - 1];

    for (int u: g[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vi(l + 1));
    dfs(root, root);
}

int main() {
    Fastio();
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    n = 500001;
    int k; cin >> k;
    vector<req> reqs;
    g.resize(n, vi());
    fore(i, 0, k){
        string s; int x, y;
        cin >> s >> x >> y;
        x--; y--;
        if (s == "ADD"){
            g[x].push_back(y);
            g[y].push_back(x);
        }
        else if(s == "GET"){
            reqs.push_back({x, y});
        }
    }
    preprocess(0);
    for(req r: reqs){
        cout << lca(r.x, r.y) + 1 << eol;
    }
}