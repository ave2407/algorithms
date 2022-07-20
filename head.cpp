#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <stack>
#include <sstream>
#include <cstring>
#include <numeric>
#include <ctime>
#include <cassert>
#include <random>
#include <deque>
#include <valarray>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <deque>
#include <functional>
#include <list>

using namespace std;

#define re return
#define fi first
#define se second
#define mp make_pair
#define pb emplace_back
#define aint(x) x.begin(), x.end()
#define sz(x) ((int)(x).size())
#define mfor(i, start, end) for (int i = (start); i < (end); i++)
#define rep(i, n) for (int i = 0; i < (n); i++)
#define rrep(i, n) for (int i = (n) - 1; i >= 0; i--)
#define fiint(x, y) memset(x, y, sizeof(x))
#define sqr(x) ((x)*(x))
#define unq(x) (x.resize(unique(aint(x)) - x.begin()))
#define ba back()
#define popcount __builtin_popcountint
#define fastIO() {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
#define readArr(arr, n) {for (int i = 0; i < n; i++) cin >> arr[i];}
#define nl '\n'
#define uset unordered_set
#define umap unordered_map
#define deb(x) cout << #x << "=" << x << ' ';
#define debnl(x) cout << #x << "=" << x << '\n';
#define name(x) cout << #x << ' ';

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<vvii> vvvii;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef long long ll;
typedef unsigned long long uint;
typedef long double LD;
typedef double D;
typedef pair<D, D> pdd;
typedef pair<LD, LD> pldd;

template<class T> void print(T v) { cout << sz(v) << endl; for (auto x : v) cout << x << ' '; cout << endl; };
template<class T> void print2d(T v) { cout << sz(v) << endl; for (auto x : v) { print(x); } cout << endl; };
template<class T> void print1(T v) { cout << sz(v) << endl; for (auto x : v) cout << x + 1 << ' '; cout << endl; };
template<class T> void printpair(T v) { cout << sz(v) << endl; for (auto x : v) cout << '(' << v.fi << ' ' << v.se << ')' << ' '; cout << endl; };
template<class T1, class T2> ostream& operator << (ostream& o, pair<T1, T2> x) { re o << x.fi << ',' << x.se; }
template<class T1, class T2> istream& operator >> (istream& o, pair<T1, T2>& x) { re o >> x.fi >> x.se; }
template<class T1, class T2> pair<T1, T2> operator + (pair<T1, T2> a, pair<T1, T2> b) { a.fi += b.fi; a.se += b.se; re a; }
template<class T1, class T2> pair<T1, T2> operator - (pair<T1, T2> a, pair<T1, T2> b) { a.fi -= b.fi; a.se -= b.se; re a; }
template<class T1, class T2> void operator += (pair<T1, T2>& a, pair<T1, T2> b) { a.fi += b.fi; a.se += b.se; }
template<class T1, class T2> void operator -= (pair<T1, T2>& a, pair<T1, T2> b) { a.fi -= b.fi; a.se -= b.se; }
template<class T> vector<T> operator + (vector<T> a, vector<T> b) { a.insert(a.end(), b.begin(), b.end()); re a; }
template<class T> void operator += (vector<T>& a, vector<T> b) { a.insert(a.end(), b.begin(), b.end()); }

mt19937 rnd(12);

const int INF = 1e9 + 1;
const int mod = 1e9 + 7;
const int MAXN = 4001;