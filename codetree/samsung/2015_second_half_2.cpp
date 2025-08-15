#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

int n, m;
int arr[11][11];
int by, bx;
int ry, rx;
int oy, ox;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int result = INT_MAX;
// 2의 20 제곱은 끽해야 100만이다
//
// 왼쪽에서 오른쪽으로 기울일 때는 오른쪽에 있는거부터 먼저 이동시킨다
// 오른쪽에서 왼쪽으로 기울일 대는 왼쪽에 있는거부터 먼저 이동시킨다
// 아래에서 위쪽으로 옮길 때는
//
// 일단 무턱대고 다 호출하면 재귀 깊이 너무 깊어져서 터진다
// 매 깊이마다 가능한 방향을 생각해서, 최대 깊이 10회 이내로 탐색할 수 있게끔 하자
// 그리고 위에 남겼다 시피, 파랑 빨강 구슬 위치 기반으로, 누구부터 기울일것인지 고려하자
//
// 이정도면 되는듯?

bool isWall(int y, int x, int dir, bool isRed) {
    if (arr[y + dy[dir]][x + dx[dir]] == 1) return true;
    else if (isRed && y + dy[dir] == by && x + dx[dir] == bx) return true;
    else if (!isRed && y + dy[dir] == ry && x + dx[dir] == rx) return true;
    return false;
}

void check_arr() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == ry && j == rx) { cout << 'R'; }
            else if (i == by && j == bx) { cout << 'B'; }
            else if (i == oy && j == ox) cout << 'O';
            else if (arr[i][j] == 0) cout << '.';
            else if (arr[i][j] == 1) cout << '#';
        }
        cout << endl;
    }
    cout << endl;
}
bool isRedFirst(int dir) {
    if (dir == 0) {  // 아래서 위로, 즉 위에 있는게 먼저 이동해야함
        if (ry < by) return true;
        else return false;

    }
    else if (dir == 1) { // 왼쪽에서 오른쪽으로
        if (rx > bx) return true;
        else return false;

    }
    else if (dir == 2) {
        if (ry > by) return true;
        else return false;

    }
    else {
        if (rx < bx) return true;
        else return false;
    }
}

int move_balls(int dir, bool isRed) {
    bool redDone = false;
    bool blueDone = false;
    if (isRed) {
        while (!isWall(ry, rx, dir, true)) {
            ry += dy[dir]; rx += dx[dir];
            if (ry == oy && rx == ox) {
                redDone = true;
                ry = 0; rx = 0; break;
            }
        }
        while (!isWall(by, bx, dir, false)) {
            by += dy[dir]; bx += dx[dir];
            if (by == oy && bx == ox) {
                blueDone = true;
                by = 0; bx = 0; break;
            }
        }

    }
    else {
        while (!isWall(by, bx, dir, false)) {
            by += dy[dir]; bx += dx[dir];
            if (by == oy && bx == ox) {
                blueDone = true;
                by = 0; bx = 0; break;
            }
        }
        while (!isWall(ry, rx, dir, true)) {
            ry += dy[dir]; rx += dx[dir];
            if (ry == oy && rx == ox) {
                redDone = true;
                ry = 0; rx = 0; break;
            }
        }
    }

    if (redDone == true && blueDone == false) return 0;  // 최소 후보군
    else if (redDone == false && blueDone == false) return 1; // dfs 더 해보기
    else return 2; // blue가 나온시점에서 무의미함
}

void dfs(int depth) {
    if (depth == 10) {
        return;
    }

    check_arr();
    vector<int> dirs;
    for (int i = 0; i < 4; i++) {
        dirs.push_back(i);  // 가능성 따지지말고 그냥 다 넣는게 맞음 (퍼랭이가 움직일 수 있으니 해당 경우도 봐줘야함)
    }


    for (int i = 0; i < (int)dirs.size(); i++) {
        int bf_ry = ry; int bf_rx = rx;
        int bf_by = by; int bf_bx = bx;

        int val = move_balls(dirs[i], isRedFirst(dirs[i]));
        if (val == 0) {
            result = min(result, depth + 1);
        }
        else if (val == 1) {
            dfs(depth + 1);
        }

        ry = bf_ry; rx = bf_rx;
        by = bf_by; bx = bf_bx;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    char val;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> val;
            if (val == '#') arr[i][j] = 1;
            else if (val == 'R') { ry = i; rx = j; }
            else if (val == 'B') { by = i; bx = j; }
            else if (val == 'O') { oy = i; ox = j; }
            else arr[i][j] = 0;
        }
    }

    dfs(0);
    if (result == INT_MAX) cout << -1 << endl;
    else cout << result << endl;
    return 0;
}

