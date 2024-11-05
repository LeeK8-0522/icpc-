#include <bits/stdc++.h>
#define MULTIPLY(a, b, c) (((a % c) * (b % c)) % c)
#define K 10  // false positive 확률 : 1 / 1024 이하
using namespace std; 
typedef unsigned long long ll;

/*
    시간복잡도: O(k * lg N ^ 1/2)   vs  일반적인 소수 판별 시간복잡도: O(N ^ 1/2)
*/

ll power(ll a, ll d, ll n) { // a ^ d mod n 구하기
    if(d == 0) return 1;
    if(d == 1) return a % n;
    ll half = power(a, d/2, n);
    if(d % 2) return MULTIPLY(a, MULTIPLY(half, half, n), n);
    else return MULTIPLY(half, half, n);
}

bool miller_rabin(ll& a, ll& n) { // test 1 & 2
    ll s = 0;
    ll d = n - 1;
    while(d % 2 == 0) {
        d /= 2;
        s++;
    }

    // test 1
    ll base = power(a, d, n);
    if(base == 1) return true;

    // test 2
    for(ll i = 0; i < s; i++) {
        if(base == n - 1) return true;
        base = MULTIPLY(base, base, n); // r++
    }

    return false;
} 

bool is_prime(ll& n) { // 3 이상의 홀수에 대하여 소수 판별
    for(ll j = 0; j < K; j++) {
        ll a = rand() % (n - 3) + 2 ; // [2, n - 2]에서 임의로 선택 (1과 n - 1은 무의미한 테스트 -> 무조건 true)
        if(!miller_rabin(a, n)) return false;
    }

    return true;
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll n; cin>>n;
    bool flag = false;
    if(n == 1) flag = false;
    if(n == 2) flag = true;
    else if(n % 2 == 0) flag = false;
    else { // 3 이상의 홀수에 대해서 밀러-라빈 판별법 수행
        if(is_prime(n)) flag = true;
        else flag = false;
    } 

    if(flag) cout<<n<<" is prime number.\n";
    else cout<<n<<" is not prime number.\n";

    return 0;
}