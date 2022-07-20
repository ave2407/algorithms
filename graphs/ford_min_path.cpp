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
struct edge{
    int v, to, w;
};

void relax(edge e, vll & d){
    d[e.to] = min(d[e.v] + e.w, d[e.to]);
}

int main() {
    Fastio();
    int n, m; cin >> n >> m;
    vector<edge> edges;
    fori(m){
        int v, u, w;
        cin >> v >> u >> w;
        if (v == u) continue;
        edges.push_back({--v, --u, w});
    }
    int INF = 30000;
    vll dist(n, INF);
    dist[0] = 0;

    fore(i, 0, n){
        for(auto edge: edges){
            if (dist[edge.v] == INF) continue;
            //cout << edge.v << " " << edge.to << eol;
            relax(edge, dist);
        }
    }
    print(dist);
}