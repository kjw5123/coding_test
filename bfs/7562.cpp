#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int t, n, sy, sx, fy, fx;
int arr[301][301];

void arr_init() {
    for (int i = 0; i < 301; i++) {
        for (int j = 0; j < 301; j++) {
            arr[i][j] = 0;
        }
    }
}

int dy[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
int dx[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

void bfs(int y, int x) {
    queue<pair<int, int> > q;
    q.push({y, x});
    while(!q.empty()) {
        int now_y = q.front().first;
        int now_x = q.front().second;
        q.pop();
        if (now_y == fy && now_x == fx) break;    
        for (int i = 0; i < 8; i++) {
            int ny = now_y + dy[i]; int nx = now_x + dx[i];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
            if (arr[ny][nx] != 0) continue;
            arr[ny][nx] = arr[now_y][now_x] + 1;
            q.push({ny, nx});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t;

    for ( int tc = 0; tc < t; tc++ ) {
        cin >> n >> sy >> sx >> fy >> fx;
        arr_init();
        bfs(sy, sx);
        cout << arr[fy][fx] << '\n';
    }
    
    
    return 0;
}
