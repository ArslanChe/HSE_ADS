#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> prefix(string &s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

string s;

int Prefix() {
    cin >> s;
    vector<int> prefix_function = prefix(s);
    for (int i = 0; i < prefix_function.size(); ++i) {
        cout << prefix_function[i] << " ";
    }
    return 0;
}
