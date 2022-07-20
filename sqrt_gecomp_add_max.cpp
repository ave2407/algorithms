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

vll a, ans_b, push;
vvll blocks, sort_b;
int c, k;

void init(ll n){
    c = (int) ceil(sqrt(n));
    k = n/c+3;
    a.resize(n, 0);
    ans_b.resize(k, 0);
    push.resize(k, 0);
    blocks.resize(k, vll());
    sort_b.resize(k, vll());

    fore(i, 0, n){
        cin >> a[i];
        blocks[i / c].push_back(a[i]);
        ans_b[i / c] = max(a[i], ans_b[i / c]);
    }
}
ll Max(ll l, ll r){
    ll ans = 0;
    while(l <= r){
        if (l % c == 0 and l + c - 1 <= r){
            ans = max(ans, ans_b[l / c]);
            l += c;
            continue;
        }
        ans = max(ans, a[l] + push[l / c]);
        l++;
    }
    return ans;
}
void sett(ll i, ll val){
    ans_b[i / c] += val - a[i];
    blocks[i / c][i % c] = val;
    a[i] = val;
}

void add(ll l, ll r, ll val){
    while(l <= r){
        if (l % c == 0 and l + c - 1 <= r){
            ans_b[l/c] += val;
            push[l/c] += val;
            l += c;
            continue;
        }
        a[l] += val;
        ans_b[l/c] = max(a[l] + push[l/c], ans_b[l/c]);
        //blocks[l/c][l%c] += val;
        l++;
    }
}
int main(){
    Fastio();
    int n, m; cin >> n;
    init(n);
    cin >> m;
    fori(m){
        string s;
        ll x, y;
        cin >> s >> x >> y;
        x--; y--;
        if (s == "m") {
            cout << Max(x, y) << eol;
        }else{
            ll val; cin >> val;
            add(x, y, val);
        }
    }
}