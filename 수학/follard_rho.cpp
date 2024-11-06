#include <bits/stdc++.h>
#define MULTIPLY(a, b, c) (((a % c) * (b % c)) % c)
#define f(a, b, c) ((a * a + b) % c)
#define K 10 // false positive 확률 : 1 / 1024 이하
using namespace std;
typedef __int128 ll;

/*  
    64비트짜리 큰 수에 대한 소인수분해
    - 소수 판별: 밀러-라빈
    - 소인수분해: 폴라드 로 (한번에 하나의 소인수)
*/

////////////////////////////////////////////////////////////////////////
// __int128 출력 함수 (by chatGPT)
void printInt128(ll n) { // O(lg N) -> 최대 18번  
    if (n == 0) {
        cout << "0";
        return;
    }
    string result;
    bool isNegative = (n < 0);
    if (isNegative) n = -n;
    while (n > 0) {
        result.push_back((n % 10) + '0');
        n /= 10;
    }
    if (isNegative) result.push_back('-');
    reverse(result.begin(), result.end());
    cout << result;
}

// __int128 입력 함수 (by chatGPT)
ll readInt128() { // O(lg N) -> 최대 18번
    string s;
    cin >> s;
    ll result = 0;
    bool isNegative = (s[0] == '-');
    for (size_t i = (isNegative ? 1 : 0); i < s.size(); ++i) {
        result = result * 10 + (s[i] - '0');
    }
    return isNegative ? -result : result;
}
////////////////////////////////////////////////////////////////////////

ll power(ll a, ll d, ll n) { // a ^ d mod n 구하기
    if (d == 0) return 1;
    if (d == 1) return a % n;
    ll half = power(a, d / 2, n);
    if (d % 2) return MULTIPLY(a, MULTIPLY(half, half, n), n);
    else return MULTIPLY(half, half, n);
}

bool miller_rabin(ll& a, ll& n) { // test 1 & 2
    ll s = 0;
    ll d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    ll base = power(a, d, n);
    if (base == 1) return true;

    for (ll i = 0; i < s; i++) {
        if (base == n - 1) return true;
        base = MULTIPLY(base, base, n);
    }

    return false;
}

bool is_prime(ll& n) { // 3 이상의 홀수에 대하여 소수 판별
    // for edge case에서의 소수 판정 (1, 2, 3, 짝수)
    if(n == 1) return false; 
    if(n == 2 || n == 3) return true;
    if(n % 2 == 0) return false; // 4이상의 짝수는 소수가 X

    for (ll j = 0; j < K; j++) {
        ll a = rand() % (n - 3) + 2;
        if (!miller_rabin(a, n)) return false;
    }
    return true;
}

ll pollardRho(ll N) {  // 합성수에 대해서만 적용 가능 O
    if (N % 2 == 0) return 2; 

    ll x = 2, y = 2, c = 1, d = 1; // 편의상 x, y를 2로, c를 1로 초기화
    while (d == 1) {  // (1, N) 구간의 d 찾기
        x = f(x, c, N);  // x <- f(x)
        y = f(f(y, c, N), c, N);  // y <- f(f(y))
        ll diff = (x > y) ? x - y : y - x; // abs 사용하지 않기 위해
        d = __gcd(diff, N);

        if (d == N) {
            c++;  // 다른 c로 재도전
            x = 2; 
            y = 2;
            d = 1;
        }
    }

    return d;
}

void factorize(ll N, vector<ll>& factors) {
    if (N <= 1) return;  // 1은 무시

    if (N % 2 == 0) {  // 짝수라면,
        factors.push_back(2);
        factorize(N / 2, factors);
        return;
    }

    if (is_prime(N)) {  // 소수라면,
        factors.push_back(N);
        return;
    }

    ll factor = pollardRho(N);
    factorize(factor, factors);
    factorize(N / factor, factors);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N = readInt128();  
    if (N == 2 || is_prime(N)) { // 소수라면,
        printInt128(N);
        cout<<"\n";
        return 0;
    }

    vector<ll> factors;
    factorize(N, factors);
    sort(factors.begin(), factors.end());

    for (ll& e : factors) {
        printInt128(e);
        cout<<"\n";
    }

    return 0;
}
