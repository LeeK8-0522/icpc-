#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int V, E;
vector<int> parent;
vector<pair<int, pair<int, int>>> edges;
vector<pair<int, int>> mst_edges; // MST를 구성하는 간선을 저장

long long int ans = 0;

void initialize() {
    parent.resize(V + 1);
    for(int i = 1; i <= V; i++) parent[i] = i;
}

int find_root(int u) {
    if(u == parent[u]) return u;
    else return parent[u] = find_root(parent[u]);
}

void kruskal_algorithm() {
    sort(edges.begin(), edges.end());

    for(auto it : edges) {
        int cost = it.first;
        int u = it.second.first;
        int v = it.second.second;

        int root1 = find_root(u);
        int root2 = find_root(v);
        
        if(root1 != root2) {
            if(root1 < root2) parent[root2] = root1;
            else parent[root1] = root2;

            ans += cost;
            mst_edges.push_back({u, v}); // MST 간선을 저장
        }
    }
}

void print_mst() {
    cout << "Edges in the MST:\n";
    for(auto edge : mst_edges) {
        cout << edge.first << " - " << edge.second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> V >> E;

    initialize();

    for(int i = 0; i < E; i++) {
        int cost;
        int u, v;

        cin >> u >> v >> cost;
        edges.push_back(make_pair(cost, make_pair(u, v)));
    }

    kruskal_algorithm();
    cout << "Minimum cost: " << ans << "\n";
    print_mst();

    return 0;
}
