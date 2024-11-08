    #include <bits/stdc++.h>
    using namespace std;

    /*
        위상 정렬 구현 방식 : dfs, bfs
    */

    int N, M;
    vector<vector<int>> adj;
    vector<bool> visited;

    /*
    void topological_sort() { // bfs 방식
        queue<int> Q;
        for(int i = 1; i <= N; i++) if(in_degree[i] == 0) Q.push(i); // 위상 정렬 시작 전,

        for(int iter = 0; iter < N; iter++) {
            if(Q.empty()) {
                cout<<"Cycle detected!\n";
                return;
            }

            int curr = Q.front();
            Q.pop();

            cout<<curr<<" ";

            for(auto next : adj[curr]) {
                in_degree[next]--;
                if(in_degree[next] == 0) Q.push(next);
            }
        }
    }
    */

    void dfs(int curr) { // dfs 방식
        visited[curr] = true;
        
        for(auto next : adj[curr]) {
            if(!visited[next]) dfs(next);
        }

        cout<<curr<<" ";
    }

    void dfs_all() {
        visited.resize(N + 1, false); // 초기화
        for(int i = 1; i <= N; i++) {
            if(!visited[i]) dfs(i);
        }
    }
    
    int main() {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        cin>>N>>M;
        adj.resize(N + 1);
        for(int i = 0; i < M; i++) {
            int u, v;
            cin>>u>>v;
            adj[v].push_back(u); // u < v 역으로 설정 (for dfs)
        }

        dfs_all();

        return 0;
    }