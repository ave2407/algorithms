#include <iostream>
#include <vector>
#include <algorithm>
#include "set"
#include "map"
#include "cmath"

#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")

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


#define Fastio() {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
#define fori(n) for (int i = 0; i < n; i++)
#define sqr(x) (x)*(x)
#define eol '\n'


//______________________________________________________________

#define print_p(a) {for(auto p: a){cout << p.x << " " << p.y << eol;}cout << eol;}

ld eps = 1e-12;
ld pi = acos(-1);

struct Point{
    ld x, y;
    Point operator-(Point a) {return {x - a.x, y - a.y};}
    Point operator+(Point a) {return {x + a.x, y + a.y};}
    // в векторном произведении возможно переполнение int
    ll operator^(Point a) {return x * a.y - y * a.x;}
    bool operator==(Point a){return a.x == x && a.y == y;}
    bool operator<(const Point &a)  const {return a.y > y || (a.x > x && a.y == y);}
};

ll dist_sqrt(Point p) {
    return sqr(p.x) + sqr(p.y);
}

bool comp(Point a, Point b){
    return ((a ^ b) > 0) || ((a ^ b) == 0 && dist_sqrt(a) < dist_sqrt(b));
}

map <Point, bool> used;
map <Point, int> ind;
vi ans;

ll cur = 1;
vector<Point> convex_hull(vector<Point> points){
    Point p0 = points[0];
    for (Point p : points){
        if (p.y < p0.y or (p.y == p0.y and p.x < p0.x))
            p0 = p;
    }
    for (Point &x : points) {
        x.x -= p0.x;
        x.y -= p0.y;
    }
    sort(points.begin(), points.end(), comp);
    vector<Point> hull;
    for (Point p : points) {
        // удаляем последнюю точку МВО пока она образует невыпуклость (оператор "-" у точек должен быть перегружен, как и "^"
        /*
        Пусть т. A - последняя в оболочке, т. B - предпоследняя, т. C - точка, которую мы хотим добавить
        Тогда невыпуклость(или вырожденность) образуется, когда (C - A) ^ (B - A) <= 0
        */

        while (hull.size() >= 2 && ((p - hull.back()) ^ (hull[hull.size() - 2] - hull.back())) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }
    // переместим начало координат обратно
    for (Point &x : hull) {
        x = x + p0;
//        used[x] = true;
//        ans[ind[x]] = cur;
    }
    return hull;
}



signed main(){
    Fastio();
    int n; cin >> n;
    ans.resize(n);
    vector<Point> points, p2, env;
    fori(n){
        ld x, y;
        cin >> x >> y;
        points.push_back({x, y});
        used[{x, y}] = false;
        ind[{x, y}] = i;
    }

    while(points.size() > 2){
        env = convex_hull(points);
        cur++;
        //print_p(env);
        p2 = {};
        for(Point p: points){
            if (!used[p])
                p2.push_back(p);
        }
        points = p2;
    }
    for(Point p: points){
        ans[ind[p]] = cur++;
    }

    print(ans);
}
