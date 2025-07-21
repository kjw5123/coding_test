#include <iostream>
#include <deque>
#include <algorithm>
#include <utility>

using namespace std;
int n, k;
int zero_cnt = 0;
// deque 안 쓰면 바보인 문제인듯?
// 1 ~ N || N+1 ~ 2N 이렇게 앞뒤 있음
// 1에서 로봇 올리기 가능
// N에서 로봇 내리기 가능 (무조건임)
// 로봇을 올리거나 움직이면 해당 칸은 내구도 1 하락
//
// 특정 루틴을 반복한다 
// 1. 벨트가 로봇과 함께 회전
// 2. 벨트에 올라간 로봇부터, 회전하는 방향으로 이동 가능 시 이동, 불가능 하다면 이동 안한다 
// 불가능의 조건이란, 이동할 칸에 딴 로봇 있거나 내구도 1일 때
// 
// 3. 올리는 위치에 있는 칸 내구도가 0이 아니면 올림
// 4. 내구도 0인 칸 개수가 K개 이상이면 종료 
// 아니면 1로 복귀 

// 일단 bool로 로봇 유무 표현하자.
// 먼저 올라온 순서대로 한다고 하니, 
// 0 ~ N - 1 || N ~ 2N - 1 인덱스인데,
// N - 1부터 0 까지 이동 시키면 된다.

deque<pair<int, bool> > dq;

void rotate_dq() {
    pair<int, bool> last = dq.back();
    dq.pop_back();
    dq.push_front(last);
    if (dq.back().second == true) {
        dq.back().second = false;  // 내림
    }
}

void move_robot() {
    if (dq[n-2].second == true && dq[n-1].first >= 1) {
        dq[n-2].second = false;  // 짜피 내리는 자리라 push 안함
        if(--dq[n-1].first == 0) zero_cnt++;
    }

    for (int i = n - 3; i >= 0; i--) {
        if (dq[i].second == true && dq[i+1].second == false && dq[i+1].first >= 1) {
            dq[i].second = false;
            dq[i+1].second = true;
            if(--dq[i+1].first == 0) zero_cnt++;
        }
    }
}

void add_robot() {
    if (dq[0].first != 0) {
        dq[0].second = true;
        if (--dq[0].first == 0) zero_cnt++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    cin >> n >> k;
    int val;
    for (int i = 0; i < n * 2; i++) {
        cin >> val;
        dq.push_back({val, false});
    }
    int turn = 0;
    while (zero_cnt < k) {
        rotate_dq();
        move_robot();
        add_robot();
        turn++;
    }
    cout << turn << endl;
    return 0;
}
