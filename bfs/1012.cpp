#include <iostream>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

int t, m, n, k;
int arr[51][51];

void arr_init() {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            arr[i][j] = 0;
        }
    }
}

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void bfs(int y, int x) {
    arr[y][x] = 0;
    queue<pair<int,int> > q;
    q.push({y, x});

    while (!q.empty()) {
        int now_y = q.front().first;
        int now_x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now_y + dy[i]; 
            int nx = now_x + dx[i];
            if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
            if (arr[ny][nx] == 0) continue;
            arr[ny][nx] = 0;  // push 하는 시점에서 방문 처리를 하는게 이치 상 맞지..
            q.push({ny, nx});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t;
    for (int tc = 0; tc < t; tc++) {
        cin >> m >> n >> k;
        arr_init();

        for (int i = 0; i < k; i++) {
            int y, x;
            cin >> x >> y;
            arr[y][x] = 1;
        }
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (arr[i][j] == 1) {
                    bfs(i,j); cnt++;
                }
            }
        }
        cout << cnt << endl;
    }
    
    
    return 0;
}
