#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> findMinLength(const string &s) {
    int n = s.size();
    vector<int> lps(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = lps[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = lps[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        lps[i] = j;
    }

    return lps;
}

string p;

int Foundation() {
    cin >> p;
    cout << p.length() - findMinLength(p).back() << endl;
    return 0;
}
