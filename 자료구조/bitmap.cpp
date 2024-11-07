#include <bits/stdc++.h>
using namespace std;

/*
    비트맵: n번째 비트 (2 ^ n) <-> 값 n인 요소가 존재하는지 유무
        
    필요한 메모리 크기 :
    비트마스킹 -> MAX_NUM / 8 (1B = 8bits)
    bool형 배열 -> MAX_NUM
    int형 set -> MAX_NUM * 4


    cf) 만약 k 길이의 1로만 이루어진 비트 패턴을 만들고 싶다면?
    : (1 << k) - 1
*/

class Bitmap {
private:
    std::vector<unsigned int> bits;
    size_t size;

public:
    // 생성자: 필요한 비트 수에 따라 벡터 크기 설정
    Bitmap(size_t n) : size(n) {
        bits.resize((n + 31) / 32, 0); // 32비트 단위로 저장
    }

    // 원소 추가
    void add(size_t x) {
        if (x >= size) return; // 범위 체크
        bits[x / 32] |= (1U << (x % 32));
    }

    // 원소 제거
    void remove(size_t x) {
        if (x >= size) return; // 범위 체크
        bits[x / 32] &= ~(1U << (x % 32));
    }

    // 원소 존재 여부 확인
    bool check(size_t x) const {
        if (x >= size) return false; // 범위 체크
        return bits[x / 32] & (1U << (x % 32));
    }

    // 원소 토글 (있으면 제거, 없으면 추가)
    void toggle(size_t x) {
        if (x >= size) return; // 범위 체크
        bits[x / 32] ^= (1U << (x % 32));
    }

    // 모든 원소 추가
    void all() {
        std::fill(bits.begin(), bits.end(), ~0U); // 모든 비트를 1로 설정
        size_t excess_bits = size % 32;
        if (excess_bits) { // 마지막 블록의 초과 비트 0으로 설정
            bits.back() &= (1U << excess_bits) - 1;
        }
    }

    // 모든 원소 제거
    void empty() {
        std::fill(bits.begin(), bits.end(), 0);
    }

    // 상태 출력 (디버깅용)
    void print() const {
        std::cout << "Current bits: ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << (check(i) ? "1" : "0");
        }
        std::cout << "\n";
    }
};
