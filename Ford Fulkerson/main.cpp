#include <bits/stdc++.h>
using namespace std;

int dfs(int u, int sink, int flow, vector<vector<int>>& capacity, vector<bool>& visited, int n) {
    if (u == sink)
        return flow;

    visited[u] = true;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && capacity[u][v] > 0) {
            int pushed = dfs(v, sink, min(flow, capacity[u][v]), capacity, visited, n);

            if (pushed > 0) {
                capacity[u][v] -= pushed;
                capacity[v][u] += pushed;
                return pushed;
            }
        }
    }

    return 0;
}

int fordFulkerson(vector<vector<int>>& capacity, int source, int sink, int n) {
    int maxFlow = 0;

    while (true) {
        vector<bool> visited(n, false);
        int flow = dfs(source, sink, INT_MAX, capacity, visited, n);

        if (flow == 0)
            break;

        maxFlow += flow;
    }

    return maxFlow;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> capacity(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        capacity[u][v] += c;
    }

    int source, sink;
    cin >> source >> sink;

    cout << fordFulkerson(capacity, source, sink, n) << '\n';

    return 0;
}