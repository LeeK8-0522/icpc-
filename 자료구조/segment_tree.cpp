#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
    조심! 리프 노드의 개수가 n개일 때 내부 노드의 개수는 항상 n - 1개이므로 이론적으론 총 2n - 1개의 노드가 필요.
    
    But, 1 index based로 하여 자식, 부모 노드를 2 * idx, 2 * idx + 1, idx / 2 꼴로 접근하는 자료구조에서는
    2 ^ (k - 1) < n < 2 ^ k에 대하여 2 ^ (k + 1)개의 노드가 필요함.
    2 ^ (k + 1) < 4 * n 이므로 넉넉하게 4 * n 크기로 메모리 할당.
*/

struct segment_tree {
    int n;  // 배열의 길이
    vector<ll> tree;
    segment_tree(vector<ll>& arr) {
        n = arr.size();
        tree.resize(n * 4);
        init(arr, 0, n - 1, 1);  // [0, n) 초기화 (단, 루트 노드는 1)
    }

    // top-down 방식 초기화
    // T(n) = 2 * T(n/2) + 1 이므로 O(n)
    ll init(vector<ll>& arr, int l, int r, int idx) { // 가정 : idx 노드 표현 범위 -> [l, r]
        if(l == r) return tree[idx] = arr[l]; // 리프 노드라면,
        
        int mid = l + (r - l)/2;
        ll left_result = init(arr, l, mid, idx * 2); // 왼쪽 서브 트리
        ll right_result = init(arr, mid + 1, r, idx * 2 + 1); // 오른쪽 서브 트리
        return tree[idx] = left_result + right_result; // 병합
    }

    // [l, r]과 [sl, sr] 교집합의 구간 합 반환
    /*
        핵심 성질: 두 서브 트리에 모두 걸쳐 있을 때 각각 한 쪽 자식은 탐색을 종료. => 최대 2번만 리프 노드에 접근 => O(lg n)

        또 다르게 생각하면, 위 성질에 의해 분할을 할 때 쿼리 범위가 절반이 되므로 T(n) = T(n/2) + 1 => O(lg n)
    */
    ll query(int l, int r, int sl, int sr, int idx) { // 가정 : idx 노드 표현 범위 -> [sl, sr]
        if(l > sr || r < sl) return 0; // 공집합이라면 결과에 무의미한 0을 반환
        if(l <= sl && r >= sr) return tree[idx]; // [sl, sr]이라면,

        int smid = sl + (sr - sl)/2;
        ll left_query = query(l, r, sl, smid, idx * 2); // 왼쪽 서브 트리
        ll right_query = query(l, r, smid + 1, sr, idx * 2 + 1); // 오른쪽 서브 트리
        return left_query + right_query;
    }

    ll query(int l, int r) { // overloading
        return query(l, r, 0, n - 1, 1);
    }

    ll update(int target, ll change, int l, int r, int idx) { // 가정 : idx 노드 표현 범위 -> [l, r]
        if(target < l || target > r) return tree[idx]; // 범위 밖이라면 변동이 없으므로 기존의 데이터 바로 return
        if(target == l && target == r) { // 목표물이라면 업데이트하고 반환
            return tree[idx] = change;
        }

        int mid = l + (r - l)/2;
        tree[idx] = update(target, change, l, mid, idx * 2) + update(target, change, mid + 1, r, idx * 2 + 1);  // [l, mid] & (mid, r] 병합
        return tree[idx];
    }

    ll update(int target, ll change) { // overloading
        return update(target, change, 0, n - 1, 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, M, K;
    cin>>N>>M>>K;
    vector<ll> arr(N); // 자료형 범위 조심하고 또 조심!!
    for(int i = 0; i < N; i++) cin>>arr[i];
    segment_tree st(arr);
    for(int i = 0; i < M + K; i++) {
        ll a, b, c;
        cin>>a>>b>>c;
        if(a == 1) { // update
            b--;  // index based
            st.update(b, c);
        }
        else if(a == 2) { // find
            b--;  // index based
            c--;
            cout<<st.query(b, c)<<"\n";
        }
    }

    return 0;
}