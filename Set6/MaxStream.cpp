#include <iostream>
#include <queue>
#include <climits>
#include <vector>

bool bfs(const std::vector<std::vector<int>> &graph, size_t s, size_t t, std::vector<size_t> &parent) {
    size_t n = graph.size();
    std::vector<bool> visited(n, false);
    std::queue<size_t> que;
    que.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!que.empty()) {
        size_t u = que.front();
        que.pop();
        for (size_t v = 0; v < n; v++) {
            if ((!visited[v]) && graph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                que.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

size_t find(std::vector<std::vector<int>> &graph, size_t s, size_t t) {
    size_t n = graph.size();
    size_t max_flow = 0;
    std::vector<std::vector<int>> tmp(n, std::vector<int>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            tmp[i][j] = graph[i][j];
        }
    }

    std::vector<size_t> parent(n);

    while (bfs(tmp, s, t, parent)) {
        int curr_flow = INT_MAX;
        size_t v = t;
        while (v != s) {
            size_t u = parent[v];
            curr_flow = std::min(curr_flow, tmp[u][v]);
            v = parent[v];
        }

        v = t;
        while (v != s) {
            size_t u = parent[v];
            tmp[u][v] -= curr_flow;
            tmp[v][u] += curr_flow;
            v = parent[v];
        }
        max_flow += curr_flow;
    }
    return max_flow;
}

int MaxStream() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n, std::vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph[u - 1][v - 1] = w;
    }

    std::cout << find(graph, 0, n - 1);

    return 0;
}
