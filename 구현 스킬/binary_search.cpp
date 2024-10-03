#include <bits/stdc++.h>
using namespace std;

/*
    구현 point:
    - 'ans' 변수를 만들어서 이전 상태 기억해두기
    - 커지게 하고 싶다면, l = mid + 1
    - 작아지게 하고 싶다면, r = mid - 1
*/

/*
    인덱스 패턴:
    - l <= r
    - l = mid + 1
    - r = mid - 1
*/

// first occurence
int binary_search1(vector<int>& arr, int k) {
    int l = 0, r = arr.size() - 1;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l)/2;
        if(arr[mid] > k) r = mid - 1;
        else if(arr[mid] == k) {
            ans = mid;
            r = mid - 1; // 작아지게 하기
        }
        else l = mid + 1;
    }

    return ans;
}

// last occurence
int binary_search2(vector<int>& arr, int k) {
    int l = 0, r = arr.size() - 1;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l)/2;
        if(arr[mid] > k) r = mid - 1;
        else if(arr[mid] == k) {
            ans = mid;
            l = mid + 1; // 커지게 만들기
        }
        else l = mid + 1;
    }

    return ans;
} 

// least greater than k (upper bound)
int binary_search3(vector<int>& arr, int k) {
    int l = 0, r = arr.size() - 1;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l)/2;
        if(arr[mid] > k) {
            ans = mid;
            r = mid - 1; // 작아지게 만들기
        }
        else if(arr[mid] == k) l = mid + 1; // 커지게 만들기
        else l = mid + 1;
    }

    return ans;
} 

// greatest less than target 
int binary_search4(vector<int>& arr, int k) {
    int l = 0, r = arr.size() - 1;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l)/2;
        if(arr[mid] > k) r = mid - 1;
        else if(arr[mid] == k) r = mid - 1; // 작아지게 만들기
        else {
            ans = mid;
            l = mid + 1; // 커지게 만들기
        }
    }

    return ans;
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin>>N;
    vector<int> arr(N);
    for(int i = 0; i < N; i++) cin>>arr[i];
    sort(arr.begin(), arr.end());

    int k; cin>>k;
    cout<<binary_search1(arr, k)<<"\n"; // first occurence
    cout<<binary_search2(arr, k)<<"\n"; // last occurence
    cout<<binary_search3(arr, k)<<"\n"; // upper bound
    cout<<binary_search4(arr, k)<<"\n"; // lower bound

    return 0;
}
