#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

pii extended_gcd(int a, int b) {
    if (b == 0) return {1, 0}; // 편의상 y값을 0으로 설정. 당연히 임의의 값 가능. 
    
    int x0, y0;
    tie(x0, y0) = extended_gcd(b, a % b);

    int x, y;
    x = y0;
    y = x0 - (a / b) * y0;

    return {x, y};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int a, b;
    cin >> a >> b;

    int x, y;
    tie(x, y) = extended_gcd(a, b);
    cout << x << " " << y << endl;

    return 0;
}
