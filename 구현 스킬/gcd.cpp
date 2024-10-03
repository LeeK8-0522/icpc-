#include <bits/stdc++.h>
using namespace std;

/*
    구현 point:
    - 이전 상태 기억해두는 변수 이용
    - 종결 조건: (a, 0) -> a
*/

/*
    인덱스 패턴:
    - 종결 조건: (a, 0) -> a
*/

int gcd(int a, int b) {
    while(b != 0) { // 종결 조건: (a, 0)
        int temp = b; // 이전 상태 기억해두기
        b = a % b;
        a = temp;
    }

    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n1, n2;
    cin>>n1>>n2;
    cout<<gcd(n1, n2);

    return 0;
}
