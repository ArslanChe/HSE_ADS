#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int BackpackWithCosts() {
    int N, M;
    cin >> N >> M;

    vector<int> m(N);
    vector<int> c(N);

    for (int i = 0; i < N; ++i) {
        cin >> m[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> c[i];
    }
    vector<vector<int>> dp(N + 1, vector<int>(M + 1, 0));
    for (int i = 1; i < N + 1; ++i) {
        for (int j = 0; j < M + 1; ++j) {
            if (m[i-1] <= j) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - m[i-1]] + c[i-1]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    cout << dp[N][M] << endl;

    return 0;
}
