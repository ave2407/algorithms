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

const int MAXN = 1e5;
vi g[MAXN];
set<int> cut_point;
bool used[MAXN];
int t = 0, n, tin[MAXN], dp[MAXN];

void dfs (int v, int p = -1) {
    used[v] = true;
    tin[v] = dp[v] = t++;
    int children = 0;
    for (auto to: g[v]) {
        if (to == p) continue;
        if (used[to])
            dp[v] = min(dp[v], tin[to]);
        else {
            dfs(to, v);
            dp[v] = min(dp[v], dp[to]);
            if (dp[to] >= tin[v] && p != -1) {
                cut_point.insert(v);
            }
            ++children;
        }
    }
    if (p == -1 && children > 1)
        cut_point.insert(v);
}

int main(){
    Fastio();
    int m; cin >> n >> m;
    fore(i, 1, m+1){
        int u, v;
        cin >> u >> v;
        if (u == v) continue;
        g[u].push_back(v);
        g[v].push_back(u);

    }
    dfs(1, -1);
    cout << cut_point.size() << eol;
    print(cut_point);
}