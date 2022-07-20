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
int n, num = 0;
vvi g, gt;
vi color, lst;

void dfs(int v){
    color[v] = 1;
    for(auto to: g[v]){
        if (!color[to]){
            dfs(to);
        }
    }
    color[v] = 2;
    lst.push_back(v);
}
void dfs2(int v){
    color[v] = num;
    for(auto to: gt[v]){
        if (!color[to]){
            dfs2(to);
        }
    }
}

int main(){
    int m; cin >> n >> m;
    g.resize(n+1); gt.resize(n+1); color.resize(n+1, 0);

    fore(i, 0, m){
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
        gt[u].push_back(v);
    }
    fore(i, 1, n+1){
        if (!color[i]){
            dfs(i);
        }
    }
    reverse(all(lst));
    color.assign(n+1, 0);
    for(auto c: lst){
        if (!color[c]){
            num++;
            dfs2(c);
        }
    }
    cout << num << eol;
    fore(i, 1, n+1){
        cout << color[i] << " ";
    }
}