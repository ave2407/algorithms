#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "cmath"
#include "set"
#include "map"
#include <queue>
#include "list"
#include "iomanip"
#include "stack"

#pragma GCC optimize ("Ofast")

using namespace std;
typedef  unsigned long long ull;
typedef  long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
template <class T> void print(T & v){for (auto el: v){cout << el << " ";}cout << "\n";}
#define readArr(arr, n) {for (int i = 0; i < n; i++) cin >> arr[i];}
#define fore(i, l, r) for(int i = int(l); i < int(r); i++)
#define fori(n) for (size_t i = 0; i < n; i++)
#define all(a) (a).begin(), (a).end()
#define Fastio() {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
//#define INF 0x3f3f3f3f3f3f
const double EPS = 1e-9;
#define pi acos(-1.0)
#define eol '\n'

//#define int ll
#define double long double

struct point{
    double x, y;
};
struct line{
    double a, b, c;
};
struct vec{
    double x, y;
};

double dist(point a, point b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double psevd_vec_prod(vec a, vec b){
    return a.x * b.y - a.y * b.x;
}

double vect_prod(point a1, point b1, point a2, point b2){
    return (b1.x - a1.x) * (b2.y - a2.y) - (b1.y - a1.y) * (b2.x - a2.x);
}

double square(point a, point b, point c){
    return vect_prod(a, b, a, c) / 2;
}

double polar_angle(point p)
{
    double alpha = atan2(p.y, p.x);
    if (alpha < 0) alpha += 2 * pi;
    return alpha;
}
double vect_angle(vec a, vec b){
    return acos((a.x * b.x + a.y * b.y) / (sqrt((double)a.x * a.x + a.y * a.y) * sqrt((double)b.x * b.x + b.y * b.y)));
}

line get_line(double x1, double y1,double x2,double y2){
    line l{};
    l.a = y2 - y1;
    l.b = x1 - x2;
    l.c = x2*y1 - x1*y2;
    return l;
}
vec get_vec(point a, point b){
    vec v{b.x - a.x, b.y - a.y};
    return v;
}

line get_line_p(point a, point b){
    return get_line(a.x, a.y, b.x, b.y);
}
double square1(vector<point>& a){
    a.emplace_back(a[0]);
    double s = 0.0;
    for (int i = 1; i < a.size(); i++){
        s -= a[i-1].x * a[i].y;
        s += a[i-1].y * a[i].x;
    }
    return abs(s) / 2;
}
double dist_to_line(point p, line l){
    return abs(l.a * p.x + l.b * p.y + l.c) / sqrt(l.a*l.a + l.b*l.b);
}


double det(double a, double b, double c, double d) {
    return a * d - b * c;
}

bool intersect(line m, line n, point& res) {
    double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS)
        return false;
    res.x = -det(m.c, m.b, n.c, n.b) / zn;
    res.y = -det(m.a, m.c, n.a, n.c) / zn;
    return true;
}
bool is_in_line(point a, line n){
    return n.a*a.x + n.b*a.y + n.c < EPS;
}
bool is_in_ray(point p, point a, point b){
    return (p.x - a.x) * (b.x - a.x) >= 0 and (p.y - a.y) * (b.y - a.y) >= 0 and
           ((p.x - a.x) * (b.y - a.y) == (b.x - a.x) * (p.y - a.y));
}
bool is_in_segment(point p, point a, point b){
    return dist(p, a) + dist(p, b) == dist(a, b);
}
bool is_on_one_side(point a, point b, line n){
    return (n.a*a.x + n.b*a.y + n.c) * (n.a*b.x + n.b*b.y + n.c) >= 0;
}
double dist_point_to_ray(point p, point p1, point p2)
{
    vec v1 = get_vec(p1, p);
    vec v2 = get_vec(p1, p2);

    if (vect_angle(v1, v2) < pi / 2){
        return dist_to_line(p, get_line_p(p1, p2));
    }

    return dist (p, p1);
}

double two_vect_cos(vec a, vec b){
    return (a.x * b.x + a.y * b.y) / (sqrt((double)a.x * a.x + a.y * a.y) * sqrt((double)b.x * b.x + b.y * b.y));
}
double dist_to_seg(point p, point p1, point p2){
    vec v11 = get_vec(p1, p);
    vec v12 = get_vec(p1, p2);

    vec v21 = get_vec(p2, p);
    vec v22 = get_vec(p2, p1);

    double a1 = two_vect_cos(v11, v12);
    double a2 = two_vect_cos(v21, v22);

    if (a1 < 0 || a2 < 0){
        return min(dist(p, p1), dist(p, p2));
    } else {
        return dist_to_line(p, get_line_p(p1, p2));
    }
}

line get_bissectris(point x, point y, point z){
    double a = dist(x, y);
    double b = dist(x, z);
    double c = dist(y, z);
    double d = (a * c) / (b + a);
    //cout << d << eol;

    point p = {((z.x * d + (c - d) * y.x) / c), ((z.y * d + (c - d) * y.y) / c)};

    line bis = get_line_p(x, p);
    bis.a *= 2;
    bis.b *= 2;

    return bis;
}

double dist_seg_to_seg(point a1, point b1, point a2, point b2){
    line l1 = get_line_p(a1, b1);
    line l2 = get_line_p(a2, b2);

    if (!is_on_one_side(a1, b1, l2) && !is_on_one_side(a2, b2, l1)){
        return 0.0;
    }

    double a = min(dist_to_seg(a1, a2, b2), dist_to_seg(b1, a2, b2));
    double b = min(dist_to_seg(a2, a1, b1), dist_to_seg(b2, a1, b1));

    return min(a, b);
}


int main(){
    Fastio();
    freopen("line3.in", "r", stdin);
    freopen("line3.out", "w", stdout);
    double a, b, c, r;
    cin >> a >> b >> c >> r;
    cout << fixed << setprecision(6) << a << " " << b << " " << c+r*sqrt(a*a + b*b) << eol << a << " "<< b << " " << c-r*sqrt(a*a + b*b);
}
