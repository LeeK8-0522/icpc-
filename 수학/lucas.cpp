#include <bits/stdc++.h>
#define ADD(a, b, c) (((a%c) + (b%c))%c)
#define MULTIPLY(a, b, c) (((a%c) * (b%c))%c)
using namespace std;
typedef long long ll;

/*
    뤼카 정리: 
    소수 p진법으로 나타냈을 때,
    N = N(l)N(l-1) ... N(0)
    K = K(l)K(l-1) ... K(0)
    => (N, K) = (N(i), K(i))들의 곱

    시간복잡도: O(p ^ 2 + lg N)
    증명 idea:
    - N을 p진법으로 나타냈었을 때 (1 + x) ^ N 식 변형
    - 각각의 N(i)에 대한 x ^ K에 대한 계수를 생각
*/

ll N, K, M;
vector<vector<ll>> C;

void init() {
    for(int i = 0; i <= M; i++) C[i][0] = C[i][i] = 1; // 초기화 조심!

    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= i; j++) {
            C[i][j] = ADD(C[i-1][j], C[i-1][j-1], M);
        }
    }
}

void print_C() {
    for(int i = 0; i <= M; i++) {
        for(int j = 0; j <= i; j++) {
            cout<<C[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin>>N>>K>>M;
    C.resize(M + 1, vector<ll>(M + 1, 0));
    init(); 
    //print_C();
    ll ans = 1;
    while(N || K) {
        ans = MULTIPLY(ans, C[N%M][K%M], M);
        N /= M; K /= M;
    }

    cout<<ans;
   
    return 0;
}