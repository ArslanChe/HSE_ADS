#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    double cost;
    double weight;
    double unit_value;
    Item(double c, double w) : cost(c), weight(w) {
        unit_value = c / w;
    }
};

bool compareItems(const Item& a, const Item& b) {
    return a.unit_value > b.unit_value;
}

int Backpack() {
    int n;
    double W;
    cin >> n >> W;

    vector<Item> items;
    for (int i = 0; i < n; ++i) {
        double c, w;
        cin >> c >> w;
        items.emplace_back(c, w);
    }
    sort(items.begin(), items.end(), compareItems);

    double mx = 0.0;

    for (const auto& item : items) {
        if (W == 0) break;
        double amount = min(item.weight, W);
        mx += amount * item.unit_value;
        W -= amount;
    }
    cout << fixed << setprecision(3) << mx << endl;

    return 0;
}
