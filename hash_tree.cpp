#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include "deque"
#include "set"
#include "map"
#include <climits>
#include "cmath"
#include "random"
#include "time.h"

//#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")
//#define int ll


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
typedef pair<int, int> pii;

template<class T>
void print(T &v) {
    for (auto el : v) { cout << el << " "; }
    cout << "\n";
}

template<class T>
void print_2d(T &vv) {
    for (auto v : vv) {
        for (auto el : v) { cout << el << " "; }
        cout << "\n";
    }
    cout << "\n";
}

template<class T>
void print_pairs(T &v) {
    cout << "\n";
    for (auto el : v) { cout << el.first << " " << el.second << "\n"; }
}

#define read(arr) {for (auto & x : arr) cin >> x;}
#define fore(i, l, r) for (int i = int(l); i < int(r); i++)
#define fori(n) for (int i = 0; i < n; i++)
#define all(a) (a).begin(), (a).end()
#define fi first
#define se second
#define Fastio() {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
#define deb(x) cout << #x << " = " << x << '\n';
#define eol '\n'

//______________________________________________________________

const int MAXN = 1e5;
vvi g;
map<vector<int>, int> hashes;
vi col;
vector<int> h1, h2;

int getHash(const vector<int> &values) {
    if (hashes.find(values) != hashes.end()) {
        return hashes[values];
    }
    hashes.insert({values, (int) hashes.size()});
    return hashes[values];
}

int dfs(vi &h, int v, int p) {
    vi values;
    col[v] = 1;
    for (auto to : g[v]) {
        if (to != p) {
            if (col[to] == 0) {
                values.push_back(dfs(h, to, v));
            } else {
                values.push_back(h[to]);
            }
        }
    }
    sort(all(values));
    col[v] = 2;
    h[v] = getHash(values);
    return h[v];
}

void read_graph(int n) {
    g.assign(n + 1, vi());
    col.assign(n + 1, 0);

    fori(n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

int main() {
    int n;
    cin >> n;
    int r1, r2;
    cin >> r1 >> r2;
    h1.resize(n + 1, 0);
    h2.resize(n + 1, 0);

    read_graph(n);
    dfs(h1, r1, -1);

    read_graph(n);
    dfs(h2, r2, -1);

    if (h1[r1] == h2[r2]) {
        cout << "YES" << eol;
    } else {
        cout << "NO" << eol;
    }
}