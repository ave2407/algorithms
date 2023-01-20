struct Vector {
    long double x, y;

    long double len() {
        return sqrtl(x * x + y * y);
    }

    Vector operator+(Vector k) {
        return {x + k.x, y + k.y};
    }

    Vector operator-(Vector k) {
        return {x - k.x, y - k.y};
    }

    Vector operator/(long double k) {
        return {x / k, y / k};
    }

    Vector operator*(long double k) {
        return {x * k, y * k};
    }

    void norm() {
        long double l = len();
        x /= l;
        y /= l;
    }

    void set(long double k) {
        long double l = len();
        x /= l;
        y /= l;
        x *= k;
        y *= k;
    }
};

struct Line {
    long double a, b, c;
};

#define Point Vector

long double cross(Vector v1, Vector v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

long double dot(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

Vector make_vector(Point p1, Point p2) {
    return {p2.x - p1.x, p2.y - p1.y};
}

Line make_line(Point p1, Point p2) {
    Vector v = make_vector(p1, p2);
    long double a = v.y;
    long double b = -v.x;
    long double c = -p1.x * a - p1.y * b;
    return {a, b, c};
}

long double get_s(Point p1, Point p2, Point p3) {
    Vector v1 = make_vector(p1, p2);
    Vector v2 = make_vector(p1, p3);
    return abs(cross(v1, v2)) / 2;
}

long double dist(Point p1, Point p2) {
    return sqrtl((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool on_line(Point p, Line l) {
    long double f = l.a * p.x + l.b * p.y + l.c;
    if (abs(f) <= eps) return true;
    else return false;
}

bool cmpCH(Vector v1, Vector v2) {
    int c = cross(v1, v2);
    if (c != 0) {
        return c > 0;
    } else {
        return v1.len() < v2.len();
    }
}

vector <Point> convex_hull(vector <Point> v) {
    int n = v.size();

    int dl = 0;
    for (int i = 1 ; i < n ; i++) {
        if (v[i].x < v[dl].x || (v[i].x == v[dl].x && v[i].y < v[dl].y)) {
            dl = i;
        }
    }

    Vector delta = v[dl];

    for (int i = 0 ; i < n ; i++) {
        v[i] = v[i] - delta;
    }

    sort(v.begin(), v.end(), cmpCH);

    vector <Point> st;
    st.push_back({0, 0});

    for (int i = 0 ; i < v.size() ; i++) {
        while (st.size() > 1) {
            Point p = st[st.size() - 2];
            Point p1 = st[st.size() - 1];
            Point p2 = v[i];
            if (cross(make_vector(p, p1), make_vector(p, p2)) <= 0) {
                st.pop_back();
            } else {
                break;
            }
        }

        st.push_back(v[i]);
    }

    for (int i = 0 ; i < st.size() ; i++) {
        st[i] = st[i] + delta;
    }

    return st;
}
