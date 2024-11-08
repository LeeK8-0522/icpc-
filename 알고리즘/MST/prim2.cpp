#include <bits/stdc++.h>
#define INF 1e9

using namespace std;

/*
    일반적인 그래프에서 사용할 수 있도록 개선된 프림 알고리즘
    O(V^2) 시간 복잡도.
    역추적을 위해 parent 벡터를 추가하여 MST 구성 간선들을 추적할 수 있도록 함.
*/

int prim(int n, vector<vector<int>>& dist) {
    vector<int> min_weight(n, INF); // MST에 추가하는 데 드는 비용의 최솟값 저장
    vector<bool> visited(n, false); // MST 포함 여부
    vector<int> parent(n, -1); // 각 노드의 부모 노드 저장 (역추적용)
    int sum = 0;

    min_weight[0] = 0; // 시작 노드 비용 0 설정
    for(int iter = 0; iter < n; iter++) { // n개의 간선 선택
        int next = -1;
        // 최소 가중치 간선 선택
        for(int i = 0; i < n; i++) {
            if(!visited[i] && (next == -1 || min_weight[i] < min_weight[next])) next = i;
        }

        visited[next] = true;
        sum += min_weight[next];

        // 인접 노드 갱신
        for(int i = 0; i < n; i++) {
            if(!visited[i] && dist[next][i] < min_weight[i]) {
                min_weight[i] = dist[next][i];
                parent[i] = next; // 부모 노드 설정
            }
        }
    }

    // MST 구성 간선 출력
    cout << "Edges in the MST:\n";
    for(int i = 1; i < n; i++) { // 0번 노드 제외
        if(parent[i] != -1) {
            cout << parent[i] << " - " << i << " (Weight: " << dist[i][parent[i]] << ")\n";
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
    vector<vector<int>> dist(n, vector<int>(n, INF));

    // 그래프 입력 (정점 u, v와 가중치 w)
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = w;
        dist[v][u] = w; // 무방향 그래프
    }

    cout << "Total Weight of MST: " << prim(n, dist) << "\n";

    return 0;
}
