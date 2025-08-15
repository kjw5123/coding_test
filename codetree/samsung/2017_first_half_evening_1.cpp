#include <iostream>

using namespace std;

/* [규칙]
 * 1. 왼쪽 방향 한번도 간적 없으면 좌회전 후 해당방향으로 1칸 이동
 * 2. 왼쪽이 인도거나 이미 방문한 도로인 경우 좌회전 후 다시 1번 트라이
 * 3. 4방향 다 해도 아동 못했으면 바라보는 바라보는 방향 유지 후 1칸 후진 후 다시 1번 트라이
 * 4. 3번도 못하게 되면 작동 포기
 * 
 * */

int n, m;
int arr[51][51]; // 0 도로, 1 벽, 2 방문
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int ry, rx;
int dir; // 상 우 하 좌 0 1 2 3

void print_result() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] == 2) cnt++;
        }
    }

    cout << cnt << endl;
}

void turn_left() {
    dir = (dir + 4 - 1) % 4;
}

int get_left_dir() {
    return (dir + 4 - 1) % 4;
}

void turn_reverse() {
    dir = (dir + 2) % 4;
}
int get_reverse_dir() {
    return (dir + 2) % 4;
}

bool try_move() {
    int left_dir = get_left_dir();

    int ny = ry + dy[left_dir]; int nx = rx + dx[left_dir];
    if (arr[ny][nx] == 0) {
        ry = ny; rx = nx;
        arr[ry][rx] = 2;
        turn_left();
        return true;

    } else {
        turn_left();
        return false;    
    }
}

bool go_back() {
    int reverse_dir = get_reverse_dir();
    int ny = ry + dy[reverse_dir]; int nx = rx + dx[reverse_dir];

    if (arr[ny][nx] == 1) return false;
    else {
        ry = ny; rx = nx;
        // 방향 자체를 바꾸는게 아니라 후진이라서 dir은 건들지 않는다
        return true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    cin >> ry >> rx >> dir;
    ry++; rx++;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
        }
    }

    arr[ry][rx] = 2; // 시작점 방문처리

    while(true) {
        bool isTurned = false;
        for (int i = 0; i < 4; i++) {
            isTurned = try_move();
            if (isTurned) break;
        }
        // 어짜피 4번 진행하면서 안되면 방향 원상복구 된다
        if (!isTurned) {
            bool isCan = go_back();
            if(!isCan) break;
        }
    }

    print_result();
    return 0;
}
