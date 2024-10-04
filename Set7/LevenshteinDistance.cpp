#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int task(string &s1, string &s2) {
    int m = s1.size();
    int n = s2.size();
    if (s1.size() > s2.size()) {
        return task(s2, s1);
    }
    vector<vector<int>> dop(m + 1, vector<int>(n + 1));
    for (int i = 0; i <= m; ++i) {
        dop[i][0] = i;
    }
    for (int j = 0; j <= n; ++j) {
        dop[0][j] = j;
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dop[i][j] = dop[i - 1][j - 1];
            } else {
                dop[i][j] = 1 + min({dop[i - 1][j], dop[i][j - 1], dop[i - 1][j - 1]});
            }
        }
    }
    return dop[m][n];
}

int n;

int LevenshteinDistance() {
    cin >> n;
    string s;
    getline(cin,s);
    vector<string> words(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        getline(cin,words[i]);
    }
    for (int i = 0; i < n; ++i) {
        cout << task(words[2 * i], words[2 * i + 1]) << " ";
    }

    return 0;
}
