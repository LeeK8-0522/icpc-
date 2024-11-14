#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cd;

/*
    in-place & 비재귀 => 시간복잡도는 동일하더라도 실행 속도 up!
*/

/*
    행렬적인 관점: (신호) = (w - 주파수 & 시간) * (시간에 따른 신호의 진폭)

    F = W * f
    f = (1/N) * W ^ -1 * F (역행렬 계산)

    pf) W * U = N * I
    즉, W ^ -1 = U/N
*/

const double PI = acos(-1);

void FFT(vector<cd>& a, bool invert) {
    int n = a.size();

    /*
        비트 반전 순서로 배열 재정렬 (재귀 호출할 때와 비재귀에서의 요소 접근 순서가 다름)
        ex) n = 8
        [0, 1, 2, 3, 4, 5, 6, 7] -> [0, 4, 2, 6, 1, 5, 3, 7]

        001(1) -> 100(4)
    */
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1; // n / 2
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;

        if (i < j) swap(a[i], a[j]);
    }

    // Cooley-Tukey FFT 알고리즘 (in place & 비재귀 알고리즘)
    for (int len = 2; len <= n; len <<= 1) { // 재귀 호출 시: 2, 4, 8, 16 ... 크기로 정복해나감
        long double theta = 2 * PI / len * (invert ? -1 : 1); // 단위 각 설정 : 2 * pi / len
        cd wn(cos(theta), sin(theta)); // cos + i * sin
        for (int i = 0; i < n; i += len) {
            cd w(1); // 1 + 0 * i
            for (int j = 0; j < len / 2; j++) {
                cd even = a[i + j];
                cd odd = a[i + j + len / 2]; // 재배열 후의 위치 (짝수는 절반 앞, 홀수는 절반 뒤)
                a[i + j] = even + w * odd;
                a[i + j + len / 2] = even - w * odd;
                w *= wn; // 다음 칸으로 이동
            }
        }
    }

    if (invert) for(cd& x : a) x /= n; // 역 FFT라면, 
}

void multiply(vector<int>& A, vector<int>& B, vector<int>& result) {
    int len = 1;
    while (len < A.size() + B.size()) len <<= 1;

    vector<cd> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    fa.resize(len);
    fb.resize(len);

    FFT(fa, false);
    FFT(fb, false);

    for (int i = 0; i < len; i++) fa[i] *= fb[i];

    FFT(fa, true);

    result.resize(len);
    for (int i = 0; i < len; i++) result[i] = lround(fa[i].real());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m;
    cout << "첫 번째 다항식의 차수 n을 입력하세요: ";
    cin >> n;
    vector<int> a(n + 1);
    cout << "첫 번째 다항식의 계수를 낮은 차수부터 높은 차수 순으로 입력하세요: ";
    for (int i = 0; i <= n; i++)
        cin >> a[i];

    cout << "두 번째 다항식의 차수 m을 입력하세요: ";
    cin >> m;
    vector<int> b(m + 1);
    cout << "두 번째 다항식의 계수를 낮은 차수부터 높은 차수 순으로 입력하세요: ";
    for (int i = 0; i <= m; i++)
        cin >> b[i];

    vector<int> result;
    multiply(a, b, result);

    cout << "결과 다항식의 계수 (낮은 차수부터 높은 차수 순): ";
    for (int i = 0; i < n + m + 1; i++)
        cout << result[i] << " ";
    cout << endl;

    return 0;
}
