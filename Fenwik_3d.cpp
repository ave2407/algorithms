#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef  long long ll;
typedef vector<long long> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;

#define Fastio() {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

ll n;
vvvll t;

int F(int i){
    return (i & (i+1)) - 1;
}

ll sum(int x, int y, int z){
    ll res = 0;
    int old_y = y, old_z = z;

    for( ; x >= 0; x = F(x)){
        for( ; y >= 0; y = F(y)){
            for( ;z >= 0; z = F(z)){
                //cout << "sum";
                res += t[x][y][z];
            }
            z = old_z;
        }
        y = old_y;
    }
    return res;
}

int E(int i){
    return i | (i + 1);
}

void update(int x, int y, int z, ll delta){
    int old_y = y, old_z = z;
    for (; x < n; x = E(x)){
        for (; y < n; y = E(y)){
            for (; z < n; z = E(z)){
                t[x][y][z] += delta;
            }
            z = old_z;
        }
        y = old_y;
    }
}


int main(){
    Fastio();
    int m;
    cin >> n;
    t.resize(n);
    for(int i = 0; i < n; i ++){
        t[i].resize(n);
        for (int j = 0; j < n; j++){
            t[i][j].resize(n);
        }
    }
    bool flag = true;

    while(flag){
        cin >> m;
        if(m == 1){
            int x, y, z;
            ll val;
            cin >> x >> y >> z >> val;
            update(x, y, z, val);
        }
        else if (m == 2){
            int lx, ly, lz, rx, ry, rz;
            cin >> lx >> ly >> lz >> rx >> ry >> rz;
            lx --;
            ly--;
            lz--;
            ll summ = sum(rx, ry, rz)
                      - sum(lx, ry, rz) - sum(rx, ly, rz) - sum(rx, ry, lz)
                      + sum(rx, ly, lz) + sum(lx, ry, lz) + sum(lx, ly, rz)
                      - sum(lx, ly, lz);
            cout << summ << endl;
        } else{
            flag = false;
        }
    }


}