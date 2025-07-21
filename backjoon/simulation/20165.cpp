#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// 노 종이 이슈로 여기에 풀이 진행
// N M 사이즈 판에 도미노 세움 (도미노 길이는 1 ~ 5)
// 매 라운드 공격수는 공격, 수비는 이후 수비 진행
//
// 공격수는 특정 격자에 놓인 도미노를 동 서 남 북 아무데나 넘어뜨림
// 길이 k인 도미노가 넘어지면 k-1개의 도미노들 중 안넘어진 것들이
// 같은 방향으로 연달아 넘어진다
// 이거는 선형 탐색 스윽~ 하면서 최대값 갱신 하고
// 갱신 없으면 -- 슥슥 해주면 될듯 싶음
// 이미 넘어진거 픽 하면 아무일도 일어나지 않는다
//
// 수비수는 넘어진거 다시 세울 수 있다
// 서있는거 고르면 아무일도 발생하지 않음
//
// R 라운드 간 위 공수 반복
//
// 매 라운드, 공격수가 해당 라운드에 넘어뜨린 도미노 게수를 셈
// 다 합친게 공격수의 점수다

// 재귀쓸까?

int n, m, r;
int x, y;  // 말을 왤케 꼬았어 ㅡㅡ
char dir;
// 넘어진건 F로, 서있는건 S로 
int arr[101][101];
bool state[101][101];  // stand == false, 넘어짐 == true
int result = 0;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int dir2idx(char dir) {
    switch(dir) {
        case 'N':
            return 0;
        case 'E':
            return 1;
        case 'S':
            return 2;
        case 'W':
            return 3;
    }
    return 0;
}

void state_output() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << ((state[i][j] == false) ? 'S' : 'F') << " ";
        }
        cout << '\n';
    }
}

void fall_domino(int direction) {  // 매개변수 필요없긴하네
    if (state[y][x] == true) return;

    int dist = arr[y][x] - 1;  // 초기 넘어질 길이
    result += 1;
    state[y][x] = true;
    while (dist != 0) {
        y += dy[direction];
        x += dx[direction];
        dist--;
        if ( y <= 0 || y > n || x <= 0 || x > m ) break;
        if ( state[y][x] == true ) continue;
        state[y][x] = true;
        dist = max(arr[y][x] - 1, dist);
        result += 1;
    }
}

void restore_domino() {
    state[y][x] = false;  // 0이 stand임 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> r;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
        }
    }

    while (r--) {
        // 공격 측
        cin >> y >> x >> dir;
        fall_domino(dir2idx(dir));

        // 수비측
        cin >> y >> x;
        restore_domino();
    }
    
    cout << result << endl;
    state_output();
    return 0;
}
