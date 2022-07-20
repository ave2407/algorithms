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
vll t;
vll a;
const int INF = 1e9;

void update(int v){
    t[v] = t[2*v] + t[2*v+1];
}

void build (int tl ,int tr, int v){
    if (tl + 1 == tr){
        t[v] = a[tl];
        return;
    }
    int mid = (tl + tr) / 2;
    build(tl, mid, 2*v);
    build(mid, tr, 2*v+1);
    update(v);
}

ll get(int tl, int tr, int v, int l, int r){
    if (l <= tl and r >= tr){
        return t[v];
    }
    if (tl >= r or tr <= l){
        return 0;
    }
    int mid = (tl + tr) / 2;
    return get(tl, mid, 2*v, l, r) + get(mid, tr, 2*v+1, l, r);
}

void set_(int tl ,int tr, int v, int ind, int val){
    if (tl + 1 == tr and tl == ind){
        t[v] = val;
        return;
    }
    if (ind < tl or ind >= tr) return;

    int mid = (tl + tr) / 2;
    set_(tl, mid, 2*v, ind, val);
    set_(mid, tr, 2*v+1, ind , val);
    update(v);
}

int main(){
    Fastio();
    int n, q; cin >> n;
    t.resize(4*n);
    a.resize(n);
    readArr(a)
    build(0, n, 1);
    cin >> q;
    fori(q){
        char c; int x, y;
        cin >> c >> x >> y;
        x--;
        if (c == 'q'){
            cout << get(0, n, 1, x, y) << eol;
        }else{
            set_(0, n, 1, x, y);
            //a[x] = y;
        }
    }

}