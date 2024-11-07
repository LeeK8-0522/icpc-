    #include <bits/stdc++.h>
    #define INF 1e9
    #define TOKEN 

    using namespace std;

    void get_path(vector<int>& path, vector<vector<int>>& via, int n, int u, int v) { // u -> v
        if(via[u][v] == -1) {
            path.push_back(u);
            if(u != v) path.push_back(v);
        }
        else {
            int mid = via[u][v];
            get_path(path, via, n, u, mid); // u -> mid
            path.pop_back(); // mid 노드 중복 방지
            get_path(path, via, n, mid, v); // mid -> v
        }
    }

    void floyd_warshall(vector<vector<int>>& adj, int n) {
        vector<vector<int>> via(n + 1, vector<int>(n + 1, -1)); // u -> v 경로에서 경유하는 노드들 중 가장 큰 번호를 가진 노드(즉, 가장 마지막에 업데이트된 노드)

        for(int k = 1; k <= n; k++) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <=n; j++) {
                    if((i != j) && adj[i][k] != INF && adj[k][j] != INF && (adj[i][j] > adj[i][k] + adj[k][j])) {// 만약 i -> v에서 k 노드를 경유해야 한다면,
                        adj[i][j] = adj[i][k] + adj[k][j];
                        via[i][j] = k; // i -> j 경로에서 k 노드를 경유함. (경유하는 노드들 중 번호가 가장 큼.)
                    }
                }
            }
        }

        // 최단 거리 출력
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(adj[i][j] == INF) cout<<"0 ";
                else cout<<adj[i][j]<<" ";
            }
            cout<<"\n";
        }


        // 최단 경로 출력
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(adj[i][j] == INF) cout<<"0\n";
                else {
                    vector<int> path;
                    get_path(path, via, n, i, j);
                    cout<<path.size()<<" ";
                    for(auto e : path) cout<<e<<" ";

                    cout<<"\n";
                }
            }
        }
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        int n, m;
        cin>>n>>m;
        vector<vector<int>> adj(n + 1, vector<int>(n + 1, INF));
        for(int i = 0; i < m; i++) {
            int a, b, c;
            cin>>a>>b>>c;
            if(c < adj[a][b]) adj[a][b] = c;
        }

        floyd_warshall(adj, n); 

        return 0;
    }