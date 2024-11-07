#include <bits/stdc++.h>
#define INF 1e9

using namespace std;
typedef pair<int, int> pii;

vector<int> bellman_ford(vector<vector<pii>>& edges, int V, int E, int start) {
    vector<int> dist(V + 1, INF);
    vector<int> parent(V + 1);

    for(int i = 1; i <= V; i++) parent[i] = i; // parent 초기화

    dist[start] = 0;

    bool is_updated = false; 

    for(int i = 0; i < V - 1; i++) { // |V| - 1번 수행
        is_updated = false;
        for(int u = 1; u <= V; u++) {
            for(int i = 0; i < edges[u].size(); i++) { // 모든 간선에 대하여 수행
                int v = edges[u][i].first;
                int w = edges[u][i].second;

                if(dist[u] > dist[v] + w) { // relaxation 연산
                    dist[u] = dist[v] + w;
                    parent[u] = v;
                    is_updated = true;
                }
            }
        }

        if(!is_updated) break;
    }

    return parent;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int V, E;
    cin>>V>>E;
    int start, goal;
    cin>>start>>goal;
    vector<vector<pii>> edges(V + 1);
    for(int i = 0; i < E; i++) {
        int u, v, w;
        cin>>u>>v>>w;
        edges[u].push_back({v, w});
        //edges[v].push_back({u, w}); // if undirected graph,
    }

    vector<int> parent = bellman_ford(edges, V, E, start);

    // reconstruction
    vector<int> path;
    path.push_back(goal);
    int curr = parent[goal];
    while(curr != start) {
        path.push_back(curr);
        curr = parent[curr];
    }
    path.push_back(start);

    for(int i = 0; i < path.size(); i++) cout<<path[i]<<" "; // print path

    return 0;
}