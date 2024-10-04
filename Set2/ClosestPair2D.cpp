#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;

    [[nodiscard]] double euclideanDistance(const Point &other) const {
        return sqrt(
                pow(this->x - other.x, 2)
                + pow(this->y - other.y, 2)
        );
    }
};


bool compareX(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool compareY(const Point &a, const Point &b) {
    return a.y < b.y;
}

double closestPair(vector<Point> &points, int left, int right) {
    if (right - left <= 3) {
        double ans = 100000000000.0;
        for (int i = left; i <= right; ++i) {
            for (int j = i + 1; j <= right; ++j) {
                ans = min(ans, points[i].euclideanDistance(points[j]));
            }
        }
        return ans;
    }

    int mid = (left + right) / 2;
    double leftDistance = closestPair(points, left, mid);
    double rightDistance = closestPair(points, mid + 1, right);
    double minDistance = min(leftDistance, rightDistance);

    vector<Point> tmp;
    for (int i = left; i <= right; ++i) {
        if (abs(points[i].x - points[mid].x) < minDistance) {
            tmp.push_back(points[i]);
        }
    }

    sort(tmp.begin(), tmp.end(), compareY);
    int c = 0;
    for (size_t i = 0; i < tmp.size(); ++i) {
        for (size_t j = i + 1; j < tmp.size() && c < 6; ++j) {
            if (minDistance > tmp[i].euclideanDistance(tmp[j])){
                ++c;
                minDistance = tmp[i].euclideanDistance(tmp[j]);
            }
            

        }
    }
    return minDistance;
}

vector<Point> points;

int ClosestPair2D() {
    Point p{};
    int n = 0;

    while (cin >> p.x >> p.y) {
        points.push_back(p);
        ++n;
    }
    sort(points.begin(), points.end(), compareX);
    double minDistance = closestPair(points, 0, n - 1);

    cout << static_cast<int>(minDistance);

    return 0;
}