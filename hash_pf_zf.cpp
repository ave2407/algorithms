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
typedef pair<int, int> pii;

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

vi z_function (string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    z[0] = n;
    return z;
}
vi p_function (string s) {
    int n = (int) s.length();
    vi pi (n);
    fore(i, 1, n) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])  ++j;
        pi[i] = j;
    }
    return pi;
}

//ll mod = 288228227;
ll mod = 1e9 + 7;
ll k = 139;
ll P[(int)1e6];

ll mult(ll x, ll y){
    return (x * y) % mod;
}

ll add(ll x, ll y){
    return (x + y) % mod;
}
void build_p(int n){
    P[0] = 1;
    fore(i, 0, n){
        P[i + 1] = mult(P[i], k);
    }
}

vll build_hash(string s){
    ll n = s.size();
    vll h(n+1, 0);
    h[0] = 0;
    fore(i, 0, n){
        h[i+1] = add(h[i], mult(s[i], P[i]));
    }
    return h;
}

ll get_hash(int l, int r, vll & h, int n) { // [l; r)
    return mult(h[r] - h[l] + mod, P[n - l]);
}

vll build_hash_rev(string s){
    ll n = s.size();
    vll h(n+1, 0);
    h[0] = 0;
    fore(i, 0, n){
        h[i+1] = add(mult(h[i], k), s[i]);
    }
    return h;
}

ll get_hash_rev(int l, int r, vll & h) { // [l; r]
    return (h[r] - mult(h[l-1], P[r-l+1]) + mod) % mod;

}

int main(){
    string sub, s; cin >> sub >> s;
    int n = s.size(), m = sub.size();
    build_p(n);

    vll h = build_hash(s);
    ll hs = mult(build_hash(sub)[m], P[n]);
    //cout << hs << eol;
    //print(h);
    vi ans;
    for (int l = 0; l <= n - m; l++){
        int r = l + m;
        //cout << l << " " << r << eol;
        ll cur_h = get_hash(l, r, h, n);

        if (cur_h != hs) continue;

        ans.push_back(l+1);
    }

    cout << ans.size() << eol;
    print(ans);
}