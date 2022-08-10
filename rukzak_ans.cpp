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
#include "iomanip"

#pragma GCC optimize("Ofast")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("unroll-loops")

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

int main() {
    Fastio();
    int n, m;
    cin >> n >> m;
    vvi a(n + 1, vi(m + 1, 0));
    vi w(n + 1, 0), p(n + 1, 0);

    fore(i, 1, n + 1) {
        int x; cin >> x;
        p[i] = x;
        cin >> w[i];
    }

    fore(i, 1, n + 1) {
        fore(j, 1, m + 1) {
            a[i][j] = 0;
            if (j >= w[i]) {
                a[i][j] = max(a[i - 1][j], (a[i - 1][j - w[i]] + p[i]));
            } else if (a[i - 1][j] != 0) {
                a[i][j] = a[i - 1][j];
            }
        }
    }
    cout << a[n][m]<< endl;

    int mm = m;
    vector<int> ans;
    for (int i = n; i >= 1; i--) {
        if (a[i - 1][mm] != a[i][mm]) {
            ans.push_back(i);
            mm = mm - w[i];
        }
    }
    reverse(all(ans));
    print(ans);
    return 0;
}