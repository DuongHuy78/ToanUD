#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

void convexHull(Point points[], int n)
{
    if (n < 3)
        return;
    Point* hull = new Point[n];
    int hullSize = 0;
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
    int p = l, q;
    do
    {
        hull[hullSize++] = points[p];
        q = (p + 1) % n;
        for (int i = 0; i < n; i++)
        {
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }
        p = q;

    } while (p != l);
    for (int i = 0; i < hullSize; i++)
        cout << "(" << hull[i].x << ", "
             << hull[i].y << ")\n";
}
int main()
{
    Point points[] = {1,25,14,1,25,0,17,12,18,6,14,7,3,9,23,0,8,9,6,16,21,19,2,16,17,12,14,12,11,18,18,12,14,22,9,2,4,7,4,13,21,5,1,7,9,1,7,12,2,21,24,6,16,21,5,19,18,11,20,18};
    // Point points[] = {
    // {0, 0}, {1, 1}, {2, 2}, {3, 3},
    // {3, 0}, {0, 3}, {1, 2}, {2, 1}
    // };
    int n = sizeof(points) / sizeof(points[0]);
    convexHull(points, n);
    return 0;
}
