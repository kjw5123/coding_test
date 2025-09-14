#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <cstring>
#include <climits>

using namespace std;

/* [문제]
 * NxN 격자판에 m개 몬스터와 하나의 전투로봇이 있다 
 * 한칸엔 몬스터가 최대 하나만 존재 가능 (곂치기 불가)
 *
 * 전투로봇, 몬스터 모두 정수 레벨 가진다 
 * 초기 전투로봇은 레벨이 2고, 전투로봇은 1초에 상하좌우 1칸 이동 가능 
 *
 * 전투로봇은 자신의 레벨보다 큰 몬스터가 있으면 지나갈 수 없다 (강약약강)
 * 나머지 모든칸은 이동 가능 (같아도 지나치긴 가능, 죽이긴 불가)
 *
 * [전투 로봇 이동 규칙]
 * 1. 없앨 수 있는 몬스터가 있다면 해당 몬스터를 없애러 간다
 * 
 * 2. 없앨 수 있는 게 하나 이상이면 dist 계산해서 없애러 간다 (맨허튼 말고 bfs가 정배겠죠잉?)
 *    2-1. 와중에 최솟값이 동일한게 두상이면 y축 작은 걸, 그것도 여러개면 x축 작은 몬스터를 제거한다 (귀찮은데 sort를 하던가 하자)
 *
 * 3. 없앨 수 있는 몬스터가 더는 없다면 이제 작동을 멈춘다
 *
 * 전투로봇이 한칸 이동 하는 데에는 1초가 소요된다 
 * 몬스터를 없앨 땐 시간 소요가 없다
 * 
 * 전투 로봇은 자신의 레벨과 같은 수의 몬스터를 없앨 때마다 레벨이 상승한다
 * 
 * */
struct info {
    int y, x, dist;
};
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int n; // 2 ~ 20
int arr[21][21];
bool visited[21][21]; // visited 대신 사용
int ry, rx; int r_lv = 2;
int now_killed = 0;
int turn = 0;

bool cmp(info i1, info i2) {
    if (i1.dist == i2.dist) {
        if (i1.y == i2.y) {
            return i1.x < i2.x;
        }
        return i1.y < i2.y;
    }
    return i1.dist < i2.dist;
}

int bfs() {
    memset(visited, 0x00, sizeof(visited));
    queue<info> q;
    q.push({ry, rx, 0});
    visited[ry][rx] = true; // 방문 처리는 해야하니 1 뻥튀기
    vector<info> v;
    
    while(!q.empty()) {
        int cy = q.front().y;
        int cx = q.front().x;
        int c_dist = q.front().dist;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i];
            if ( ny <= 0 || ny > n || nx <= 0 || nx > n ) continue;
            if ( arr[ny][nx] > r_lv ) continue; // 못감;
            if (visited[ny][nx]) continue;

            if (0 < arr[ny][nx] && arr[ny][nx] < r_lv) v.push_back({ny, nx, c_dist + 1});
            q.push({ny, nx, c_dist + 1});
            visited[ny][nx] = true;

        }
    }

    if (v.size() == 0) return 0;
    sort(v.begin(), v.end(), cmp);
    ry = v[0].y; rx = v[0].x;
    arr[v[0].y][v[0].x] = 0;
    now_killed++;
    return v[0].dist; // 임시
}

void check_lv_up() {
    if (now_killed == r_lv) {
        r_lv++;
        now_killed = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 9) { ry=i; rx=j; arr[i][j] = 0; }
        }
    }

    while(true) {
        int turns = bfs();
        if (turns == 0) break;
        turn += turns;
        check_lv_up();
    }

    cout << turn << endl;
    return 0;
}
