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
struct node{
    int v, i;
    bool exist = true;
};

const int MAXN = 2*1e5+10;
vector<node> g[MAXN];
vb used;
int t = 0, n, tin[MAXN], fup[MAXN], comp[MAXN];
vector<pair<int, int>> bridges;
vi meta[MAXN];

void dfs1 (int v, int pi = -1) {
    used[v] = true;
    tin[v] = fup[v] = t++;
    for (auto & e: g[v]) {
        int to = e.v;
        if (e.i == pi) continue;

        if (used[to])
            fup[v] = min (fup[v], tin[to]);
        else {
            dfs1(to, e.i);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] > tin[v]) {
                e.exist = false;
                bridges.emplace_back(v, to);
                //bridges_i.push_back(e.i);
            }
        }
    }
}
void find_bridges() {
    t = 0;
    used = vb(MAXN, false);
    fore(i, 0, n) {
        if (!used[i])
            dfs1(i);
    }
}

int num = 1;
void dfs2(int v){
    comp[v] = num;
    for(auto to: g[v]){
        if (!to.exist or comp[to.v] != 0) continue;
        dfs2(to.v);
    }
}


void get_meta(){
    fore(i, 0, n){
        if(!comp[i]){
            dfs2(i);
            num++;
        }
    }
    for(auto &v: g){
        v.clear();
        v.shrink_to_fit();
    }
    for(auto bridge: bridges){
        int u = comp[bridge.fi];
        int v = comp[bridge.se];
        meta[u].push_back(v);
        meta[v].push_back(u);
    }
}

int ans = 0, cur_mx_len = 0, cnt = 0, finish = 0;
void dfs_max_depth(int v, int p){
    used[v] = true;
    if (cnt > cur_mx_len){
        cur_mx_len = cnt;
        finish = v;
    }
    for(auto to: meta[v]){
        if (to != p){
            cnt++;
            dfs_max_depth(to, v);
        }
    }
    cnt--;
}

void find_max_d(){
    fore(i, 0, num){
        used[i] = false;
    }
    fore(start, 1, num){
        if (!used[start]){
            cur_mx_len = cnt = 0;
            dfs_max_depth(start, -1);

            cur_mx_len = cnt = 0;
            dfs_max_depth(finish, -1);

            ans = max(cur_mx_len, ans);
        }
    }
}
int man(){
    Fastio();
    int m; cin >> n >> m;
    fore(i, 1, m+1){
        int u, v;
        cin >> u >> v;
        if (u == v) continue;
        u--; v--;
        g[u].push_back({v, i, true});
        g[v].push_back({u, i, true});
    }

    find_bridges();
    get_meta();
    find_max_d();
    cout << bridges.size() - ans << eol;
}

/*
 const int MAXN = 2*1e5+10;

int t = 0, n, tin[MAXN], fup[MAXN], comp[MAXN];
vector<pair<int, int>> bridges;
vi meta[MAXN], g[MAXN];
bool used[MAXN], exist[MAXN];


map<pair<int, int>, int> cnt_edge;
pair<int, int> make_edge(int a, int b){
    return make_pair(min(a, b), max(a, b));
}

void dfs1 (int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = t++;
    for (auto to: g[v]) {
        if (to == p) continue;
        if (used[to])
            fup[v] = min (fup[v], tin[to]);
        else {
            dfs1(to, v);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] > tin[v] and cnt_edge[make_edge(to, v)]++ == 0) {
                exist[to] = false;
                exist[v] = false;
                bridges.emplace_back(v, to);
            }
        }
    }
}
void find_bridges() {
    fore(i, 1, n+1) {
        if (!used[i])
            dfs1(i);
    }
}

int num = 1;
void dfs2(int v){
    comp[v] = num;
    for(auto to: g[v]){
        if (!exist[to] or comp[to] != 0) continue;
        dfs2(to);
    }
}


void get_meta(){
    fore(i, 1, n+1){
        if(!comp[i]){
            dfs2(i);
            num++;
        }
    }
    for(auto &v: g){
        v.clear();
        v.shrink_to_fit();
    }
    for(auto bridge: bridges){
        int u = comp[bridge.fi];
        int v = comp[bridge.se];
        meta[u].push_back(v);
        meta[v].push_back(u);
    }
}

int ans = 0, cur_mx_len = 0, cnt = 0, finish = 0;
void dfs_max_depth(int v, int p){
    used[v] = true;
    if (cnt > cur_mx_len){
        cur_mx_len = cnt;
        finish = v;
    }
    for(auto to: meta[v]){
        if (to != p){
            cnt++;
            dfs_max_depth(to, v);
        }
    }
    cnt--;
}

void find_max_d(){
    fore(i, 0, num+2){
        used[i] = false;
    }
    fore(start, 1, num){
        if (!used[start]){
            cur_mx_len = cnt = 0;
            dfs_max_depth(start, -1);

            cur_mx_len = cnt = 0;
            dfs_max_depth(finish, -1);

            ans = max(cur_mx_len, ans);
        }
    }
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
    fill_n(exist, n+2, true);
    find_bridges();
    print_pairs(bridges);
    fore(i, 0, n+1) cout << exist[i] << " "; cout << eol;
    get_meta();
    cout << "meta\n";
    fore(i, 0, num+1){
        cout << i << "   ";
        print(meta[i]);
    }
    find_max_d();
    cout << bridges.size() - ans << eol;
}*/