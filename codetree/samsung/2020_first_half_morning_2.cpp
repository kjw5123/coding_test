#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

// 2025 09 07 1142
// 문제
// $x$ 격자 있다
// 체스판에서 술래잡기 체스 할거다
// 술래 말 하나만 사용해서 도둑 말을 잡고
// 도둑말을 잡을 때마다 도둑말의 방향을 가지게 된다
// 말의 방향이란 해당 말이 이동할 수 있는 방향을 의미한다
//
// 8가지 방향이 있다
// 말판 위치 x는 위에서부터 아래, 왼쪽에서 오른쪽으로 0 base다
// y가 j, x가 i
//
// 각 도둑말은 1 ~ 16 번호가 서로 안겹치게 매겨져 있다
//
// 1. 초기에는 (0,0) 위치의 도둑말 잡고 시작한다
//
// 2. 도둑말은 번호가 작은 순서대로 본인이 가진 이동 방향대로 이동
//    한번의 이동에 한 칸을 이동하며, 빈 칸이나 다른 도둑말이 있는 칸은 이동할 수 있는 칸이다
//    술래말이 있는 칸이나 격자 밖은 못간다
//    도둑말은 이동할 수 있을 때 까지 45도 CCW 회전하며 갈 수 있는 칸을 탐색한다
//    이동할 ㅅ ㅜ있는 칸이 없다면 이동하지 않는다
//    그 이외의 경우에는 칸을 이동
//    해당 칸에 다른 도둑말이 있다면 서로 위치를 swap 한다
//
// 3. 도둑말 이동이 끝나면 술래말이 이동을 시작한다
//    술래말은 이동 가능한 방향의 어느 칸이나 이동 가능하다
//    한번에 여러 칸 이동도 가능하다
//    술래말이 잡고자 하는 도둑말로 이동할 때는 지나는 칸들의 말들을 잡지 않는다
//    술래말은 도둑말이 없는 곳으로는 이동할 수 없다
//
// 술래말이 다른 도둑을 잡은 뒤에 다시 도둑말이 번호 순서대로 이동한다
//
// 술래말이 더이상 잡을 도둑말이 없으면 게임을 끝낸다
//
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

struct obj {
    int num;
    int dir;
};

obj arr[4][4];  // 간만에 0 base로 풀자
int sy, sx, s_dir;  // seeker? 암튼 술래 좌표
int result;

void hider_move() {
    for (int k = 1; k <= 16; k++) {
        bool next_num_flag = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (arr[i][j].num == k) {
                    int dir = arr[i][j].dir;

                    for (int p = 0; p < 8; p++) {
                        int n_dir = (dir + p) % 8;
                        int ny = i + dy[n_dir]; int nx = j + dx[n_dir];
                        if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4) continue;  // 격자 밖 가면 않되
                        if (ny == sy && nx == sx) continue; // 술래 자리로 가면 않되
                        // 빈칸이거나 다른 말이거나 알빠 없고
                        swap(arr[i][j].num, arr[ny][nx].num);
                        arr[i][j].dir = n_dir;
                        swap(arr[i][j].dir, arr[ny][nx].dir);
                        next_num_flag = true;  // 이거 안하면 완전 탐색 마저하면서, 어 또 같은 번호네? ㅇㅋ 이동 시킴 이난리 난다
                        break;
                    }
                }
                if (next_num_flag) break;
            }
            if (next_num_flag) break;
        }
    }
}

void check_canGo(vector<pair<int, int>>& canGo) {
    int y = sy; int x = sx;
    while (!(y < 0 || y >= 4 || x < 0 || x >= 4)) {
        if (arr[y][x].num != 0) canGo.push_back({ y, x });
        y += dy[s_dir]; x += dx[s_dir];
    }
}

void dfs(int score) {
    vector<pair<int, int>> canGo;
    check_canGo(canGo);

    if (canGo.empty()) { result = max(result, score); return; }

    int now_sy = sy; int now_sx = sx;
    int now_s_dir = s_dir;
    obj temp[4][4];  // 현재 단계 저장용
    memcpy(temp, arr, sizeof(temp));  // 이전 상태 저장 시켜줘야한다..

    for (int i = 0; i < (int)canGo.size(); i++) {
        int y = canGo[i].first; int x = canGo[i].second; int dir = arr[y][x].dir; int num = arr[y][x].num;
        sy = y; sx = x; s_dir = dir; arr[y][x].num = 0;
        hider_move();
        dfs(score + num);
        sy = now_sy; sx = now_sx; s_dir = now_s_dir;
        memcpy(arr, temp, sizeof(arr));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int num, dir;
            cin >> num >> dir;
            dir--;
            arr[i][j] = { num ,dir };
        }
    }

    result = arr[0][0].num;
    arr[0][0].num = 0; // 시작부터 죽이고 시작
    s_dir = arr[0][0].dir;  // 죽인 말 방향 뺏기
    hider_move();

    dfs(result);  // 0 박았다가 봉변 당함
    cout << result << endl;
    return 0;
}
