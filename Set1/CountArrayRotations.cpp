#include <iostream>
#include <vector>
#include <set>

int HammingDistance(const std::vector<int> &arr1, const std::vector<int> &arr2) {
    int ans = 0;
    for (size_t i = 0; i < arr1.size(); ++i) {
        ans += arr1[i] != arr2[i] ? 1 : 0;
    }
    return ans;
}

int CountArrayRotations(const std::vector<int> &arr) {
    int n = arr.size();
    int ans = 0;
    std::set<std::vector<int>> rotations;

    for (int i = 0; i < n; i++) {
        std::vector<int> rotatedArr;
        for (int j = 0; j < n; j++) {
            rotatedArr.push_back(arr[(n - i + j) % n]);
        }
        rotations.insert(rotatedArr);
    }
    int maxHammingDistance = 0;
    for (const auto &rotatedArr: rotations) {
        int tmp = HammingDistance(arr, rotatedArr);
        if (tmp > maxHammingDistance) {
            maxHammingDistance = tmp;
            ans = 1;
        } else if (tmp == maxHammingDistance) {
            ans++;
        }
    }

    return ans;
}

int CAR() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t size;
    std::cin >> size;
    std::vector<int> array(size);
    for (size_t i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
    std::cout << CountArrayRotations(array);
    return 0;
}
