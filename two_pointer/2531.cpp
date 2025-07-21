#include <iostream>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;

// 문제 어휴 왤케 길어
//
// 회전초밥집임
// 시계 방향으로 돎
// 각 초밥의 종류는 번호로 표기함
// 같은 종류가 트레일러 위에 여러개 있을 수 있음
// 손님은 자기가 좋아하는 초밥 골라 먹음
//
// 사장님이 삶이 힘듦
// 행사 2가지 해서 판매 촉진 할거
//
// 1. 원래는 손님이 맘대로 고르고 그거대로 계산했는데
//    벨트 임의 위치로부터 k개 접시 연소개서 먹으면 할인된 정액가격으로 쳐줌
//
// 2. 고객한테 초밥 종류 한개 쓰인 쿠폰 주고
//    1번 행사 참가한 경우엔 이 쿠폰에 적힌 종류 초밥 하나 공짜로 제공함
//    만약그 초밥이 지금 벨트에 없으면 따로 만들어 제공해줌 
//
// 난 다양한 종류 초밥 먹고 싶음
// 
// 음식점 벨트 상태
// 메뉴 상 초밥 가짓 수
// 연속해서 먹는 접시 수 
// 쿠폰 번호 
//
// 주어졌을 때 내가 먹을 수 있는 최대 가짓수를 구해보거라.

// 벨트 위 접시 수 n
// 초밥 종류       d
// 연속해서 먹는 접시 수 k
// 쿠폰 번호       c
//
//
int n, d, k, c;
int table[60001];
int cnt[3001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> d >> k >> c;
    
    for (int i = 0; i < n; i++) cin >> table[i];
    for (int i = n; i < n + k; i++) table[i] = table[i-n];

    // 걍 set 쓰면 만사 ok 아닌가?????????????
    // 아 erase 하면 중복 다 날라가는구나 
    // int cnt[] 하면 되겠음 ㅇㅇ ㄱ

    int cnts = 0; int maxVal = INT_MIN;
    int minIdx = 0; cnt[c] = 100000;  // 입력이 많은 것도 아닐 뿐더러, 쿠폰은 늘 활성화 되어야 하니 대충 100000넣어줬다
    set<int> s; s.insert(c);

    for (int i = 0; i < n + k; i++) {
        if (cnts != k) {
            int food_num = table[i];

            s.insert(food_num);
            maxVal = max(maxVal, (int)s.size());
            cnt[food_num]++;
            cnts++;

        } else {
            int popFoodNum = table[minIdx++];
            int food_num = table[i];

            s.insert(food_num);
            cnt[food_num]++;

            if (--cnt[popFoodNum] == 0) s.erase(popFoodNum);

            maxVal = max(maxVal, (int)s.size());

        }
    }
    cout << maxVal << endl;
    
    return 0;
}
