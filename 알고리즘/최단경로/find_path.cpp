#include <bits/stdc++.h>
#define INF 1e9

using namespace std;

int V, E;
vector<vector<pair<int, int>>> edges;
vector<int> d;
vector<int> parent; // 최단 경로를 역추적하기 위해 각 노드의 부모를 저장
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

void init() {
    edges.resize(V + 1);
    d.resize(V + 1);
    parent.resize(V + 1, -1); // -1로 초기화하여 경로가 없는 경우를 처리

    for (int i = 0; i <= V; i++) d[i] = INF;
}

void relaxation(int u, int v, int w) {
    if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        parent[v] = u; // v의 부모 노드를 u로 설정
        Q.push(make_pair(d[v], v));
    }
}

void dijkstra(int s) {
    d[s] = 0;
    Q.push(make_pair(d[s], s));

    while (!Q.empty()) {
        int curr = Q.top().second, curr_dist = Q.top().first;
        Q.pop();

        if (curr_dist > d[curr]) continue; // 이미 최단 거리보다 큰 경우 무시

        for (auto& edge : edges[curr]) {
            int next = edge.first;
            int weight = edge.second;
            relaxation(curr, next, weight);
        }
    }
}

vector<int> get_path(int target) {
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end()); // 경로를 올바른 순서로 재배열
    return path;
}

int main() {
    cin >> V >> E;

    init();

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back(make_pair(v, w));
        // edges[v].push_back(make_pair(u, w)); // 무방향 그래프라면 이 줄 추가
    }

    dijkstra(1);

    cout << "Shortest path cost from node 1\n";
    for (int i = 1; i <= V; i++) {
        cout << i << ": " << d[i] << "\n";
    }

    cout << "\nPaths from node 1:\n";
    for (int i = 1; i <= V; i++) {
        if (d[i] < INF) {
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
