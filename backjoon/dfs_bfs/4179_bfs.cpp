#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstdlib>

using namespace std;
/* [문제]
 *
 * 미로에서 탈출 해야함 
 * 지훈의 위치와 불이 붙은 위치 바탕으로
 * 1. 지훈이 불타기 전에 탈출 가능한지?
 * 2. 얼마나 빨리 탈출하는지
 * 알아내자
 *
 * 불은 dy dx로 번진다
 * 지훈이도 마찬가지로 dy dx 이동한다
 * 지훈이는 미로 가장자리에 접한 공간에서 탈출 가능하다
 * 벽은 못뚫음 불이든 지훈이든
 *
 * [입력]
 * n m 따로 주어짐 최대 1000x1000 사이즈
 * # 벽
 * . 빈공간
 * J 지훈이 초기 위치
 * F 불난 곳
 *
 * [출력]
 * 못나올시 IMPOSSIBLE 출력
 * 나올 시 빠른 탈출 시간 출력
 *
 * [사견]
 * 안 그래도 배열 2개 써가면서 확인하는 bfs dfs 해보고 싶었는데 마침
 * 좋은 유형의 문제인 것 같다 
 * */
struct obj {
    int y, x, id;  // id = 0이면 지훈, 1이면 불
};

int n, m;
int arr[1001][1001];
bool visited[1001][1001];
int jy, jx;
int turn = 0;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

vector<obj> fires;

void check_arr() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void bfs() {
    int turn = 0;
    queue<obj> q;

    while (!fires.empty()) {
        for (int i = 0; i < (int)fires.size(); i++) {
            q.push(fires[i]);
        }
        fires.clear();

        while(!q.empty()) {
            // cout << q.size() << endl;
            int cur_y = q.front().y;
            int cur_x = q.front().x;
            bool isFire = q.front().id;
            q.pop();

            if ((cur_y == n || cur_y == 1 || cur_x == m || cur_x == 1)&&!isFire) {
                cout << turn + 1 << endl;
                exit(0);
            }

            for (int i = 0; i < 4; i++) {
                int ny = cur_y + dy[i];
                int nx = cur_x + dx[i];
                if (ny <= 0 || ny > n || nx <= 0 || nx > m) continue;
                if (!isFire && visited[ny][nx]) continue;
                if (arr[ny][nx] != 0) continue;
                
                if (!isFire) {
                    visited[ny][nx] = true;
                    fires.push_back({ny, nx, isFire});

                } else {
                    arr[ny][nx] = -1;
                    fires.push_back({ny, nx, isFire});
                }
            }
        }
        turn++;
        // if (turn < 3) check_arr();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    string str;
    for (int i = 1; i <= n; i++) {
        cin >> str;
        for (int j = 1; j <= m; j++) {
            if (str[j-1] == '#') {
                arr[i][j] = 1;  // 벽
            } else if (str[j-1] == '.') {
                arr[i][j] = 0;  // 이동 가능 공간 

            } else if (str[j-1] == 'J') {
                jy = i; jx = j; // 지훈이 초기 위치

            } else if (str[j-1] == 'F') {
                fires.push_back({i, j, 1});  // 불들 초기 위치
                arr[i][j] = -1;
            }
        }
    }
    visited[jy][jx] = true;
    fires.push_back({jy, jx, 0});
    bfs();
    // cout << "IMPOSIBLE" << endl;  // 야!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    cout << "IMPOSSIBLE" << endl;

    return 0;
}
