#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "numeric"
#include "set"
#include "cmath"
#include "iomanip"
using namespace std;

typedef  long long ll;
typedef vector<long long> vll;
typedef vector<int> vi;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;

#define read_arr(arr, n) {for (int i = 0; i < (n); i++) cin >> (arr)[i];}
#define Fastio() {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
#define eol '\n'

struct point{
    double x, y;
};
struct line{
    double a, b, c;
};
struct vec{
    double vx, vy;
};

double dist(point a, point b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double psevd_vec_prod(vec a, vec b){
    return a.vx*b.vy - a.vy*b.vx;
}

double vect_prod(point a1, point b1, point a2, point b2){
    return (b1.x - a1.x) * (b2.y - a2.y) - (b1.y - a1.y) * (b2.x - a2.x);
}
double square(point a, point b, point c){
    return vect_prod(a, b, a, c) / 2;
}


point base;
vector<point> env;

bool comp(point a, point b){
    return vect_prod(env[0], a, env[0], b) > 0 || (vect_prod(env[0], a, env[0], b) == 0 && dist(env[0], a) < dist(env[0], b));
}

int main()
{
    Fastio();
    double x1, y1, n;
    cin >> n;
    vector <point> points;

    cin >> base.x >> base.y;
    n--;
    while(n--){
        cin >> x1 >> y1;
        point a = {x1, y1};
        if (base.y > y1 || (base.y == y1 && x1 < base.x)){
            points.push_back(base);
            base = a;
        }else{
            points.push_back(a);
        }
    }
    env.push_back(base);
    sort(points.begin(), points.end(), comp);
    points.push_back(base);
    env.push_back(points[0]);

    for (size_t i = 1; i < points.size(); i++){
        while (vect_prod(env[env.size()-2], env[env.size()- 1], env[env.size() - 1], points[i]) < 0){
            env.pop_back();
        }
        env.push_back(points[i]);
    }
    //cout << endl << endl;
    double ans = 0, s = 0;
    //cout << env.size() << eol;
    for(size_t i = 1; i < env.size(); i++){
        //cout << env[i].x << " " << env[i].y << endl;
        ans += dist(env[i], env[i-1]);
        s += abs(square(env[0], env[i], env[i-1]));
    }
    cout <<ans << endl;
    cout << s << endl;
    return 0;
}