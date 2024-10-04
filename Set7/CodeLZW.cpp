#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<int> encoding(string s1) {
    unordered_map<string, int> table;
    for (int i = 0; i <= 127; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s1[0];
    int code = 128;
    vector<int> ans;
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        } else {
            ans.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    ans.push_back(table[p]);
    return ans;
}

int CodeLZW() {

    string s;
    getline(cin, s);
    vector<int> ans = encoding(s);
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
