#include <iostream>
#include <queue>
#include <utility>

using namespace std;
int n, m;
int arr[101][101];
int dist[101][101];

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void bfs(int y, int x) {
    queue<pair<int, int> > q;
    q.push({y, x});
    arr[y][x] = 0;

    while(!q.empty()) {
        int now_y = q.front().first;
        int now_x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now_y + dy[i]; int nx = now_x + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > m) continue;
            if (arr[ny][nx] == 0) continue;
            arr[ny][nx] = 0;
            dist[ny][nx] = dist[now_y][now_x] + 1;
            q.push({ny, nx});
        }
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
            arr[i][j] = str[j-1] - 48;
        }
    }
    /*
    for (int i = 1; i<= n; i++) {
        for (int j = 1; j<= m; j++) {
            cout << arr[i][j];
        }
        cout << endl;
    }
    cout << endl;
    dist[1][1] = 1;
    for (int i = 1; i<= n; i++) {
        for (int j = 1; j<= m; j++) {
            cout << dist[i][j];
        }
        cout << endl;
    }
    cout << endl;
    bfs(1,1);
    for (int i = 1; i<= n; i++) {
        for (int j = 1; j<= m; j++) {
            cout << dist[i][j];
        }
        cout << endl;
    }
    cout << endl;
    */
    dist[1][1] = 1;
    bfs(1,1);
    cout << dist[n][m] << endl;
    return 0;
}
