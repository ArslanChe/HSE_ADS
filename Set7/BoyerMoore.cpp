#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


vector<int> bmh(const string &P, const string &T) {
    vector<int> matches;
    int PLength = P.length();
    int TLength = T.length();
    if (PLength == 0 || TLength == 0 || PLength > TLength) {
        return matches;
    }
    unordered_map<char, int> shiftTable;
    for (int i = 0; i < PLength - 1; ++i) {
        shiftTable[P[i]] = PLength - i - 1;
    }
    int i = PLength - 1;
    while (i < TLength) {
        int j = PLength - 1;
        int k = i;
        while (j >= 0 && T[k] == P[j]) {
            --j;
            --k;
        }
        if (j == -1) {
            matches.push_back(i - PLength + 1);
        }
        i += shiftTable[T[i]] ? shiftTable[T[i]] : PLength;
    }

    return matches;
}

int BoyerMoore() {
    string P, T;
    getline(cin, P);
    getline(cin, T);

    vector<int> matches = bmh(P, T);

    cout << matches.size() << endl;
    for (int match: matches) {
        cout << match << endl;
    }

    return 0;
}
