#include <iostream>
#include <algorithm>
#include <cfloat>
#include <cmath>
using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    };
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) const {
        return x != other.x && y != other.y;
    }
};

const int MAX_N = 1000;

// tính cross product
int cross(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// trả về số đỉnh hull (đã loại bỏ đỉnh lặp lại cuối)
int convex_hull(Point pts[], int n, Point ans[]) {
    if (n < 3) return 0;
    sort(pts, pts + n);
    int k = 0;
    // lower
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(ans[k-2], ans[k-1], pts[i]) <= 0) --k;
        ans[k++] = pts[i];
    }
    // upper
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && cross(ans[k-2], ans[k-1], pts[i]) <= 0) --k;
        ans[k++] = pts[i];
    }
    return k - 1;
}

// tính diện tích hull
double area(const Point hull[], int m) {
    double A = 0.0;
    for (int i = 0; i < m; ++i) {
        int j = (i + 1) % m;
        A += double(hull[i].x) * hull[j].y - double(hull[i].y) * hull[j].x;
    }
    return fabs(A) / 2.0;
}

// khoảng cách nhỏ nhất giữa các cạnh hull
double min_distance(const Point hull[], int m) {
    double dmin = DBL_MAX;
    for (int i = 0; i < m; ++i) {
        int j = (i + 1) % m;
        double dx = hull[i].x - hull[j].x;
        double dy = hull[i].y - hull[j].y;
        dmin = min(dmin, sqrt(dx*dx + dy*dy));
    }
    return dmin;
}

// liệt kê các điểm nằm trong
// trả về số điểm inside[]
int points_inside_hull(Point pts[], int n, Point hull[], int m, Point inside[]) {
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        bool isinside = true;
        for (int j = 0; j < m; ++j) {
            if (pts[i] == hull[j]) {
                isinside = false;
                break;
            }
        }
        if (isinside) {
            inside[cnt++] = pts[i];
        }
    }
    return cnt;
}

// khoảng cách nhỏ nhất giữa điểm inside và đỉnh hull
double min_distance_inside_hull(Point inside[], int ni, Point hull[], int m) {
    double dmin = DBL_MAX;
    for (int i = 0; i < ni; ++i) {
        for (int j = 0; j < m; ++j) {
            double dx = inside[i].x - hull[j].x;
            double dy = inside[i].y - hull[j].y;
            dmin = min(dmin, sqrt(dx*dx + dy*dy));
        }
    }
    return dmin;
}

int main() {
    // mảng đầu vào
    Point pts[MAX_N] = { {0,3}, {2,2}, {1,1}, {2,1}, {3,0}, {0,0}, {3,3} };
    int n = 7;

    // tính hull
    Point hull[2*MAX_N];
    int m = convex_hull(pts, n, hull);

    // in các đỉnh hull
    cout << "Convex hull points:\n";
    for (int i = 0; i < m; ++i)
        cout << "(" << hull[i].x << "," << hull[i].y << ")\n";

    // tính và in diện tích, min edge
    double A = area(hull, m);
    double me = min_distance(hull, m);
    cout << "Area of convex hull: " << A << "\n";
    cout << "Minimum edge length on hull: " << me << "\n";

    //inside
    Point inside[MAX_N];
    int ni = points_inside_hull(pts, n, hull, m, inside);

    // tính và in min distance between inside points và hull
    double mi = min_distance_inside_hull(inside, ni, hull, m);
    cout << "Minimum distance between inside points and hull points: " << mi << "\n";

    // in danh sách inside
    cout << "Points inside hull:\n";
    for(int i = 0; i < ni; ++i)
        cout << "(" << inside[i].x << "," << inside[i].y << ")\n";

    // in tổng kết
    cout << "Total points: " << n << "\n";
    cout << "Total on hull: " << m << "\n";
    cout << "Total inside or on hull: " << ni << "\n";
    cout << "Sum(on + strictly inside): " << m + ni - m << "\n";  // nếu muốn chỉ tính strictly inside, giảm m

    return 0;
}