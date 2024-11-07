#include <bits/stdc++.h>
#define INF 1e9
using namespace std;
typedef pair<int, int> pii;

int V, E;
vector<int> dist;
vector<int> parent; // 각 노드의 부모를 저장
vector<vector<pii>> adj;

void dijkstra2(int src) {
    vector<bool> visited(V + 1, false); // 1-based index
    dist[src] = 0;
    visited[src] = false;
    parent[src] = -1; // 시작 노드는 부모가 없음

    while (1) {
        int closest = INF, here;
        for (int i = 1; i <= V; i++) {
            if (dist[i] < closest && !visited[i]) {
                here = i;
                closest = dist[i];
            }
        }

        if (closest == INF) break;

        visited[here] = true;
        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].first;
            if (visited[there]) continue;
            int next_dist = dist[here] + adj[here][i].second;
            if (next_dist < dist[there]) {
                dist[there] = next_dist;
                parent[there] = here; // 부모 노드 갱신
            }
        }
    }
}

vector<int> get_path(int target) {
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end()); // 경로를 올바른 순서로 정렬
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> V >> E;
    dist.resize(V + 1, INF);
    parent.resize(V + 1, -1); // 초기 부모를 -1로 설정
    adj.resize(V + 1);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        // adj[v].push_back({u, w}); // 무방향 그래프의 경우 필요
    }

    int start_node = 1; // 시작 노드
    dijkstra2(start_node);

    cout << "Shortest path cost from node " << start_node << "\n";
    for (int i = 1; i <= V; i++) {
        cout << i << ": " << dist[i] << "\n";
    }

    cout << "\nPaths from node " << start_node << ":\n";
    for (int i = 1; i <= V; i++) {
        if (dist[i] < INF) {
            vector<int> path = get_path(i);
            cout << "Path to " << i << ": ";
            for (int node : path) {
                cout << node << " ";
            }
            cout << "\n";
        } else {
            cout << "No path to " << i << "\n";
        }
    }

    return 0;
}
