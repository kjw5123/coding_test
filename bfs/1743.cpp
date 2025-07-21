#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

int arr[101][101];

int n, m, k;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int bfs(int y, int x) {
    queue<pair<int , int> > q;
    q.push({y, x});
    arr[y][x] = 0;
    int cnt = 1;

    while(!q.empty()) {
        int now_y = q.front().first;
        int now_x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now_y + dy[i];
            int nx = now_x + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > m) continue;
            if (arr[ny][nx] == 0) continue;
            arr[ny][nx] = 0; cnt++;
            q.push({ny, nx});
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int y, x;
        cin >> y >> x;
        arr[y][x] = 1;
    }
    int bigger = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] == 1) {
                bigger = max(bfs(i, j), bigger);
            }
        }
    }
    cout << bigger << endl;
    return 0;
}
