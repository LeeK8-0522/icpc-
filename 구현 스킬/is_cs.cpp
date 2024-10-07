#include <bits/stdc++.h>
using namespace std;

/*
    구현 point: 
    - 두 문자열을 동시에 선형 탐색할 때, 
    비교 문자열의 요소가 다르다면, 원본 문자열 인덱스는 멈춘 채, 비교 문자열 인덱스를 일치할 때까지 증가
    같다면 둘 다 증가시키고 pass

    => 이 사실을 잘 관찰하면,
    같다면, idx2만 증가
    다르다면, idx1과 idx2 모두 증가
*/


bool is_cs(string& str1, string& str2) {
    if(str1.size() > str2.size()) return false;

    int idx1 = 0, idx2 = 0; // 투 포인터 응용 (알고리즘 정식 명칭은 X)
    while(idx1 < str1.size() && idx2 < str2.size()) {
        if(str1[idx1] == str2[idx2]) idx1++;
        
        idx2++;
    }
    return (idx1 == str1.size());
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    string str1, str2;
    cin>>str1>>str2;

    // is CS?
    if(is_cs(str1, str2)) cout<<"YES\n";
    else cout<<"NO\n";

    return 0;
}
