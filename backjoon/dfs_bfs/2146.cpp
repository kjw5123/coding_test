#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

/* [문제]
 *
 * 여러 섬으로 이루어진 나라가 있음
 * 섬을 이어야 함 
 * 가장 짧게 선 이을 수 있는 것 하나만 찾자 
 *
 * [사견]
 * 땅 별로 번호 다르게 해주는 게 좋은 것 같은데
 * 
 * */

int n;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int arr[101][101];
int world[101][101];
bool visited[101][101];
int world_num = 0;
int minVal = INT_MAX;

void print_world() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << world[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void make_world_bfs(int y, int x, int cnt) {
    queue<pair<int,int> > q;
    q.push({y, x});
    world[y][x] = cnt;
    visited[y][x] = true;

    while(!q.empty()){
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
            if (arr[ny][nx] == 0) continue;
            if (visited[ny][nx] == true) continue;

            visited[ny][nx] = true;
            world[ny][nx] =cnt;
            q.push({ny, nx});
        }
    }
}

void make_world() {
    int cnt = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if(!visited[i][j] && arr[i][j] != 0) make_world_bfs(i , j, cnt++);
        }
    }
    world_num = cnt - 1;
}

struct bridge {
    int y, x, turn;
};

void bfs(int y, int x) {
    queue<bridge> q;
    int cw = world[y][x];  // current_world, 지금 bfs 굴리는 나라
    q.push({y, x, 0});
    visited[y][x] = true;

    while(!q.empty()) {
        int cy = q.front().y;
        int cx = q.front().x;
        int ct = q.front().turn;
        q.pop();

        if (world[cy][cx] != 0 && world[cy][cx] != cw) {minVal = min(minVal, ct-1); return;}

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i]; int nt = ct + 1;
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
            if (world[ny][nx] == cw) continue;
            if (visited[ny][nx]) continue;
            visited[ny][nx] = true;
            q.push({ny, nx, nt});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }
    
    make_world();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            memset(visited, 0x00, sizeof(visited));
            if (world[i][j] != 0) bfs(i, j);
        }
    }
    // print_world();
    // cout << world_num << endl;
    cout << minVal << endl;
    return 0;
}
