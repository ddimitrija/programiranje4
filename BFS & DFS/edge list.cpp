#include <bits/stdc++.h>
using namespace std;

void bfs(int start, int n, vector<pair<int, int>>& edges) {
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for (auto edge : edges) {
            int u = edge.first;
            int v = edge.second;

            if (u == node && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }

            if (v == node && !visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
}

void dfs(int node, int n, vector<pair<int, int>>& edges, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (auto edge : edges) {
        int u = edge.first;
        int v = edge.second;

        if (u == node && !visited[v]) {
            dfs(v, n, edges, visited);
        }

        if (v == node && !visited[u]) {
            dfs(u, n, edges, visited);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    int start;
    cin >> start;

    bfs(start, n, edges);
    cout << endl;

    vector<bool> visited(n, false);
    dfs(start, n, edges, visited);

    return 0;
}