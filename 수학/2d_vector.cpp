#include <bits/stdc++.h>
using namespace std;

const double PI = 2.0 * acos(0.0); // pi 값

struct vec2 { // 2차원 벡터
    double x, y;

    vec2(double x = 0, double y = 0) : x(x), y(y) {}
 
    bool operator == (const vec2& cmp) const { // 두 벡터 동일 여부
        return x == cmp.x && y == cmp.y;
    }

    bool operator < (const vec2& cmp) const { // 정렬 기준
        return x != cmp.x ? x < cmp.x : y < cmp.y;
    }

    vec2 operator + (const vec2& cmp) const { // 두 벡터 합 연산
        return vec2(x + cmp.x, y + cmp.y);
    }

    vec2 operator - (const vec2& cmp) const { // cmp -> x
        return vec2(x - cmp.x, y - cmp.y);
    }

    vec2 operator * (double k) const { // 실수 k배
        return vec2(x * k, y * k);
    }

    double norm() const {return hypot(x, y);}; // 벡터의 크기 (cf. 'hypot': 피타고라스 정리의 빗변의 길이)

    vec2 normalize() const { // 정규화된 벡터를 반환
        return vec2(x/norm(), y/norm()); 
    }

    double polar() const {return fmod(atan2(y, x) + 2 * PI, 2 * PI);}; // x축의 양의 방향과의 반시계 방향 각도 [0, 2 * pi) 

    double dot(const vec2& cmp) const { // 내적
        return x * cmp.x + y * cmp.y;
    }

    double cross(const vec2& cmp) const { // x X cmp 외적
        return x * cmp.y - y * cmp.x;
    }

    vec2 project(const vec2& cmp) const { // x를 cmp에 사영한 벡터 반환
        vec2 u = cmp.normalize();
        return u * u.dot(*this);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    return 0;
}