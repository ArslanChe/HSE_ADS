#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void floyd_warshall(vector<vector<long long>> &graph) {
    int n = graph.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i][k] < 9223372036854775807 && graph[k][j] < 9223372036854775807)
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
}

int FloydWarshall() {
    int n, m;
    cin >> n >> m;

    vector<vector<long long>> graph(n, vector<long long>(n, 9223372036854775807));

    for (int i = 0; i < n; ++i)
        graph[i][i] = 0;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
    }

    floyd_warshall(graph);
    for (int u = 0; u < n ; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u == v) continue;
            graph[u][v] == 9223372036854775807 ? cout << u << " " << v << " -1\n" : cout << u << " " << v << " " << graph[u][v]
                                                                             << "\n";
        }
    }

    return 0;
}
