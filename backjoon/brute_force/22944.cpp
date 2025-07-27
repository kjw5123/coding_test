#include <iostream>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>

using namespace std;

/* [문제]
 * 가로 세로 N 2차원 배열
 * 2곳을 제외한 곳엔 체력 1 감소시키는 광역기가 켜짐
 *
 * 현재 위치, 안전지대 이 2곳이 비가 안내리고
 * 현재위치도 곧 비가 내림
 *
 * 각 격자에 비 막아주는 우산이 K개가 있고, 우산엔 내구도 D가 있다
 * 1턴 지날 때 마다 내구도 줄어들고, 내구도 0 되면 우산 없음 
 * 모든 우산의 내구도는 D로 통일 돼 있다 
 *
 *
 * [규칙]
 * dy dx 이동 가능
 * 이동한 곳이 안전지대면 이동 종료 
 * 이ㅗㅇ한 곳에 우산 있으면 우산 들기 
 * 이동할 대부터 우산이 있으면 가지고 있는 우산 버리고 새 우산으로 교환
 * 버린 우산은 다시 못주움
 * 죽음의 비를 맞았을 때, 우산 가지고 있으면 내구도 감소, 아니라면 체력 감소
 * 우산 내구도 0 되면 우산 사라짐
 * 체력 0 되면 사망 
 * 체력이 남아있다면 위를 반복
 * 안전지대로 빨리 이동하자
 * 
 * U는 우산
 * S는 지금 위치
 * 안전지대 E
 * 빈칸 .
 * 
 * 
 * 
 * 
 * */
int n, h, d, k;
int sy, sx, ey, ex;
bool arr[501][501][11];  // 우산 상태 관리  // 아니 3차원 할 필요 없었네 얘는
bool visited[501][501][11];

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

struct man {
    int y;
    int x;
    int mh;  // man health 사람 채력 
    int uh;  // umblella health 우산 체력
    int used_um;  // 지금까지 살면서 주워온 우산의 개수를 기억하는 변수
    int t;  // turn
};

void bfs() {
    queue<man> q;
    if (arr[sy][sx][0]) {
        q.push({sy, sx, h, d, 1, 0});
        visited[sy][sx][1] = true;
    } else {
        q.push({sy, sx, h, 0, 0, 0});
        visited[sy][sx][0] = true;
    }

    while (!q.empty()) {
        int cy = q.front().y; int cx = q.front().x;
        int cmh = q.front().mh; int cuh = q.front().uh;
        int cuu = q.front().used_um; int ct = q.front().t;
        q.pop();

        if (cy == ey && cx == ex) { cout << ct << '\n'; exit(0); }

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;

            int nmh = cmh; int nuh = cuh; int nuu = cuu; int nt = ct + 1;

            if (ny == ey && nx == ex) { cout << nt << '\n'; exit(0); }

            if (arr[ny][nx][nuu]) { nuu++; nuh = d; }

            if (nuh > 0) nuh--;
            else nmh--;

            if (nmh <= 0) continue;
            if (nuu > k) continue;
            if (visited[ny][nx][nuu]) continue;

            visited[ny][nx][nuu] = true;
            q.push({ny, nx, nmh, nuh, nuu, nt});
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> h >> d;
    char val;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> val;

            if (val == '.') continue;
            else if (val == 'S') { sy = i; sx = j; }
            else if (val == 'E') { ey = i; ex = j; }
            else if (val == 'U') {
                for (int k = 0; k <= 10; k++) {
                    arr[i][j][k] = true;  // 우산 있다 여기 !!
                }
                k++;
            }
        }
    }
    
    bfs();
    cout << -1 << endl;    
    return 0;
}
