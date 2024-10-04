#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


void decoding(vector<int> op) {

    unordered_map<int, string> table;
    for (int i = 0; i <= 127; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = op[0], n;
    string s = table[old];
    string c = "";
    c += s[0];
    cout << s;
    int count = 128;
    for (int i = 0; i < op.size() - 1; i++) {
        n = op[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        } else {
            s = table[n];
        }
        cout << s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
}

int DecodeLZW() {

    int k;
    cin >> k;
    int ch;
    vector<int> output_code;
    for (int i = 0; i < k; ++i) {
        cin >> ch;
        output_code.push_back(ch);
    }
    decoding(output_code);
}
