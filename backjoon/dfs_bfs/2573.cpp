#include <iostream>
#include <climits>
#include <queue>
#include <utility>
#include <cstring>
#include <vector>

using namespace std;

/* [문제]
 * 지구 온난화 때문에 북극 빙하 녹는중
 * 2차원 배열이 있다 치자 
 * 
 * 각 빙산 부분별 높이 정보는 양의 정수로 저장된다
 * 빙산 외의 바다는 0으로 저장 된다 
 * 
 * 5 * 7
 * 0 0 0 0 0 0 0
 * 0 2 4 5 3 0 0 
 * 0 3 0 2 5 2 0
 * 0 7 6 2 4 0 0
 * 0 0 0 0 0 0 0
 * 
 * 빙산 높이는 바닷물에 많이 접할 수록 빨리 녹는다 
 * 1년마다 동서남북 4방위에있는 바다 칸 만큼 줄어든다
 * 0보다 줄어들진 않는다 
 *
 * 덩어리 개수란, 동서남북으로 단절된 각 별개 덩어리를 칭한다
 *
 * 2 덩어리 이상으로 분리되는 최초의 시간을 구하자
 *
 *
 * */
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int n, m;
int arr[301][301];
int temp[301][301];
int visited[301][301];
int t = 0;

void print_arr() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void bfs(int y, int x) {
    queue<pair<int,int> > q;
    q.push({y, x});
    visited[y][x] = true;

    while(!q.empty()) {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        visited[cy][cx] = true;

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > m) continue;  // 칸 밖 멸시
            if (arr[ny][nx] == 0) {
                if (temp[cy][cx] > 0) temp[cy][cx]--;
                continue;
            }
            if (visited[ny][nx]) continue;
            visited[ny][nx] = true;
            q.push({ny, nx});
        }
    }
}

bool check_arr() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] != 0) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
        }
    }
    
    while(true) {
        memset(visited, 0x00, sizeof(visited));
        memcpy(temp, arr, sizeof(temp));
        int dunguri = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (arr[i][j] != 0 && !visited[i][j]) { bfs(i,j); dunguri++;}
            }
        }
        // print_arr();
        if (dunguri >= 2) { cout << t << endl; return 0; }
        t++;
        memcpy(arr, temp, sizeof(arr));
        if(!check_arr()) break;
    }
    cout << 0 << endl;
    return 0;
}
