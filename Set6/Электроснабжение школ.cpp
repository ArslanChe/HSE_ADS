#include <vector>
#include <limits>
#include <iostream>

using namespace std;



static vector<vector<int>> createGraph(int n) {
    vector<vector<int>> result;
    result.resize(n, vector<int>(n, 0));
    return result;
}


static size_t findMinint(const vector<int> &key, const vector<bool> &mstSet) {
    size_t min_index = 0;
    int min_dist = numeric_limits<int>::max();
    for (size_t v = 0; v < key.size(); ++v) {
        if (!mstSet[v] && key[v] < min_dist) {
            min_dist = key[v];
            min_index = v;
        }
    }
    return min_index;
}

static vector<vector<int>> minSpanTree(vector<vector<int>> G) {
    size_t V = G.size();
    vector<int> parent(V);
    vector<int> key(V);
    vector<bool> mstSet(V, false);
    int i = 0;
    while (i < V) {
        key[i] = numeric_limits<int>::max();
        ++i;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; ++count) {
        int u = findMinint(key, mstSet);

        mstSet[u] = true;

        for (int v = 0; v < V; ++v) {

            if (G[u][v] && !mstSet[v] && G[u][v] < key[v]) {
                parent[v] = u;
                key[v] = G[u][v];
            }
        }
    }

    vector<vector<int>> mstGraph(V, vector<int>(V, 0));
    for (int i = 1; i < V; ++i) {
        mstGraph[parent[i]][i] = G[parent[i]][i];
        mstGraph[i][parent[i]] = G[parent[i]][i];
    }

    return mstGraph;
}

static vector<vector<int>> secondMinSpanTree(vector<vector<int>> G) {

    vector<vector<int>> min_span_tree = minSpanTree(G);

    vector<vector<int>> second_min_span_tree = min_span_tree;

    size_t V = G.size();
    int min_weight = 1e9;

    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (min_span_tree[i][j] > 0) {
                G[i][j] = 0;
                G[j][i] = 0;
                vector<vector<int>> tmp = minSpanTree(G);

                G[i][j] = min_span_tree[i][j];
                G[j][i] = min_span_tree[i][j];

                int weight = 0;
                int m = 0;
                while (m < V) {
                    for (int n = m + 1; n < V; ++n) {
                        weight += tmp[m][n];
                    }
                    ++m;
                }

                if (weight < min_weight) {
                    min_weight = weight;
                    second_min_span_tree = tmp;
                }
            }
        }
    }
    return second_min_span_tree;
}


int task() {
    int n, m, a, b, w;
    int i = 0;
    cin >> n >> m;

    vector<vector<int>> G = createGraph(n);

    while (i < m) {
        cin >> a >> b >> w;
        G[a - 1][b - 1] = w;
        G[b - 1][a - 1] = w;
        ++i;
    }

    size_t tmp = 0;
    size_t second_tmp = 0;

    for (const auto &cur_line: minSpanTree(G)) {
        for (const auto &cur_int: cur_line) {
            tmp += cur_int;
        }
    }
    for (const auto &cur_line: secondMinSpanTree(G)) {
        for (const auto &cur_int: cur_line) {
            second_tmp += cur_int;
        }
    }
    cout << tmp / 2 << " " << second_tmp / 2 << endl;
}
