    #include <bits/stdc++.h>
    #define INF 1e9
    using namespace std;

    /*
        그 유명한 TSP NP-Hard 문제.

        비트마스크를 이용하여 O(2^N)이나 되는 공간복잡도를 O(1)로 줄임.

        핵심: dp[curr][mask] -> 현재 위치 curr이고 mask로 방문을 완료한 상태가 되도록 하는 최소 비용

        cf) [i][j]는 [ii][jj]에 의존하는데 i > ii, j > jj
        따라서 i, j 모두 증가하는 방향으로 테이블을 채워나가도록 한다.

        비트 연산자 우선순위에 주의하자! 일반적으로 우선순위가 낮다.
        1. 일반 산술 연산자
        2. <<, >>   시프트 
        3. &    AND
        4. ^    XOR
        5. |    OR
    */
    
    int main() {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        int N;
        cin>>N;
        vector<vector<int>> dist(N, vector<int>(N));
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                cin>>dist[i][j];
            }
        }

        vector<vector<int>> dp(N, vector<int>(1 << N, INF)); // 각 자리수 당 한 개의 도시
        // [i][mask] : 현재 i 도시에 있고 mask 상태로 도시들을 방문 완료하는데 드는 최소 비용

        dp[0][1] = 0; // 출발점
        for(int mask = 1; mask < (1 << N); mask++) { // 모든 상태에 대하여 탐색 (0번 도시는 이미 탐색함.)
            for(int curr = 0; curr < N; curr++) { // 현재 위치
                if(!(mask & (1 << curr))) continue; // 방문하지 않은 곳이라면,
                for(int next = 0; next < N; next++) {
                    if(mask & (1 << next)) continue; // 이미 방문한 상태라면,
                    if(dist[curr][next] != 0) dp[next][mask | (1 << next)] = min(dp[next][mask | (1 << next)], dp[curr][mask] + dist[curr][next]); 
                }
            }
        }

        // 마지막으로 돌아오는 비용
        int ans = INF;
        int mask = (1 << N) - 1;
        for(int i = 1; i < N; i++) {
            if(dist[i][0] != 0) ans = min(ans, dp[i][mask] + dist[i][0]);
        }

        cout<<ans;

        return 0;
    }