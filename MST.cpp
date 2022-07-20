#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <queue>
#include "cmath"
#include "set"
#include "map"

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

//____________________________________
vi p, sz, ex;
struct edge{
    int u, v, x;
};

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
bool comp(edge a, edge b){
    return a.x < b.x;
}
int main(){
    int n, m;
    cin >> n >> m;
    vector<edge> edges, skeleton;
    p.resize(n+1);
    fore(i, 1, n+1) p[i] = i;
    sz.resize(n+1, 1);
    //ex.resize(n+1, 0);

    fori(m){
        int u, v, x;
        cin >> u >> v >> x;
        edges.push_back({u, v, x});
    }
    sort(all(edges), comp);
    for(auto e: edges){
        //cout << e.x << eol;
        int v = get(e.v);
        int u = get(e.u);
        if (u != v){
            join(u, v);
            skeleton.push_back(e);
        }
    }
    int ans = 0;
    for(auto e: skeleton){
        ans = max(e.x, ans);
    }
    cout << ans;
}