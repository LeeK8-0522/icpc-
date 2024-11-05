#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*  
    소인수분해 시간복잡도: O(N ^ 1/4)   vs  일반 소인수분해 시간복잡도: O(N ^ 1/2 * lg N)
    주의!) N이 합성수일 때 적용 가능 O
*/

ll f(ll x, ll c, ll N) {
    return (x * x + c) % N;
}

ll pollardRho(ll N) { // O(p ^ 1/2)
    if (N % 2 == 0) return 2; // 짝수라면 가장 작은 소인수: 2

    ll x = 2, y = 2, c = 1, d = 1;

    while (d == 1) { // (1, N) 범위의 d 찾기
        x = f(x, c, N);
        y = f(f(y, c, N), c, N);
        d = __gcd(abs(x - y), N); // |x - y|와 N의 최대 공약수 구하기

        if (d == N) { // 실패했으므로 다른 c로 재도전
            c++;
            x = 2;
            y = 2;
            d = 1;
        }
    }

    return d;
}

void factorize(ll N, vector<ll>& factors) {
    if (N <= 1) return; 

    if (N % 2 == 0) { // 짝수라면 홀수로 만들어주기
        factors.push_back(2);
        factorize(N / 2, factors);
        return;
    }

    // 소수 판별 O(N ^ 1/2)
    bool isPrime = true;
    for (ll i = 3; i * i <= N; i += 2) {
        if (N % i == 0) {
            isPrime = false;
            break;
        }
    }
    if (isPrime) {
        factors.push_back(N);
        return;
    }

    long long factor = pollardRho(N);
    factorize(factor, factors); // factor 인수분해
    factorize(N / factor, factors); // N/factor 인수분해
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N; cin >> N;
    vector<long long> factors;
    factorize(N, factors);

    // 인수들을 오름차순으로 정렬
    sort(factors.begin(), factors.end());

    cout << "Prime factors of " << N << " are: ";
    for (long long factor : factors) {
        cout << factor << " ";
    }
    cout << endl;
    

    return 0;
}
