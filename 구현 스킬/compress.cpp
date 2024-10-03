#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

/*
    구현 point:
    - prev, cnt 기억
    - 만약 이전과 다른 값이 나온다면 flush!

    주의) for문이 끝나고 마지막 덩어리 flush해야 함.
*/

/*
    인덱스 패턴:
    - prev = arr[0]
    - cnt = 1
    - for(int i = 1; i < arr.size(); i++)
*/

vector<pii> compress(vector<int>& arr) {
    vector<pii> ret;

    if(arr.empty()) return ret;

    int prev = arr[0];
    int cnt = 1;
    for(int i = 1; i < arr.size(); i++) {
        if(arr[i] == prev) cnt++;
        else {
            ret.push_back({prev, cnt});
            prev = arr[i];
            cnt = 1;
        }
    }

    ret.push_back({prev, cnt}); // 마지막 처리

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin>>N;
    vector<int> arr(N);
    for(int i = 0; i < N; i++) cin>>arr[i];
    sort(arr.begin(), arr.end());

    vector<pii> compressed = compress(arr); 
    for(auto e : compressed) {
        cout<<e.first<<"("<<e.second<<") ";
    }

    return 0;
}
