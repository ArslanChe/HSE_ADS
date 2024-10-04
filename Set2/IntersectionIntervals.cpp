#include <iostream>
#include <vector>
#include <tuple>
#include <set>

using namespace std;

struct Interval {
    int left;
    int right;

    size_t length() const {
        return right - left + 1;
    }

    static Interval overlap(const Interval &a, const Interval &b) {
        int begin = max(a.left, b.left);
        int end = min(a.right, b.right);
        return begin <= end ? Interval{begin, end} : Interval{0, -1};
    }

    bool operator<(const Interval &other) const {
        return std::tie(left, right) < std::tie(other.left, other.right);
    }
};


void merge(vector<Interval> &intervals, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<Interval> leftArray(n1);
    vector<Interval> rightArray(n2);

    for (int i = 0; i < n1; i++) {
        leftArray[i] = intervals[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = intervals[middle + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].left <= rightArray[j].left) {
            intervals[k] = leftArray[i];
            i++;
        } else {
            intervals[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        intervals[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        intervals[k] = rightArray[j];
        j++;
        k++;
    }
}


void mergeSort(vector<Interval> &intervals, int left, int right) {
    if (left < right) {
        mergeSort(intervals, left, left + (right - left) / 2);
        mergeSort(intervals, left + (right - left) / 2 + 1, right);
        merge(intervals, left, left + (right - left) / 2, right);
    }
}

Interval find_ans(const std::vector<Interval> &intervals, size_t n) {
    Interval ans{0, -1};
    std::multiset<int> tmp;

    for (size_t i = 0; i < n; ++i) {
        while (!tmp.empty() && *tmp.begin() < intervals[i].left) {
            tmp.erase(tmp.begin());
        }
        if (!tmp.empty()) {
            Interval cur_overlap = Interval::overlap(intervals[i], {intervals[i].left, *tmp.rbegin()});
            if (cur_overlap.length() > ans.length()) {
                ans = cur_overlap;
            }
        }
        tmp.insert(intervals[i].right);
    }

    return ans;
}

int n;

int IntersectionIntervals() {

    cin >> n;
    vector<Interval> intervals(n);
    for (int i = 0; i < n; i++) {
        cin >> intervals[i].left >> intervals[i].right;
    }

    mergeSort(intervals, 0, intervals.size() - 1);
    Interval ans = find_ans(intervals, intervals.size());

    std::cout << ans.length() << "\n";
    if (ans.length() > 0) {
        std::cout << ans.left << " " << ans.right << "\n";
    }

    return 0;
}