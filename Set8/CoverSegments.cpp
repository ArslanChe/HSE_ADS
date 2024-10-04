#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    int start, end;
};

bool compareSegments(Segment a, Segment b) {
    return a.end < b.end;
}

int CoverSegments() {
    int n;
    cin >> n;

    vector<Segment> segments(n);

    for (int i = 0; i < n; ++i) {
        cin >> segments[i].start >> segments[i].end;
    }

    sort(segments.begin(), segments.end(), compareSegments);

    vector<int> points;
    int currentPoint = segments[0].end;
    points.push_back(currentPoint);

    for (int i = 1; i < n; ++i) {
        if (segments[i].start > currentPoint) {
            currentPoint = segments[i].end;
            points.push_back(currentPoint);
        }
    }

    cout << points.size() << endl;
    for (int point: points) {
        cout << point << " ";
    }
    cout << endl;

    return 0;
}
