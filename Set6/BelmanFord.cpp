#include <iostream>
#include <climits>
#include <cstdint>
#include "vector"
#include <map>

using namespace std;

class Vertex {
public:
    static inline vector<Vertex *> graph;
    long long index = 0;
    vector<long long> ne;
    vector<long long> wn;

    Vertex(long long data) : index(data) {
    }
};


int BelmanFord() {
    long long n, m;
    cin >> n >> m;
    if (!n) return 0;
    Vertex::graph = vector<Vertex *>(n);

    for (int i = 0; i < n; ++i) {
        Vertex::graph[i] = new Vertex(i);
    }

    long long w;
    long long u, v, c;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        Vertex::graph[v]->ne.push_back(u);
        Vertex::graph[v]->wn.push_back(w);
    }
    vector<long long> path = vector<long long>(n, LONG_LONG_MAX);
    path[0] = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c = Vertex::graph[j]->ne.size();
            for (int k = 0; k < c; ++k) {
                path[j] = path[Vertex::graph[j]->ne[k]] != LONG_LONG_MAX ? min(path[j],
                                                                               path[Vertex::graph[j]->ne[k]] +
                                                                               Vertex::graph[j]->wn[k])
                                                                         : path[j];
            }
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c = Vertex::graph[j]->ne.size();
            for (int k = 0; k < c; ++k) {
                if (path[j] >
                    path[Vertex::graph[j]->ne[k]] + Vertex::graph[j]->wn[k] ||
                    path[Vertex::graph[j]->ne[k]] == LONG_LONG_MIN) {
                    path[j] = LONG_LONG_MIN;
                    }
            }
        }
    }
    for (int i = 1; i < n; ++i) {
        path[i] == LONG_LONG_MIN ? cout << "-inf" << endl : cout << path[i] << endl;


    }
}