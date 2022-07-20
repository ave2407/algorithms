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

int cnt = 0, n, m, mx_len = 0, finish = 1e9;
vb need, use;
vvi g;

void dfs_max_depth(int v, int p){
    if (cnt > mx_len){
        mx_len = cnt;
        finish = v;
    }
    if (cnt == mx_len){
        finish = min(finish, v);
    }
    for(auto to: g[v]){
        if (use[to] and to != p){
            cnt++;
            dfs_max_depth(to, v);
        }
    }
    cnt--;
}

int mn(){
    Fastio();
    cin >> n >> m;
    g.resize(n+1);
    need.resize(n+1, false), use.resize(n+1, true);
    vi degree(n+1), need_v;

    fori(n-1){
        int v, u;
        cin >> v >> u;
        g[u].push_back(v);
        g[v].push_back(u);
        //degree[v]++; degree[u]++;
    }
    fori(m){
        int v; cin >> v;
        need_v.push_back(v);
        need[v] = true;
    }


    //______________
    queue<int> q;
    fore(i, 1, n+1){
        degree[i] = g[i].size();
        if (degree[i] == 1){
            q.push(i);
        }
    }
    //cout << "degree 1  :";print(degree);
    while(!q.empty()){
        int t = q.front(); q.pop();
        if (need[t]) continue;
        degree[t]--;
        use[t] = false;

        for(auto c: g[t]){
            degree[c]--;
            if (degree[c] == 1 and !need[c]){
                q.push(c);
            }
        }
    }
    //cout << "degree 2  :";print(degree);
    //cout << "use :";print(use);


    //______________
    int root = need_v[0];
    dfs_max_depth(root, -1);
    cnt = 0; mx_len = 0;
    int start = finish;
    dfs_max_depth(start, -1);
    start = min(start, finish);
    if (start == 1e9) start = need_v[0];
    //______________
    ll edges = -1; // из-за 0 = 1
    for(auto x: use){
        edges += x;
    }
    ll len = 2*edges - mx_len - 2;
    cout << start << eol << len << eol;
}