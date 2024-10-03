#include <bits/stdc++.h>
using namespace std;

/*
    구현 point!
    - 각 자리수 임의 접근을 위해 string으로 변환.
    - power값을 점차적으로 증가시킴. (이전 상태 기억해두기)

    인덱스 헷갈리지 않도록 조심!
*/

/*
    인덱스 패턴:
    - for(int i = str.size() - 1; i >= 0; i--)
    - ret = 0
    - power = 1
    - num > 0
    - num /= N
*/

// N진법 -> 10진법
int to_decimal(int num, int N) { // 이미 int형 자체가 10진법
    int ret = 0;
    int power = 1;
    string str = to_string(num); // for random access (중요 구현 point!)
    for(int i = str.size() - 1; i >= 0; i--) {
        if(str[i] >= '0' && str[i] <= '9') ret += (int)(str[i] - '0') * power;
        else ret += (int)(str[i] - 'A') * power;

        power *= N;
    }

    return ret;
}

// 10진법 -> N진법
string from_decimal(int num, int N) { // 10진법이 넘어간다면 어쩔 수 없이 string 이용
    string ret = "";
    while(num > 0) {
        int r = num % N;
        if(r < 10) ret += (char)(r + '0'); // '+=' 연산자 지원
        else ret += (char)(r - 10 + 'A');

        num /= N;
    }

    reverse(ret.begin(), ret.end());

    return ret;
}

string conversion(int num, int N, int M) {
    int decimal_val = to_decimal(num, N);
    return from_decimal(decimal_val, M);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int num; 
    int N, M;
    cin>>num;
    cin>>N>>M;

    cout<<conversion(num, N, M);
    
    return 0;
}
