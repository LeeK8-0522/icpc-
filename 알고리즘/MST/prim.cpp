#include <bits/stdc++.h>
#define INF 1e9

using namespace std;

/*
    O(E log V) 시간 복잡도의 프림 알고리즘.
    우선순위 큐를 사용하여 최소 가중치 간선을 효율적으로 선택.
    역추적을 위해 parent 벡터를 추가하여 MST 구성 간선을 추적할 수 있도록 함.
*/

int prim(int n, vector<vector<pair<int, int>>>& adj) {
    vector<int> min_weight(n, INF); // MST에 추가하는 데 드는 비용의 최솟값 저장
    vector<bool> inMST(n, false); // MST 포함 여부
    vector<int> parent(n, -1); // 각 노드의 부모 노드 저장 (역추적용)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // (weight, node)
    int sum = 0;

    // 시작 노드 설정
    min_weight[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        sum += min_weight[u];

        // 인접 노드 처리
        for (auto &[v, weight] : adj[u]) {
            if (!inMST[v] && weight < min_weight[v]) {
                min_weight[v] = weight;
                pq.push({weight, v});
                parent[v] = u; // 부모 노드 설정
            }
        }
    }

    // MST 구성 간선 출력
    cout << "Edges in the MST:\n";
    for (int i = 1; i < n; i++) { // 0번 노드 제외
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " (Weight: " << min_weight[i] << ")\n";
        }
    }

    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m; // n: 노드 수, m: 간선 수
    vector<vector<pair<int, int>>> adj(n);

    // 그래프 입력 (정점 u, v와 가중치 w)
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // 무방향 그래프
    }

    cout << "Total Weight of MST: " << prim(n, adj) << "\n";

    return 0;
}
