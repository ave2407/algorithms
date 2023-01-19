#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include "deque"
#include "set"
#include <climits>
#include "cmath"

//#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")


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
    cout << "\n";
    for (auto el: v) { cout << el.first << " " << el.second << "\n"; }
}

#define readArr(arr) {for (auto & x: arr) cin >>x;}
#define fore(i, l, r) for(int i = int(l); i < int(r); i++)
#define fori(n) for (size_t i = 0; i < n; i++)
#define all(a) (a).begin(), (a).end()
#define fi first
#define se second
#define Fastio() {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
#define deb(x) cout << #x << " = " << x << '\n';
#define eol '\n'

//______________________________________________________________
struct node {
    int x1, y1, y2;
    bool open;
};

bool comp(node a, node b) {
    return a.x1 < b.x1 or (a.x1 == b.x1 and a.open);
}


const int MAXY = 1e6;
struct tnode {
    int mx, i;
};
tnode t[8 * MAXY];
int p[8 * MAXY];

tnode merge(tnode a, tnode b) {
    if (a.mx > b.mx or (a.mx == b.mx and a.i < b.i))
        return a;
    return b;
}

void push(int tl, int tr, int v) {
    if (tl + 1 == tr or p[v] == 0) return;

    p[2 * v] += p[v];
    p[2 * v + 1] += p[v];
    t[2 * v].mx += p[v];
    t[2 * v + 1].mx += p[v];

    p[v] = 0;
}


void build(int tl, int tr, int v) {
    if (tl + 1 == tr) {
        t[v] = {0, tl};
        return;
    }
    int mid = (tl + tr) / 2;
    build(tl, mid, 2 * v);
    build(mid, tr, 2 * v + 1);
    t[v] = merge(t[2 * v], t[2 * v + 1]);
}

tnode get_(int tl, int tr, int p, int l, int r) {
    push(tl, tr, p);
    if (l <= tl and tr <= r) {
        return t[p];
    }
    if (tl >= r or tr <= l)
        return {0, -1};
    int m = (tl + tr) / 2;
    return merge(get_(tl, m, 2 * p, l, r), get_(m, tr, 2 * p + 1, l, r));
}

void set_(int tl, int tr, int v, int l, int r, ll val) {
    push(tl, tr, v);
    if (l <= tl and tr <= r) {
        t[v].mx += val;
        p[v] += val;
        return;
    }
    if (tl >= r or tr <= l) return;

    int mid = (tl + tr) / 2;
    set_(tl, mid, 2 * v, l, r, val);
    set_(mid, tr, 2 * v + 1, l, r, val);
    t[v] = merge(t[2 * v], t[2 * v + 1]);
}

signed main() {
    Fastio();
    int n;
    cin >> n;
    vector<node> vert_lines;
    fori(n) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        y1+=MAXY;
        y2+=MAXY;
        vert_lines.push_back({x1, y1, y2, true});
        vert_lines.push_back({x2, y1, y2, false});
    }

    build(0, 2 * MAXY, 1);
//    for(auto x: t){
//        cout << x.mx << " " << x.i << eol;
//    }
    sort(all(vert_lines), comp);

    int max_x = -MAXY, max_y = -MAXY, ans = 0;
    for (auto line: vert_lines) {

        //cout << line.x1 << " " << line.y1 << " " << line.y2 << " " << line.open << eol;
        if (line.open) {
            set_(0, 2 * MAXY, 1, line.y1, line.y2 + 1, 1);
            push(0, 10, 1);
            tnode cur = merge(t[2], t[3]);//get_(0, 2 * MAXY, 1, 0, 2 * MAXY);
            //cout << cur.mx << " " << cur.i << eol;
            if (cur.mx > ans) {
                ans = cur.mx;
                max_x = line.x1;
                max_y = cur.i;
            }
        } else {
            set_(0, 2 * MAXY, 1, line.y1, line.y2 + 1, -1);

        }
    }
    cout << ans << eol;
    cout << max_x << " " << max_y - MAXY << eol;
}