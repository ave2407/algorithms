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
vll t, p, a;

const int INF = 1e9;

ll merge(ll x, ll y){
    return max(x, y);
}

void push(int tl, int tr, int v){
    if (p[v] == 0) return; // no debt
    p[2*v] += p[v];
    p[2*v+1] += p[v];

    int mid = (tl + tr) / 2;
    t[2*v] += p[v];
    t[2*v+1] += p[v];
    p[v] = 0;
}



void build (int tl ,int tr, int v){
    if (tl + 1 == tr){
        t[v] = a[tl];
        return;
    }
    int mid = (tl + tr) / 2;
    build(tl, mid, 2*v);
    build(mid, tr, 2*v+1);
    t[v] = merge(t[2*v], t[2*v+1]);
}

ll get(int tl, int tr, int v, int l, int r){
    if (l <= tl and  tr <= r){
        return t[v];
    }
    if (tl >= r or tr <= l){
        return 0;
    }
    push(tl, tr, v);
    int mid = (tl + tr) / 2;
    return merge(get(tl, mid, 2*v, l, r),get(mid, tr, 2*v+1, l, r));
}

void set_(int tl ,int tr, int v, int l, int r, ll val){
    if (l <= tl and tr <= r){
        t[v] += val;
        p[v] += val;
        return;
    }
    if (tl >= r || tr <= l) return;

    push(tl, tr, v);
    int mid = (tl + tr) / 2;
    set_(tl, mid, 2*v, l, r, val);
    set_(mid, tr, 2*v+1, l, r, val);
    t[v] = merge(t[2*v], t[2*v+1]);
}

void print_seg_tree(int n){
    for (int i = 0; i < n; i++){
        cout << get(0,n, 1, i, i +1) << ' ';
    }
    cout << "\n......................\n";
}

int main(){
    //Fastio();
    int n, q; cin >> n;
    t.resize(4*n);
    p.resize(4*n);
    a.resize(n);
    readArr(a);
    build(0, n, 1);
    cin >> q;
    fori(q){
        char c;
        ll l, r, v;
        cin >> c >> l >> r;
        l--;
        if (c == 'a'){
            cin >> v;
            set_(0, n, 1, l, r, v);
            //print_seg_tree(n);
        }else{
            cout << get(0, n, 1, l, r) << eol;
        }
//        cout << i << eol;
//        print(t);
//        print(p);
//        cout << eol;
    }

}