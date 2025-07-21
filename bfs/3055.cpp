#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>


using namespace std;

/*
 * 빈 곳: '.' = 0
 * 물가 : '*' >= 1
 * 돌   : 'X' = -1
 * 비버 : 'D' = -1
 * 고슴 : 'S' = 0
 *
 * 고슴, 물 특) 0보다 큰 데서만 이동 시도 가능함
 *
 * */

int w_arr[51][51];
int g_arr[51][51];
int n, m, Sy, Sx, Dy, Dx;


int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

queue<pair<int, int> > wq; // water 
queue<pair<int, int> > gq; // hedge

void water_bfs() {
    while (!wq.empty()) {
        int y = wq.front().first;
        int x = wq.front().second;
        wq.pop();

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 1 || ny > n || nx < 1 || nx > m) continue;
            if (w_arr[ny][nx] != 0) continue; 
            w_arr[ny][nx] = w_arr[y][x] + 1;
            wq.push({ny, nx});
        }
    }
}

void gosum_bfs() {
    g_arr[Sy][Sx] = 1;

    while (!gq.empty()) {
        int y = gq.front().first;
        int x = gq.front().second;
        gq.pop();

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 1 || ny > n || nx < 1 || nx > m) continue;

            if (ny == Dy && nx == Dx) {
                cout << g_arr[y][x] << endl;
                exit(0);
            }

            if (w_arr[ny][nx] == -1 || g_arr[ny][nx] > 0) continue;

            if (w_arr[ny][nx] != 0 && g_arr[y][x] + 1 >= w_arr[ny][nx]) continue;

            g_arr[ny][nx] = g_arr[y][x] + 1;
            gq.push({ny, nx});
        }
    }

    cout << "KAKTUS" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    string str;
    for (int i = 1; i <= n; i++) {
        cin >> str;
        for (int j = 1; j <= m; j++) {
            w_arr[i][j] = str[j-1];
            if(w_arr[i][j] == 'D') {
                Dy = i; Dx = j; w_arr[Dy][Dx] = -2;

            } else if (w_arr[i][j] == 'S') {
                Sy = i; Sx = j;
                gq.push({i, j});

            } else if (w_arr[i][j] == 'X') {
                w_arr[i][j] = g_arr[i][j] = -1;

            } else if (w_arr[i][j] == '*') {
                wq.push({i, j});
                w_arr[i][j] = 1;
            } else {
                w_arr[i][j] = 0;
            }
        }
    }
    
    water_bfs();
    gosum_bfs();

    return 0;
}
