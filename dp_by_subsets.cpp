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
#include <chrono>
#include "cmath"
#include "random"
#include "time.h"
#include "unordered_map"
#include "iomanip"
#include "bitset"

//#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")

//#define ll int

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
typedef pair<ll, ll> pll;


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
    for (auto el : v) {
        cout << el.first << " " << el.second << "\n";
    }
    cout << "\n";

}

#define Fastio() {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
#define fore(i, l, r) for (int i = int(l); i < int(r); i++)
#define unq(x) (x.resize(unique(all(x)) - x.begin()))
#define read(arr) {for (auto & x : arr) cin >> x;}
#define deb(x) cout << #x << " = " << x << '\n';
#define fori(n) for (int i = 0; i < n; i++)
#define sqr(x) (x)*(x)
#define all(a) (a).begin(), (a).end()
#define fi first
#define se second
#define eol '\n'

template<class T1, class T2>
ostream &operator<<(ostream &o, pair<T1, T2> x) { return o << x.fi << ',' << x.se; }

template<class T1, class T2>
istream &operator>>(istream &o, pair<T1, T2> &x) { return o >> x.fi >> x.se; }

mt19937_64 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());


//______________________________________________________________


// {x}   1 << x
// A объединение В   А | B
// A пересечение В   А & B
// A - B    A ^ (A&B)
// x принадлежит A    A & (1<<x) != 0


//for (int x = 0 ; x < (1<<n) ; ++x) {
//    int y = x;
//    while(y > 0) {// перебираем все подмножества х
//      ...
//      y = (y-1) & x;
//    }
//}




// найти минимальное число рюкзаков вместимость S чтобы уложить n с весом w[i]
signed main(){
    ll n, S; cin >> n >> S; // n - колво предметов, S - размер каждого из рюкзаков
    vll w(n);
    read(w);
    vll weights(1<<n);
    //предпосчитываем вес каждого подмножества
    for (int x = 0 ; x < (1<<n) ; ++x) {
        for (int i = 0; i < n; i++){
            if (x & (1<<i)){
                weights[x] += w[i];
            }
        }
    }

    vector<pair<ll, ll>> dp(1<<n, {n+1, S}); // колво рюкзаков и остаток в последнем рюкзаке для множества dp[i]
    fori(n){
        dp[(1<<i)] = {1, w[i]};
    }

    // перебираем все множества
    for (int x = 1 ; x < (1<<n) ; ++x) {
        for (int i = 0; i < n; i++){
            if (x & (1<<i)){
                auto a = dp[x ^ (x & (1 << i))];
                ll cnt = a.first, ost = a.second;
                if (ost + w[i] <= S){
                    ost +=  w[i];
                }else{
                    ost = w[i];
                    cnt++;
                }
                dp[x] = min(dp[x], {cnt, ost});
            }
        }
    }
    //print_pairs(dp);
    cout << dp[(1<<n)-1].first << eol;
}