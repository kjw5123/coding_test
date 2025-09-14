#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>
#include <climits>

using namespace std;

// 09 07 1521
// 09 07 1710
// 문제
// N x M 격자가 있고
// 모든 위치엔 포탑이 있다
// 
// 각 포탑엔 공격력 존재, 공격력은 유동적이다
// 공격력이 0 이하가 되면 해당 포탑은 공격 불가 상태가 된다 
// 
// 한 턴당 4가지 액션을 순서대로 진행해서 K번 반복된다
// 단, 포탑이 1개만 남으면 바로 중지된다 
//
// 1. 공격자 선정
//    '안 부셔진 포탑' 중 가장 약한 포탑이 공격자다
//    공격자 선정되면, 가장 약한 포탑이므로 N + M 만큼 강해진다 (마천루 스카이스케이퍼)
//
//    약한 포탑 선정 기준
//    a. 공격력 가장 낮은거
//    b. 만약 그게 2개 이상이면  가장 최근에 공격한거
//    c. 만약 그게 2개 이상이면  행과 열 합이 가장 큰 포탑
//    d. 만약 그게 2개 이상이면  열 값이 가장 큰 포탑
//
// 2. 공격자 공격
//    가장 강한 포탑을 공격할 것이다
//    가장 강한 포탑은 위 약한 포탑 선정 과정의 정확히 반대다
//
//    a. 공격력 가장 강한거
//    b. 만약 2개 이상이면 공격한지 가장 오래된거 
//    c. 만약 그런 포탑이 2개 이상이라면  각 포탑 위치 행과 열 합이 가장 작은 포탑
//    d. 만약 그런 포탑이 2개 이상이면    열 값이 가장 작은 포탑
//
//    공격할 땐 레이저 공격을 시도 하고, 그게 안된다면 포탄 공격을 시도한다
//
//    A. 레이저 공격
//    1. 상하좌우 4개 방향 이동 가능
//    2. 부셔진 포탑 있는 위치는 지나기 불가능하다 
//    3. 가장 자리에서 막힌 방향으로 진행하고자 한다면 반대편으로 나올 수 있다
//    x 좌표 3 4 1 순 이런 식으로 
//
//       레이저 공격은 공격자 위치에서 대상 포탑까지 최단 경로로 공격을 시도한다
//       만약 이게 불가능하다면 포탄 공격을 진행하게 된다 
//       최단 경로가 2개 이상이라면, 우 하 좌 상 우선 순위대로 먼저 움직인 경로가 선택된다
//       
//       최단 경로가 정해진다면, 공격 대상에는 공격자의 공격력 만큼의 피해를 입히게 되며,
//       피해를 입은 포탑은 해당 수치만큼, 경로 상 포탑들은 공격력의 절반만큼 피해를 입게 된다
//
//    B. 포탄 공격
//    공격 대상에게 포탄을 던진다
//    공격 대상은 공격자 공격력만큼 피해를 입는다
//    주위 8개 방향 포탑도 피해 입는데, 공격자의 공격력 절반만큼 피해를 입게된다
//    공격자는 영향 받지 않는다
//    가장 자리에 포탄이 떨어졌다면, 레이저 이동처럼 추가 피해가 반대편 격자에 영향을 끼친다 크에엑
//
// 3. 공격을 받아 공격력이 0 이하가 된 포탑은 부셔진다
//
// 4. 포탑 정비
//    공격이 끝났다면, 부셔지지 않은 포탑중 공격과 무관했던 포탑은 공격력이 1씩 증가한다
//    즉, 공격도 안하고, 피해도 안받았어야한다

int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dx[8] = {1, 0, -1, 0, 1, -1, 1, -1};
int n, m, k;
int arr[11][11];  // 0 base로 해야 편하다 이건.. 아무리 생각해도
int attacked_turn[11][11];  // 공격했던 턴
bool not_doing[11][11];  // repair 용
int ay, ax;  // 공격자 좌표
int sy, sx;  // 맞는놈 좌표
int now_turn = 1;

void find_attacker() {
    int now_y = -1; int now_x = -1;
    int weaker_dmg = INT_MAX;
    int recent_turn = INT_MIN;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 0) continue;
            if (weaker_dmg > arr[i][j]) {  // 최대 데미지보다 작을 때
                weaker_dmg = arr[i][j];
                recent_turn = attacked_turn[i][j];
                now_y = i; now_x = j;

            } else if (weaker_dmg == arr[i][j]) {  // 데미지 같으면 턴 기준으로 생각
                if (recent_turn < attacked_turn[i][j]) {  // 지금께 우위면 갱신
                    recent_turn = attacked_turn[i][j];
                    now_y = i; now_x = j;

                } else if (recent_turn == attacked_turn[i][j]) {
                    if (now_y + now_x < i + j) {
                        now_y = i; now_x = j;
                    } else if (now_y + now_x == i + j) {
                        if (now_x < j) { now_y = i; now_x = j; }
                    }
                }
            }
        }
    }

    ay = now_y; ax = now_x;
    attacked_turn[ay][ax] = now_turn;
    not_doing[ay][ax] = false;
}

