#include <bits/stdc++.h>
#define MAX_NUM 2000000
using namespace std;

/*
    세그먼트 트리적인 사고: 남긴 족적을 tracing 
*/

vector<int> tree(MAX_NUM * 5, 0); // 초기에는 어떠한 원소도 저장 X

void update(int sl, int sr, int idx, int x) { // idx -> [sl, sr] 표현 <=> [sl, sr] 구간 내의 원소 개수
    if(x < sl || x > sr) return; // 범위 밖이라면,

    tree[idx]++; // 해당 범위내에 원소 개수 추가
    if(sl == sr) return; // 리프 노드라면,

    int smid = sl + (sr - sl)/2;
    update(sl, smid, idx * 2, x);
    update(smid + 1, sr, idx * 2 + 1, x);
}

void update(int x) {
    update(1, MAX_NUM, 1, x);
}

int query(int sl, int sr, int idx, int x) {
    tree[idx]--; // 해당 범위 내에 있으므로 원소 개수 - 1
    if(sl == sr) return sl; // 리프 노드이므로 x번째로 작은 원소 반환
    
    int smid = sl + (sr - sl)/2;
    return (x <= tree[idx * 2]) ? query(sl, smid, idx * 2, x) : query(smid + 1, sr, idx * 2 + 1, x - tree[idx * 2]); 
}

int query(int x) {
    return query(1, MAX_NUM, 1, x); 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin>>N;
    while(N--) {
        int T, X; cin>>T>>X;
        if(T == 1) update(X);
        else cout<<query(X)<<"\n";
    }
    
    return 0;
}
