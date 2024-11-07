#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
    구간합 lazy segment tree
    - 초기화: O(n)
    - 구간 & 점 갱신: O(lg n)
    - 구간 & 점 쿼리: O(lg n) 
*/

struct segment_tree {
    int n;
    vector<ll> tree;
    vector<ll> lazy;

    segment_tree(vector<ll>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        init(0, n - 1, 1, arr);
    }

    ll init(int sl, int sr, int idx, vector<ll>& arr) {
        if(sl == sr) return tree[idx] = arr[sl];

        int smid = sl + (sr - sl)/2;
        return tree[idx] = init(sl, smid, idx * 2, arr) + init(smid + 1, sr, idx * 2 + 1, arr);
    }

    void propagate(int sl, int sr, int idx) { // lazy하게 쌓여있던 업데이트 & 전파
        if(lazy[idx] != 0) {
            tree[idx] += (ll)(sr - sl + 1) * lazy[idx]; // 쌓여있던 lazy값 적용
            if(sl != sr) { // 밑으로 lazy값 flush!
                lazy[idx * 2] += lazy[idx];
                lazy[idx * 2 + 1] += lazy[idx];
            }
            lazy[idx] = 0; // 초기화
        }
    }

    ll query(int l, int r, int sl, int sr, int idx) {
        propagate(sl, sr, idx); // 해당 위치의 노드를 최신 상태로 업데이트
        if(r < sl || l > sr) return 0;
        if(l <= sl && sr <= r) return tree[idx];

        int smid = sl + (sr - sl)/2;
        return query(l, r, sl, smid, idx * 2) + query(l, r, smid + 1, sr, idx * 2 + 1);
    }

    ll query(int l, int r) {
        return query(l, r, 0, n - 1, 1);
    }

    ll update(int l, int r, ll value, int sl, int sr, int idx) {
        propagate(sl, sr, idx); // 최신 상태로 업데이트
        if(r < sl || l > sr) return 0;
        if(l <= sl && sr <= r) {
            tree[idx] += (ll)(sr - sl + 1) * value; // 업데이트
            // 밑의 자식에는 lazy하게 전파
            if(sl != sr) {  // <-- lazy 업데이트가 쌓여가는 곳
                lazy[idx * 2] += value;
                lazy[idx * 2 + 1] += value;
            }
            return tree[idx];
        }

        int smid = sl + (sr - sl)/2;
        return tree[idx] = update(l, r, value, sl, smid, idx * 2) + update(l, r, value, smid + 1, sr, idx * 2 + 1);
    }

    ll update(int l, int r, int value) {
        return update(l, r, value, 0, n - 1, 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin>>N;
    vector<ll> arr(N);
    for(int i = 0; i < N; i++) cin>>arr[i];
    segment_tree st(arr);

    int M; cin>>M;
    for(int i = 0; i < M; i++) {
        int Q; cin>>Q;
        if(Q == 1) {
            ll i, j, k; cin>>i>>j>>k;
            st.update(i - 1, j - 1, k);
        }
        else {
            int x; cin>>x;
            cout<<st.query(x - 1, x - 1)<<"\n";
        }
    }
    
    return 0;
}
