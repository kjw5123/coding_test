#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdlib>
using namespace std;

/* [규칙]
 * NxN 격자 체스판에서, K개의 말 사용
 * 말은 원판 모양이며, 말 위에 다른 말을 올릴 수 있다
 * 각 칸은 흰색 / 빨간색 / 파랑색 中 1로 색칠되어 있다
 *
 * 게임은 말 K개를 위에 놓고 시작
 * 1 ~ K 번까지 번호가 있으며, 이동방향도 미리 정해져 있다
 * 위 아래 왼쪽 오른쪽 4방향 이동 가능하다
 *
 * 턴 한번은 1 ~ K 말을 순서대로 이동 시킨다 
 * 한 말이 이동할 때, 위에 있는 말도 같이 이동한다 (이동의 주체는 아래 말의 방향)
 * 말의 이동방향에 있는 칸에 따라 말의 이동이 달라진다
 *
 * 턴이 진행되던 중에 말이 4개 이상 쌓이면 게임 종료 
 *
 * 내가 이동할 칸이
 * 흰칸 - 그냥 이동하고, 이미 다른 말이 있으면 이동하는 말을 위에 올린다
 * 이동하는 말에 이미 다른 말이 있으면 선입선출로 처리한다 (queue)
 *
 * 빨간 칸
 * 이동 후에 A 위에 있는거 뒤집어 버린다 (원래 있던 건 유지)
 *
 * 파란 칸 
 * A 번 말의 이동 방향을 반대로 하고! 이동한다
 * 방향을 반대로 한 후 이동하려는 칸이 파란색이면 이동 X, 방향만 반대로 바꾼다
 *
 * 체스판 바깥은 파란색과 동일하다
 * */
// 굳이 queue를 고집할 필욘 없을 것 같다
// 걍 2차원 벡터 만들까 싶다
// 생각보다 n도 안크고 k도 안크네
// 이게 왜 골드 2일까?
struct piece {
    int y;
    int x;
    int dir;
};
int n, k;
int arr[13][13];  // 그냥 판 정보만 기입할거다 (흰,빨,파)
int turn = 1;
vector<int> v[13][13];  // 말 인덱스 정보는 여기서 관리하자
piece mal[11]; // v를 전체 탐색하는 건 바보 같은 짓이니 여기서 좌표 관리 하자
int dy[5] = {0,0,0,-1,1};
int dx[5] = {0,1,-1,0,0};  // 우 좌 상 하

int change_dir(int dir) {
    switch(dir){
        case 1:
            return 2;
        case 2:
            return 1;
        case 3:
            return 4;
        case 4:
            return 3;
    }
    return -1;
}

void move(int idx) {
    // cout << turn << endl;
    if (v[mal[idx].y][mal[idx].x].front() != idx) return;

    int ny = mal[idx].y + dy[mal[idx].dir]; 
    int nx = mal[idx].x + dx[mal[idx].dir];

    if (ny <= 0 || ny > n || nx <= 0 || nx > n || arr[ny][nx] == 2) {
        mal[idx].dir = change_dir(mal[idx].dir);
        ny = mal[idx].y + dy[mal[idx].dir]; 
        nx = mal[idx].x + dx[mal[idx].dir];

        if (!(ny <= 0 || ny > n || nx <= 0 || nx > n || arr[ny][nx] == 2)) {
            int cur_y = mal[idx].y; int cur_x = mal[idx].x;
            if (arr[ny][nx] == 1) {
                reverse(v[cur_y][cur_x].begin(), v[cur_y][cur_x].end());
    
                for (int i = 0; i < (int)v[cur_y][cur_x].size(); i++) {
                    int it = v[cur_y][cur_x][i];
                    mal[it].y = ny;
                    mal[it].x = nx;
                    v[ny][nx].push_back(it);
                }

                if (v[ny][nx].size() >= 4) {
                    cout << turn << endl;
                    exit(0);
                }
                v[cur_y][cur_x].clear();

            } else {
                for (int i = 0; i < (int)v[cur_y][cur_x].size(); i++) {
                    int it = v[cur_y][cur_x][i];
                    mal[it].y = ny;
                    mal[it].x = nx;
                    v[ny][nx].push_back(it);
                }

                if (v[ny][nx].size() >= 4) {
                    cout << turn << endl;
                    exit(0);
                }
                v[cur_y][cur_x].clear();
            }
        }

    } else if (arr[ny][nx] == 1) {
        int cur_y = mal[idx].y; int cur_x = mal[idx].x;
        reverse(v[cur_y][cur_x].begin(), v[cur_y][cur_x].end());

        for (int i = 0; i < (int)v[cur_y][cur_x].size(); i++) {
                int it = v[cur_y][cur_x][i];
                mal[it].y = ny;
                mal[it].x = nx;
                v[ny][nx].push_back(it);
        }

        if (v[ny][nx].size() >= 4) {
            cout << turn << endl;
            exit(0);
        }
        v[cur_y][cur_x].clear();

    } else if (arr[ny][nx] == 0) {
        int cur_y = mal[idx].y; int cur_x = mal[idx].x;
        // cout << cur_y << " " << cur_x << " | " << ny << " " << nx << endl;
        for (int i = 0; i < (int)v[cur_y][cur_x].size(); i++) {
                int it = v[cur_y][cur_x][i];
                mal[it].y = ny;
                mal[it].x = nx;
                v[ny][nx].push_back(it);
        }

        if (v[ny][nx].size() >= 4) {
            cout << turn << endl;
            exit(0);
        }
        v[cur_y][cur_x].clear();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }

    for (int i = 1; i <= k; i++) {
        int y, x, d; cin >> y >> x >> d;
        mal[i] = {y, x, d};
        v[y][x].push_back(i);
    }
    
    while(turn <= 1000) {
        for(int i = 1; i <= k; i++) {
           move(i); 
        }

        turn++;
    }
    cout << -1 << endl;
    return 0;
}
