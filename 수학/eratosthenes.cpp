#include <bits/stdc++.h>
using namespace std;

/*
    시간복잡도: O(n * lg lg n)
*/

void sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false; // 0, 1은 소수 X

    for (int i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // 소수 출력
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cout << "Enter the limit: ";
    cin >> n;
    sieveOfEratosthenes(n);

    return 0;
}