void find_defender() {
     int now_y = -1; int now_x = -1;
     int strong_dmg = INT_MIN;
     int old_turn = INT_MAX;

     for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
             if (arr[i][j] == 0) continue;
             if (i == ay && j == ax) continue;

             if (strong_dmg < arr[i][j]) {  // 최대 데미지보다 작을 때
                 strong_dmg = arr[i][j];
                 old_turn = attacked_turn[i][j];
                 now_y = i; now_x = j;

             } else if (strong_dmg == arr[i][j]) {  // 데미지 같으면 턴 기준으로 생각
                 if (old_turn > attacked_turn[i][j]) {  // 지금께 우위면 갱신
                     old_turn = attacked_turn[i][j];
                     now_y = i; now_x = j;

                 } else if (old_turn == attacked_turn[i][j]) {
                     if (now_y + now_x > i + j) {
                         now_y = i; now_x = j;
                     } else if (now_y + now_x == i + j) {
                         if (now_x > j) { now_y = i; now_x = j; }
                     }
                 }
             }
         }
     }

     sy = now_y; sx = now_x;
     not_doing[sy][sx] = false;
}

bool visited[11][11]; // 맞나 ? 아 나 이런거 안좋아하는데
int dist[11][11];
void do_attack() {
    bool isLaser = false;
    arr[ay][ax] += n + m;
    int dmg = arr[ay][ax];
    // 레이저용 최단 거리 나오는지? 되면 레이저 쏘고 return
    
    int py[11][11]; int px[11][11];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            py[i][j] = px[i][j] = -1;
        }
    }

    queue<pair<int,int>> q;
    q.push({ay, ax});
    visited[ay][ax] = true;
    dist[ay][ax] = 0;

    while(!q.empty()) {
        int cy = q.front().first; int cx = q.front().second;
        q.pop();

        if (cy == sy && cx == sx) {
            vector<pair<int,int> > path;
            int y = sy; int x = sx;
            while(!(y == ay && x == ax)) {
                path.push_back({y, x});
                int ty = py[y][x]; int tx = px[y][x];
                y = ty; x = tx;
            }
            reverse(path.begin(), path.end());

            for (int i = 0; i < (int)path.size() - 1; i++) {
                int ny = path[i].first;  int nx = path[i].second;
                arr[ny][nx] -= dmg / 2; if (arr[ny][nx] < 0) arr[ny][nx] = 0;
                not_doing[ny][nx] = false;
            }
            int ny = path.back().first; int nx = path.back().second;
            arr[ny][nx] -= dmg; if (arr[ny][nx] < 0) arr[ny][nx] = 0;
            not_doing[ny][nx] = false;
            isLaser = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int ny = (cy + dy[i] + n) % n;
            int nx = (cx + dx[i] + m) % m;
            if (arr[ny][nx] == 0) continue;
            if (visited[ny][nx]) continue;

            visited[ny][nx] = true;
            dist[ny][nx] = dist[cy][cx] + 1;
            py[ny][nx] = cy; px[ny][nx] = cx;
            q.push({ny, nx});
        }
    }
    if (isLaser) return;

    // 안되면 폭격 트라이하기
    arr[sy][sx] -= dmg; if (arr[sy][sx] < 0) arr[sy][sx] = 0;
    for (int i = 0; i < 8; i++)  {
        int ny = (sy + dy[i] + n) % n;
        int nx = (sx + dx[i] + m) % m;
        if (ny == ay && nx == ax) continue;

        arr[ny][nx] -= dmg / 2;
        if (arr[ny][nx] < 0) arr[ny][nx] = 0;
        not_doing[ny][nx] = false;
    }
    
}

void repair() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (not_doing[i][j] && arr[i][j] > 0) arr[i][j]++;
        }
    }
}

bool isLastManStanding() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] > 0) cnt++;
            if (cnt > 1) return false;
        }
    }
    return true;
}

void print_strong_tower() {
    int val = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            val = max(arr[i][j], val);
        }
    }
    cout << val << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }

    while(k--) {
        memset(not_doing, true, sizeof(not_doing));  // 일단 전부 아무것도 안한걸로 초기화
        memset(visited, false, sizeof(visited));
        memset(dist, 0x00, sizeof(dist));
        find_attacker();
        find_defender();
        do_attack();
        repair();  // done

        now_turn++;
        if (isLastManStanding()) break;
    }

    print_strong_tower();  // done
    return 0;
}
