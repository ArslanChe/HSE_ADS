#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <stack>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    vector<int> components;
    vector<bool> used;
    stack<int> stack1;

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V + 1);
        components.resize(V + 1, 0);
        used.resize(V + 1, false);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }


    void dfs(int v) {
        used[v] = true;
        for (int u : adj[v]) {
            if (!used[u]) {
                dfs(u);
            }
        }
        stack1.push(v);
    }

    void fillOrder() {
        for (int i = 1; i <= V; ++i) {
            if (!used[i]) {
                dfs(i);
            }
        }
    }

    void transpose() {
        vector<vector<int>> newAdj(V + 1);
        for (int i = 1; i <= V; ++i) {
            for (int u : adj[i]) {
                newAdj[u].push_back(i);
            }
        }
        adj = newAdj;
    }

    void dfsUtil(int v, int comp) {
        used[v] = true;
        components[v] = comp;
        for (int u : adj[v]) {
            if (!used[u]) {
                dfsUtil(u, comp);
            }
        }
    }

    void getSCC() {
        fillOrder();
        transpose();
        fill(used.begin(), used.end(), false);
        int comp = 1;
        while (!stack1.empty()) {
            int v = stack1.top();
            stack1.pop();
            if (!used[v]) {
                dfsUtil(v, comp++);
            }
        }
    }

    void printSCC() {
        int maxComp = *max_element(components.begin(), components.end());
        cout << maxComp << endl;
        for (int i = 1; i <= V; ++i) {
            cout << components[i] << " ";
        }
        cout << endl;
    }
};

int SortGraphCond() {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    g.getSCC();
    g.printSCC();
    return 0;
}
