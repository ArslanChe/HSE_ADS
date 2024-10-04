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

void kmp(string &P, string &T) {
    string concatenated = P + '#' + T;
    vector<int> prefixFunction = prefix(concatenated);
    int pl = P.size();
    int tl = T.size();
    vector<int> ans;

    for (int i = 0; i < tl; ++i) {
        if (prefixFunction[pl + i + 1] == pl) {
            ans.push_back(i - pl + 1);
        }
    }
    cout << ans.size() << endl;
    for (auto pos: ans) {
        cout << pos << endl;
    }
}

int KnuthMorrisPratt() {
    string pattern, text;
    cin >> pattern >> text;

    kmp(pattern, text);

    return 0;
}
