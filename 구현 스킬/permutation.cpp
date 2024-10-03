#include <bits/stdc++.h>
using namespace std;

/*
    구현 point:
    - dfs(백트래킹) 구현의 핵심 구현: root 노드로부터 가능한 모든 서브 트리를 순회한 후에 return 및 backtracking!
*/

/*
    인덱스 패턴:
    - l == r
*/

void get_permutation(vector<int>& arr, int l, int r) { // [l, r] 구간 순열 만들기
    if(l == r) { // 더 이상 만들 수 있는 순열이 없다면,
        for(auto e : arr) cout<<e<<" ";
        cout<<"\n";
        return;
    }

    for(int i = l; i <= r; i++) {
        swap(arr[l], arr[i]);
        get_permutation(arr, l + 1, r);
        swap(arr[i], arr[l]); // 백트래킹
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin>>N;
    vector<int> arr(N);
    for(int i = 0; i < N; i++) cin>>arr[i];

    get_permutation(arr, 0, arr.size() - 1);

    return 0;
}
