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

template<class T>void print(T &v) {for (auto el: v) { cout << el << " "; }cout << "\n";}
template<class T>void print_2d(T &vv) {for (auto v: vv) {for (auto el: v) { cout << el << " "; }cout << "\n";}cout << "\n";}
template<class T>void print_pairs(T &v) {for (auto el: v) { cout << el.first << " " << el.second << "\n"; }cout << "\n";}

#define readArr(arr) {for (auto & x: arr) cin >>x;}
#define fore(i, l, r) for(int i = int(l); i < int(r); i++)
#define fori(n) for (size_t i = 0; i < n; i++)
#define all(a) (a).begin(), (a).end()
#define fi first
#define se second
#define Fastio() {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
#define eol '\n'

int cnt = 0, n;
vvi g;


int man(){
    Fastio();
    cin >> n;
    g.resize(n+1);
    vb used(n+1, false);
    vi degree(n+1), dist(n+1, 0);

    fori(n-1){
        int v, u;
        cin >> v >> u;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queue<int> q;
    fore(i, 1, n+1){
        degree[i] = g[i].size();
        if (degree[i] == 1){
            q.push(i);
        }
    }
    while(!q.empty()){
        int t = q.front(); q.pop(); degree[t]--;
        for(auto c: g[t]){
            degree[c]--;
            if (degree[c] == 1){
                q.push(c);
                dist[c] = dist[t] + 1;
            }
        }
    }

    int mx = *max_element(all(dist));
    fore(i, 1, n+1){
        if (dist[i] == mx) cout << i << " ";
    }
}