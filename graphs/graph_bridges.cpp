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
struct node{
    int v, i;
};

const int MAXN = 1e5;
vector<node> g[MAXN];
vb used;
int t = 0, n, tin[MAXN], fup[MAXN];
vector<pair<int, int>> bridges;
vi bridges_i;

void dfs (int v, int p = -1, int pi = -1) {
    used[v] = true;
    tin[v] = fup[v] = t++;
    for (auto e: g[v]) {
        int to = e.v;
        if (e.i == pi) continue;

        if (used[to])
            fup[v] = min (fup[v], tin[to]);
        else {
            dfs (to, v, e.i);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] > tin[v])
                bridges_i.push_back(e.i);
            //bridges.push_back({v, to});
        }
    }
}

void find_bridges() {
    t = 0;
    used = vb(MAXN, false);
    fore(i, 0, n) {
        if (!used[i])
            dfs(i);
    }
}
int main(){
    Fastio();
    int m; cin >> n >> m;
    fore(i, 1, m+1){
        int u, v;
        cin >> u >> v;
        if (u == v) continue;
        u--; v--;
        g[u].push_back({v, i});
        g[v].push_back({u, i});

    }
    find_bridges();
    sort(all(bridges_i));
    cout << bridges_i.size() << eol;
    print(bridges_i);
}