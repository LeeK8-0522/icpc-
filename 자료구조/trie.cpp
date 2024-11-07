#include <bits/stdc++.h>
using namespace std;

/*
    삽입, 검색 시간복잡도: O(N)

    cf) 
    - nullptr: null 포인터
    - NULL:    null 포인터로, (void*)0
    - \0:      값이 0인 문자 리터럴. 문자열의 종료를 나타냄.
    - 0:       정수형 리터럴
*/

const int ALPHABETS = 26;

int to_number(char c) {return c - 'A';};

struct node { // 트라이 노드
    node* children[ALPHABETS];
    bool terminal; // 리프 노드인가?

    node() : terminal(false) {
        memset(children, 0, sizeof(children));
    }

    ~node() {
        for(int i = 0; i < ALPHABETS; i++) {
            if(children[i]) { // nullptr이 아니라면,
                delete children[i];
            }
        }
    }

    void insert(const char* key) { // 이 노드를 루트 노드로 하는 트라이에 key를 추가
        if(*key == 0) terminal = true;
        else {
            int next = to_number(*key);
            // 해당 자식이 없다면 생성하기
            if(children[next] == NULL) children[next] = new node();

            children[next]->insert(key + 1); // 다음 문자로 시작
        }
    }

    node* find(const char* key) { // 이 노드를 루트 노드로 하는 트라이에서 key에 대응되는 노드 찾기. 없다면 NULL 반환
        if(*key == 0) return this;
        int next = to_number(*key);
        if(children[next] == NULL) return NULL;
        return children[next]->find(key + 1);
    }
};