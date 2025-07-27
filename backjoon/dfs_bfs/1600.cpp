#include <iostream>
#include <queue>
#include <utility>
#include <cstring>
#include <climits>
#include <vector>

using namespace std;

/* [문제]
 * 
 * 동물원 막 탈출한 원숭이가 세상 구경 좀 한다
 * 말이 되고 싶다
 * 말은 체스 말 처럼 움직인다 
 * 장애물 넘기 가능하다
 *
 * K번 최대 이동 가능하고
 * 그 외엔 인접 칸으로 이동하는 것만 가능하다 
 * 
 *  
 * [입력]
 * 말로써 이동가능한 횟수 k
 * 가로 길이 w 세로길이 h
 * 격자 제공
 * K = 0 ~ 30
 * W, H = 1 ~ 200
 * 원숭이는 1,1 -> n, m에 가야한다
 * [사견]
 * 아니 이거는 그냥 bfs 2번이 정배 아닌가?
 * 자, 먼저 K만 하는 bfs 먼저 해두고 (이건 전부 최소거리이다)
 * !!근데!! turn 별로 분리해서 처리 안하면 
 * 다른 영역이 침범 받거나 그럴 수도 있으니 해당 부분은 유의해서 처리해야하지 않나 싶다
 *
 * 굳이 array에 안넣어도, 그냥 어떤 q에 push 해두면 되지 않나?
 * 암튼간에, 이 상태로 그냥 일반 dy dx만 쭉 돌리고 난 후에 
 * 결과 값 보면 될 것 같은데 ?
 * */

struct mk {
    int y, x, cnt;
};

int k, n, m;
int arr[201][201];
int visited[201][201][31];
int ky[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int kx[8] = {1, 2, 2, 1, -1, -2, -2, -1}; // knight니까
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void check_dist() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            //
        }
        cout << endl;
    }
    cout << endl << endl;
}

int bfs() {
    queue<mk> q;
    q.push({1,1,0});
    visited[1][1][0] = 1;

    while(!q.empty()) {
        int cy = q.front().y;
        int cx = q.front().x;
        int cc = q.front().cnt;
        q.pop();
        if (cy == n && cx == m) return visited[cy][cx][cc] - 1;

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i]; 
            if (ny <= 0 || ny > n || nx <= 0 || nx > m) continue;
            if (arr[ny][nx] == 1) continue;
            if (visited[ny][nx][cc]) continue;

            visited[ny][nx][cc] = visited[cy][cx][cc] + 1;
            q.push({ny, nx, cc});
        }

        if (cc < k) {
            for (int i = 0; i < 8; i++) {
                int ny = cy + ky[i]; int nx = cx + kx[i];
                if ( ny <= 0 || ny > n || nx <= 0 || nx > m ) continue;
                if (arr[ny][nx] == 1) continue;
                if (visited[ny][nx][cc + 1]) continue;

                visited[ny][nx][cc+1] = visited[cy][cx][cc] + 1;
                q.push({ny, nx, cc + 1});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> k >> m >> n; // 喝!!
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
        }
    }
    
    cout << bfs() << endl;
    return 0;
}
