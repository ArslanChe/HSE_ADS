#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countingSort(vector<long long> &arr, long long exp) {
    int n = arr.size();
    vector<long long> output(n);
    vector<long long> count(256, 0);

    for (int i = 0; i < n; ++i) {
        count[arr[i] / exp % 256]++;
    }

    for (int i = 1; i < 256; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        output[count[arr[i] / exp % 256] - 1] = arr[i];
        count[arr[i] / exp % 256]--;
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

void radixSort(vector<long long> &arr, int max) {

    long long exp = 1;
    while (max / exp > 0) {
        countingSort(arr, exp);
        exp *= 256;
    }
}

int RS() {
    int n;
    cin >> n;
    if (n == 0) {
        return 0;
    }
    vector<long long> arr(n);

    int tmp;
    for (int i = 0; i < n; i++) {
        std::cin >> tmp;
        arr[i] = tmp + 1000000000;
    }
    long long max = *max_element(arr.begin(), arr.end());
    radixSort(arr, max);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] - 1000000000 << " ";
    }
    return 0;


}