#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <cassert>

using namespace std;

const int BITS_PER_HEX_DIGIT = 4;

vector<vector<int> > hexStringToBitMatrix(int n, const vector<string> &hexStrings) {
    int bitColumns = ceil(n / 4.0);
    vector<vector<int> > bitMatrix(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        string hexRow = hexStrings[i];
        int colIdx = 0;
        for (char hexDigit: hexRow) {
            bitset<BITS_PER_HEX_DIGIT> bits(stoul(string(1, hexDigit), nullptr, 16));
            for (int b = 0; b < BITS_PER_HEX_DIGIT && colIdx < n; ++b, ++colIdx) {
                bitMatrix[i][colIdx] = bits[BITS_PER_HEX_DIGIT - 1 - b];
            }
        }
    }

    return bitMatrix;
}

vector<vector<int> > multiplyMatrices(const vector<vector<int> > &A, const vector<vector<int> > &B, int n) {
    vector<vector<int> > C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] ^= (A[i][k] & B[k][j]);
            }
        }
    }
    return C;
}

bool compareMatrices(const vector<vector<int> > &A, const vector<vector<int> > &B, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (A[i][j] != B[i][j])
                return false;
        }
    }
    return true;
}

int Check() {
    int n;
    cin >> n;
    vector<string> hexA(n), hexB(n), hexC(n);
    for (int i = 0; i < n; ++i) cin >> hexA[i];
    for (int i = 0; i < n; ++i) cin >> hexB[i];
    for (int i = 0; i < n; ++i) cin >> hexC[i];
    vector<vector<int> > A = hexStringToBitMatrix(n, hexA);
    vector<vector<int> > B = hexStringToBitMatrix(n, hexB);
    vector<vector<int> > C = hexStringToBitMatrix(n, hexC);
    vector<vector<int> > computedC = multiplyMatrices(A, B, n);
    if (compareMatrices(computedC, C, n)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
