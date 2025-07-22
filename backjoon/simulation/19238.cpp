#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>
#include <cstdlib>

using namespace std;

/* [조건]
 * 
 * 택시는 손님을 도착지로 데려다주면 연료 충전
 * 연료가 다 떨어지면 샷따 내린다
 *
 * M명의 승객을 태울거다
 * 격자는 NxN 크기이고, 비워져 있거나 벽이 있다
 * 상하좌우로 이동 가능하다
 * 특정 위치로 이동할 때 항상 최단경로로 이동한다
 * 
 * 승객은 빈칸 중 하나에 서있고, 다른 빈칸 중 하나로 이동하고자 한다 
 * 여러 승객이 타지 않는다 
 * 따라서, M번 운행 해야 한다 
 * 승객은 스스로 움직이지 않고,
 * 출발지에서 탑승, 목적지에서 하차만 가능하다 
 *
 * 태울 승객 고르는 기준: 현재 위치에서 최단거리에 위치한 승객 선택
 * 그런 승객이 다수면, 그 중 행 번호가 작은 승객을,
 * 그것도 다수면 열 번호가 작은 승객을 태운다
 * 
 * 택시와 승객이 같은 위치에 있으면 승객까지의 최단거리는 0이다
 *
 * 연료는 1칸 이동할 때마다 1씩 소모된다 
 *
 * 한 승객을 목적지에 데려다주면 이동하면서 쓴 연료의 2배가 충전된다 
 *
 * 이동중 연료가 다 떨어지면 이동 실패, 업무 종료다
 *
 * 단, 승객을 내림과 동시에 연로가 바닥 난 경우에는 실패로 간주치 아니한다
 * */
struct obj {
    int id;
    int e_y = 0;
    int e_x = 0;
};

struct dist {
    int y;
    int x;
    int d;
};

/*
bool cmp(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first == p2.first) return  p1.second < p2.second;
    return p1.first < p2.first;
}
*/

bool cmp(dist d1, dist d2) {
    if (d1.d == d2.d) {
        if (d1.y == d2.y) return d1.x < d2.x;
        return d1.y < d2.y;
    }

    return d1.d < d2.d;
}

int n, m;
int fuel;
obj arr[21][21];
bool visited[21][21];
pair<int, int> car;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int start_to_end(int sy, int sx, int ey, int ex) {
    memset(visited, 0x00, sizeof(visited));
    queue<dist> q;
    q.push({sy, sx, 0});
    visited[sy][sx] = true;

    while (!q.empty()) {
        int cur_y = q.front().y;
        int cur_x = q.front().x;
        int cur_dist = q.front().d;
        q.pop();
        if (cur_y == ey && cur_x == ex) return cur_dist;
        
        for (int i = 0; i < 4; i++) {
            int ny = cur_y + dy[i];
            int nx = cur_x + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
            if (visited[ny][nx]) continue;
            if (arr[ny][nx].id == 1) continue;
            visited[ny][nx] = true;
            q.push({ny, nx, cur_dist + 1});
        }
    }
    return -1;
}

void bfs(int y, int x) {
    queue<dist> q;
    q.push({y, x, 0});
    visited[y][x] = true;
    vector<dist> v;
    if (arr[y][x].id == 2) v.push_back({y, x, 0});

    while(!q.empty()) {
        int cur_y = q.front().y;
        int cur_x = q.front().x;
        int cur_dist = q.front().d;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = cur_y + dy[i]; int nx = cur_x + dx[i];

            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
            if (arr[ny][nx].id == 1) continue;
            if (visited[ny][nx]) continue;
            if (cur_dist + 1 > fuel) continue;  // 못 갈 거리면 그냥 다 포기해버리기
            q.push({ny, nx, cur_dist + 1});
            visited[ny][nx] = true;
            if (arr[ny][nx].id == 2) v.push_back({ny, nx, cur_dist+1});
        }
    }

    sort(v.begin(), v.end(), cmp);
    if (v.size() == 0) {
        cout << -1 << endl;
        exit(0);

    } else {
        fuel -= v[0].d;
        int sy = v[0].y; int sx = v[0].x;
        arr[sy][sx].id = 0;

        int ey = arr[sy][sx].e_y; int ex = arr[sy][sx].e_x;
        int diff = start_to_end(sy, sx, ey, ex);
        if (diff > fuel || diff == -1) {
            cout << -1 << endl;
            exit(0);
        }

        car.first = ey;
        car.second = ex;
        fuel += diff;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> fuel;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j].id;
        }
    }
    
    cin >> car.first >> car.second;

    int sy, sx, ey, ex;
    for (int i = 1; i <= m; i++) {
        cin >> sy >> sx >> ey >> ex;
        arr[sy][sx] = {2, ey, ex};
    }

    for (int i = 1; i <= m; i++) {
        memset(visited, 0x00, sizeof(visited));
        bfs(car.first, car.second);
    }

    cout << fuel << endl;
    return 0;
}
