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
struct edge {
    int v, to, w;
};

void relax(edge e, vi &d, vi &p) {
    d[e.to] = min(d[e.v] + e.w, d[e.to]);
    p[e.to] = e.v;
}

int main() {
    Fastio();
    int n, m;
    cin >> n;
    vector<edge> edges;
    fore(i, 0, n) {
        fore(j, 0, n) {
            int v;
            cin >> v;
            if (v == 1e5) continue;
            edges.push_back({i, j, v});
            //g[j].push_back({i, v});
        }
    }
    fore(i, 0, n){
        edges.push_back({n, i, 0});
    }
    int INF = INT_MAX;
    vi dist(n+1, INF), p(n+1, 0);
    dist[n] = 0;

    int s;
    fore(i, 0, n+1) {
        s = -1;
        for (auto e: edges) {
            if (dist[e.v] == INF)continue;
            if (dist[e.to] > dist[e.v] + e.w) {
                relax(e, dist, p);
                s = e.v;
            }
        }
    }
    //print(p);

    if (s == -1) {
        cout << "NO\n";
        return 0;
    }
    vb used(n, false);
    vi ans;
    //cout << s << eol;
    int cur = s;
    for (; !used[cur]; cur = p[cur]) {
        ans.push_back(cur + 1);
        used[cur] = true;
    }
    cur++;
    reverse(all(ans));
    while(ans.back() != cur){
        ans.pop_back();
    }
    cout << "YES\n";
    cout << ans.size() << eol;
    print(ans);

}