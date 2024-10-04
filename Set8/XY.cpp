#include <iostream>
using namespace std;

const int MOD = 1000000007;

int XY() {
    int N;
    cin >> N;

    if (N == 1) {
        cout << 2 << endl;
        return 0;
    }

    long long a = 1;
    long long b = 1;
    long long f = 2;

    for (int i = 2; i <= N; ++i) {
        long long new_a = f;
        long long new_b = a;
        f = (new_a + new_b) % MOD;
        a = new_a;
        b = new_b;
    }

    cout << f << endl;

    return 0;
}
