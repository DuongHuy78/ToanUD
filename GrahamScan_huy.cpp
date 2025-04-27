#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

void swap(Point& a, Point& b) {
    Point temp = a;
    a = b;
    b = temp;
}

double tichCoHuong(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dist2(Point a, Point b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

bool soSanh(Point O, Point a, Point b) {
    double tich = tichCoHuong(O, a, b);
    if (fabs(tich) < 1e-9)
        return dist2(O, a) < dist2(O, b); // So sánh khoảng cách nếu thẳng hàng
    return tich > 0;
}

int ccw(const Point& a, const Point& b, const Point& c) {
    int area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area > 0) return 1;   // Ngược chiều kim đồng hồ
    if (area < 0) return -1;  // Cùng chiều kim đồng hồ
    return 0;                 // Thẳng hàng
}

int GrahamScan(Point Points[], int n, Point out[]) {
    if (n < 3) return 0; // Không đủ điểm để tạo bờ lồi


    int min_idx = 0;
    for(int i = 1; i < n; i++) {
        if (Points[i].y < Points[min_idx].y || ((Points[i].y == Points[min_idx].y) && (Points[i].x < Points[min_idx].x))) {
            min_idx = i;
        }
    }
    swap(Points[0], Points[min_idx]);
    Point O = Points[0];

    for(int i = 1; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if (!soSanh(O, Points[i], Points[j])) {
                swap(Points[i], Points[j]);
            }
        }
    }

    int GrahamScanSize = 2;
    out[0] = Points[0];
    out[1] = Points[1];
    for(int i = 2; i < n; i++) {
        while(GrahamScanSize > 1 && ccw(out[GrahamScanSize - 2], out[GrahamScanSize - 1], Points[i]) <= 0) {
            GrahamScanSize--;
        }
        out[GrahamScanSize++] = Points[i];
    }
    return GrahamScanSize;
}
int main() {
    Point Points[] = {
        Point(-5, 2), Point(-1, 3), Point(-1, 8), Point(9, 5), Point(6, 2), 
        Point(9, 4), Point(12, 1), Point(9, -5), Point(5, -8), Point(5, -10),
        Point(1, -9), Point(2, -3), Point(-1, -7), Point(-6, -8), Point(-7, -4)
    };
    
    int n = sizeof(Points) / sizeof(Points[0]);

    Point res[n];
    int size = GrahamScan(Points, n, res);
    cout << "Graham Scan Convex Hull:\n";
    for (int i = 0; i < size; i++) {
        cout << "(" << res[i].x << ", " << res[i].y << ")\n";
    }
    return 0;
}
