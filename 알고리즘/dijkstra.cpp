#include <bits/stdc++.h>
#define INF 1e9

using namespace std;

int V, E;
vector<vector<pair<int, int>>> edges;
vector<int> d;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;// STL의 'priority_queue' 자료형은 디폴트가 max heap

/* 필요한 자료구조 : 간선 정보 {[u] -> (v, w)}, 각 노드까지의 최단 경로 정보, 최단 경로에 대한 min heap {(d[i], i)}  */

void init() {
    edges.resize(V+1);
    d.resize(V+1);

    for(int i = 0; i < V + 1; i++) d[i] = INF;
}

void relaxation(int u, int v, int w) {
    if(d[v] > d[u] + w) {
        d[v] = d[u] + w;
        Q.push(make_pair(d[v], v));
    }
}

void dijkstra(int s) {// time complexity: O(E * T_dk + V * T_min) = O((E + V) * lg V)
    d[s] = 0;
    Q.push(make_pair(d[s], s));

    while(!Q.empty()) {
        int curr = Q.top().second, curr_dist = Q.top().first;
        Q.pop();

        if(curr_dist > d[curr]) continue; // 구현과 이론과의 차이!! (우선순위 큐의 decrease-key 연산 시간 복잡도는 O(1)가 아니므로 중복 발생 O)

        int adj_size = edges[curr].size();
        for(int i = 0; i < adj_size; i++) {
            int next = edges[curr][i].first;
            
            relaxation(curr, next, edges[curr][i].second);// relaxation step & decrease key
        }
    }
}

int main() {
    cin>>V>>E;

    init();

    for(int i = 0; i < E; i++) {
        int u, v, w;
        cin>>u>>v>>w;

        edges[u].push_back(make_pair(v, w));
        // edges[v].push_back(make_pair(u, w)); // <--- 무방향 그래프라면 빼먹지 않도록 조심!!
    }

    dijkstra(1);

    cout<<"shortest path cost from node 1\n";
    for(int i = 1; i <= V; i++) cout<<i<<": "<<d[i]<<"\n";

    return 0;
}