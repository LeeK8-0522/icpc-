#include <bits/stdc++.h>
using namespace std;

vector<int> factorization(int n) {
    vector<int> ret;
    int sqrt_n = (int)round(sqrt(n));
    for(int div = 2; div <= sqrt_n; div++) { // div * div <= n으로 해도 되는 듯
        cout<<"div: "<<div<<"\n";
        while(n % div == 0) {
            n /= div;
            cout<<"divide "<<div<<" -> "<<n<<"\n";
            ret.push_back(div);
        }
    }

    if(n > 1) ret.push_back(n); // 빼먹지 않도록 조심! (sqrt_n까지만 대칭적으로 고려했음)
    return ret;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin>>n;
    vector<int> f = factorization(n);
    for(auto e : f) cout<<e<<" ";

    return 0;
}
