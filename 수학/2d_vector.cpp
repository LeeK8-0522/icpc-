#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
    인덱스는 항상 조심.... 진짜 찾기 힘들고 실수하고 또 실수한다.
*/

const double PI = 2.0 * acos(0.0); // pi 값

template <typename T>
struct vec2 {
    T x, y;

    vec2(T x = 0, T y = 0) : x(x), y(y) {}

    // 벡터 동일 여부
    bool operator == (const vec2<T>& r) const {
        return x == r.x && y == r.y;
    }

    // 정렬 기준
    bool operator < (const vec2<T>& r) const {
        return x != r.x ? x < r.x : y < r.y;
    }

    // 두 벡터 합 연산
    vec2<T> operator + (const vec2<T>& r) const {
        return vec2<T>(x + r.x, y + r.y);
    }

    // 두 벡터 차 연산
    vec2<T> operator - (const vec2<T>& r) const {
        return vec2<T>(x - r.x, y - r.y);
    }

    // 스칼라 실수 k배
    vec2<T> operator * (T k) const {
        return vec2<T>(x * k, y * k);
    }

    // 벡터 크기
    double norm() const {
        return hypot(x, y); // 피타고라스 정리로 벡터 크기 계산
    }

    // 정규화된 벡터 반환
    vec2<double> normalize() const {
        return vec2<double>(x / norm(), y / norm());
    }

    // 극좌표계에서의 각도
    double polar() const {
        return fmod(atan2(y, x) + 2 * M_PI, 2 * M_PI);
    }

    // 벡터 내적
    T dot(const vec2<T>& r) const {
        return x * r.x + y * r.y;
    }

    // 벡터 외적
    T cross(const vec2<T>& r) const {
        return x * r.y - y * r.x;
    }

    // 벡터 사영
    vec2<double> project(const vec2<T>& r) const {
        vec2<double> u = r.normalize();
        return u * u.dot(*this);
    }
};

// 벡터 버전 CCW (템플릿 적용)
template <typename T>
double ccw(const vec2<T>& a, const vec2<T>& b) {
    return a.cross(b); // a X b 외적 (양수: 반시계, 음수: 시계)
}

// 세 점 버전 CCW (템플릿 적용)
template <typename T>
double ccw(const vec2<T>& a, const vec2<T>& b, const vec2<T>& c) { // a -> b, b -> c
    return ccw(b - a, c - b); 
}

template <typename T>
void get_convex_hull(vector<vec2<T>>& coord, vector<vec2<T>>& hull) { // 정수 좌표일 때 convex hull 구하기
    int N = coord.size();
    sort(coord.begin(), coord.end());
    
    for(int i = 0; i < N; i++) {
        while(hull.size() >= 2 && ccw(hull[hull.size() - 2], hull[hull.size() - 1], coord[i]) >= 0) {
            hull.pop_back();
        }
        hull.push_back(coord[i]);
    }

    int upper_hull = hull.size();
    for(int i = N - 2; i >= 0; i--) {
        while(hull.size() >= upper_hull + 1 && ccw(hull[hull.size() - 2], hull[hull.size() - 1], coord[i]) >= 0) { // 위쪽 껍질은 건들지 않도록!
            hull.pop_back();
        }
        hull.push_back(coord[i]);
    }

    hull.pop_back(); // 처음 위치 중복 제거
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin>>N;
    vector<vec2<ll>> coord(N);
    for(int i = 0; i < N; i++) cin>>coord[i].x>>coord[i].y;

    vector<vec2<ll>> hull;
    get_convex_hull(coord, hull);
    cout<<hull.size();

    return 0;
}