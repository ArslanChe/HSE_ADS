#include <iostream>
#include <string>
#include <stack>
#include <sstream>

std::string Decode(std::string &input) {
    std::stack<int> stckcol;
    std::stack<std::string> strstack;
    std::string ans;
    int col = 0;

    for (char c: input) {
        if (std::isdigit(c)) {
            col = c - '0';
        } else if (c == '[') {
            stckcol.push(col);
            strstack.push(ans);
            ans = "";
            col = 0;
        } else if (c == ']') {

            std::stringstream tmp;
            tmp << strstack.top();
            strstack.pop();
            int tmpcol = stckcol.top();
            stckcol.pop();
            while (tmpcol--) {
                tmp << ans;
            }
            ans = tmp.str();
        } else {
            ans += c;
        }
    }
    return ans;
}

int DecodeString() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::string input;
    getline(std::cin, input);
    std::cout << Decode(input) << std::endl;
    return 0;
}
