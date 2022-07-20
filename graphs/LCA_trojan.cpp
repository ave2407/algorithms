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
#pragma GCC optimize("O3")
#pragma GNU optimize("O3")
#pragma G++ optimize("O3")
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
const int MAXN = 500010;
struct req{
    int x, i;
};

int sz[MAXN], p[MAXN], ancestor[MAXN];
bool used[MAXN];
vi ans;
vvi g;
vector<vector<req>> reqs;


void init(){
    g.resize(MAXN, vi());
    reqs.resize(MAXN, vector<req>());
    fore(i, 1, MAXN){
        p[i] = i;
    }

}
int get(int x){
    if (p[x] == x) return x;
    return p[x] = get(p[x]);
}
void join(int x, int y){
    x = get(x);
    y = get(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    p[y] = x;
    sz[x] += sz[y];
}


void dfs(int v)
{
    used[v] = true;
    ancestor[v] = v;
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u);
            join(v, u);
            ancestor[get(v)] = v;
        }
    }
    for (auto node: reqs[v]) {
        if (used[node.x])
            ans[node.i] = ancestor[get(node.x)];
    }
}
int main(){
    Fastio();
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    init();
    int k; cin >> k;
    int q = 0;
    fore(i, 0, k){
        string s; int x, y;
        cin >> s >> x >> y;
        if (s == "ADD"){
            g[x].push_back(y);
            g[y].push_back(x);
        }
        else if(s == "GET"){
            reqs[x].push_back({y, q});
            reqs[y].push_back({x, q++});
        }
    }
    ans = vi(q, 0);
    dfs(1);

    for(auto x: ans) cout << x << eol;
}