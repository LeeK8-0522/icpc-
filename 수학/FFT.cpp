#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cd;

const double PI = acos(-1);


// T(n) = 2 * T(n/2) + n => O(n lg n)
// (is invert ?) ? F -> f : f -> F
void FFT(vector<cd>& f, bool is_invert) { // input: 각 점에서의 다항식 값
    int len = f.size(); 

    if(len == 1) return; // 변환할 필요 X (상수항)

    vector<cd> even(len / 2);
    vector<cd> odd(len / 2);

    for(int i = 0; i < len/2; i++) {
        even[i] = f[2 * i];
        odd[i] = f[2 * i + 1];
    }

    FFT(even, is_invert);
    FFT(odd, is_invert);

    double theta = (2 * PI)/len; // 단위근의 각도 계산
    if(is_invert) theta *= -1;
    cd w(1, 0); // 초기 단계: 1 + 0 * i
    cd wn(cos(theta), sin(theta)); // cos(theta) + i * sin(theta)


    // 대칭성을 이용하여 조금 더 효율적으로 연산!
    for(int i = 0; i < len/2; i++) { // 결과 합치기.
        f[i] = even[i] + w * odd[i];
        f[i + len/2] = even[i] - w * odd[i];
        if(is_invert) {
            f[i] /= 2;
            f[i + len/2] /= 2;
        }
        w *= wn; // 다음 각도로
    } 
}


void multiply(vector<int>& A, vector<int>& B, vector<int>& result) { // A * B
    int len = 1;
    while(len < A.size() + B.size()) len <<= 1; // 2의 거듭제곱 꼴로 맞추기
    
    vector<cd> fa(A.begin(), A.end()); // A 다항식 계수 -> f
    vector<cd> fb(B.begin(), B.end()); // B 다항식 계수 -> f

    fa.resize(len); // 크기 확장하여 조정
    fb.resize(len);   

    // f(시간에 따른 진폭) -> F(신호) 
    FFT(fa, false); 
    FFT(fb, false);

    for(int i = 0; i < len; i++) fa[i] *= fb[i]; // 신호 합치기

    FFT(fa, true); // F -> f

    result.resize(len);
    for(int i = 0; i < len; i++) result[i] = round(fa[i].real());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m;
    cout << "Enter the degree of first polynomial (n): ";
    cin >> n;
    vector<int> a(n + 1);
    cout << "Enter the coefficients of first polynomial (from lowest degree to highest): ";
    for (int i = 0; i <= n; i++)
        cin >> a[i];

    cout << "Enter the degree of second polynomial (m): ";
    cin >> m;
    vector<int> b(m + 1);
    cout << "Enter the coefficients of second polynomial (from lowest degree to highest): ";
    for (int i = 0; i <= m; i++)
        cin >> b[i];

    vector<int> result;
    multiply(a, b, result);

    cout << "Resultant polynomial coefficients (from lowest degree to highest): ";
    for (int coeff : result)
        cout << coeff << " ";
    cout << endl;

    return 0;
}