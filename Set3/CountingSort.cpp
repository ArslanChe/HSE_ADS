#include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int> &arr) {
    int max = *std::max_element(arr.begin(), arr.end());
    int min = *std::min_element(arr.begin(), arr.end());
    int range = max - min + 1;

    std::vector<int> count(range);
    std::vector<int> ans(arr.size(), 0);

    for (int i = 0; i < arr.size(); ++i) {
        count[arr[i] - min]++;
    }

    for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }
    for (int i = arr.size() - 1; i >= 0; --i) {
        ans[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    arr = ans;
}

int CS() {
    int n;
    std::cin >> n;
    if(n == 0){
        return  0;
    }
    std::vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    countingSort(arr);

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    return 0;
}
