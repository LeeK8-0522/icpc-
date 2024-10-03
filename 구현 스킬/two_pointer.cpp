#include <bits/stdc++.h>
using namespace std;

/*
    중복 O, 불연속적인 일반적인 배열에서 두 수의 합이 K가 되게 하는 조합의 수 세기

    구현 point:
    - 중복된 값에 대비하여 while문으로 warp! (이전 상태 기억해두는 변수 이용)
    
    주의! 값이 모두 동일하다면, n C 2
    (동일하다면, l_cnt, r_cnt는 각각 (전체 원소 개수), 0)

    But, what if 중복 조합..?
*/

/*
    인덱스 패턴: 
    - l < r
    - l++, r--
    - l < siz, r >= 0
    - l_cnt = 0, r_cnt = 0
*/

int two_pointer(vector<int>& arr, int K) {
    int cnt = 0; // 조합의 수
    int l = 0, r = arr.size() - 1;
    while(l < r) {
        int sum = arr[l] + arr[r];

        if(sum > K) {
            r--;
        } 
        else if(sum = K) {
            int l_val = arr[l]; 
            int r_val = arr[r]; // 값 기억해두기

            int l_cnt = 0;
            int r_cnt = 0;

            while(l < arr.size() && arr[l] == l_val) {
                l++;
                l_cnt++;
            }

            while(r >= 0 && arr[r] == r_val) {
                r--;
                r_cnt++;
            }

            if(l_val == r_val) cnt += (l_cnt * (l_cnt - 1)) / 2; // n C 2
            else cnt += l_cnt * r_cnt;
        }
        else {
            l++;
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin>>N;
    vector<int> arr(N);
    for(int i = 0; i < N; i++) cin>>arr[i];
    sort(arr.begin(), arr.end());

    int K; cin>>K;
    cout<<two_pointer(arr, K);

    return 0;
}
