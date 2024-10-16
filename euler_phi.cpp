#include <bits/stdc++.h>
using namespace std;

int euler_phi(int n) { // [1, n]에서 n과 서로소인 개수 (cf. 1은 1과도 서로소 O)
    double ret = n;
    int sqrt_n = (int)round(sqrt(n));
    for(int div = 2; div <= sqrt_n; div++) {
        if(n % div == 0) {
            ret *= (1 - (double)1/(double)div); // 1 - 1/p
            while(n % div == 0) {
                n /= div;
            }
        }
    }

    if(n > 1) ret *= (1 - (double)1/(double)n); // 빼먹지 않도록 조심! (sqrt_n까지만 대칭적으로 고려했으므로)
    return (int)round(ret);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin>>n;
    cout<<euler_phi(n);

    return 0;
}
