#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <climits>
#include <tuple>

using namespace std;

// 2025 09 06 1517
// 1649 Done ㅆㅃㅆㅃㅆㅃㅆㅆ  ㅆㅆㅆㅆ ㅆ ㅆ ㅆ ㅆ  ㅆㅆ  ㅆㅆ ㅆ ㅆ ㅆ ㅆ ㅆ  ㅆ ㅆ ㅆㅆ 
// 문제 
// 0 ~ 5로 이루어진 NxN arr 있다
// 0은 빈공간
// 1은 사무실
// 2 3 4 5는 에어컨 (좌상우하)
// 
// 에어컨이 사무실을 시원하게 하는 4과정
// 1. 자기 앞에 대해, 삼각형 모양으로 흩뿌리고, 가까우면 5, 멀면 1
//    바람 방향에 벽 있으면 전파 X
//    r ㄴ 모양으로 진행함에 있어 벽이 있으면 전파 불가
//    새로운 시원함 생성은, 모든 에어컨으로부터 나오는 시원함의 합으로 이루어지게 된다
//    에어컨 있는 자리에도 시원함 생성 가능
//
// 2. 시원한 공기들이 섞인다
//    인접 칸에 대해 시원함이 높은 곳에서 낮은 곳으로
//    시원함 차이 / 4 만큼 전파한다
//    모든 칸에 대해 동시에 발생한다
//    단, 사이에 벽이 있으면 전파 발생 X
//
// 3. 외벽 있는 칸에 대해서만 시원함 1이 쫙 감소하고, 이미 0이면 감소하지 않음
// 
// 위 과정을 진행하게 되면 1분이 지난다
// 이 사이클을 모든 사무실의 시원함이 전부 k 이상이 될 때 까지 반복한다
// 100 분 넘기면 -1 출력하도록.

struct aircon {
    int y, x, dir;
};

int dy[4] = {0, -1, 0, 1};
int dx[4] = {-1, 0, 1, 0};
int n;
int arr[21][21];
int cools[21][21];
int temp[21][21];
bool visited[21][21];
int wall_cnt;
int want_cool;

vector<aircon> aircons;
vector<pair<int,int>> works;
set<tuple<int,int,int>> walls;  // 걍 구조체 재탕 해도 된다 0: 위, 1: 왼

bool isWorkSpaceCool() {
    for (int i = 0; i < (int)works.size(); i++) {
        int y = works[i].first; int x = works[i].second;
        if (cools[y][x] < want_cool) return false;
    }
    return true;
}


void side_down() {
    for (int j = 1; j <= n; j++) {
        if (cools[1][j] > 0) cools[1][j]--;
        if (cools[n][j] > 0) cools[n][j]--;
    }
    for (int i = 2; i <= n-1; i++) {
        if (cools[i][1] > 0) cools[i][1]--;
        if (cools[i][n] > 0) cools[i][n]--;
    }
}

bool isWall(int y, int x, int dir) {
    if (dir == 0) {
        if (walls.count({y, x, 1})) return true;

    } else if (dir == 1) {
        if (walls.count({y, x, 0})) return true;

    } else if (dir == 2) {
        if (walls.count({y, x+1, 1})) return true;

    } else {
        if (walls.count({y+1, x, 0})) return true;
    }
    return false;
}

void cool_spread() {
    memset(temp, 0x00, sizeof(temp));
    for (int i = 1; i <= n; i++) {
        for (int j = 1 ; j <= n; j++) {
            if (cools[i][j] == 0) continue;
            temp[i][j] += cools[i][j];
            for (int k = 0; k < 4; k++) {
                int ny = i + dy[k]; int nx = j + dx[k];
                if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
                if (isWall(i, j, k)) continue;
                int diff = cools[i][j] - cools[ny][nx];
                if (diff > 0) {
                    temp[i][j] -= diff / 4;
                    temp[ny][nx] += diff / 4;
                }
            }
        }
    }
    memcpy(cools, temp, sizeof(cools));
} 

void true_work(int y, int x, int dir, int power) {
    if (power == 0) return;  // 0부턴 고려 안해줘도 된다
    if (y <= 0 || y > n || x <= 0 || x > n) return; // 몰라 배열 넘김도 여기서 처리
    if (visited[y][x]) return;
    visited[y][x] = true;
    cools[y][x] += power;

    int d = dir;
    if (d == 0) {
        if (!isWall(y, x, d))                       true_work(y,   x-1, d, power-1);
        if (!isWall(y, x, 1) && !isWall(y-1, x, 0)) true_work(y-1, x-1, d, power-1);
        if (!isWall(y, x, 3) && !isWall(y+1, x, 0)) true_work(y+1, x-1, d, power-1);

    } else if (dir == 1) {
        if (!isWall(y, x, d))                       true_work(y-1, x, d, power-1);
        if (!isWall(y, x, 0) && !isWall(y, x-1, 1)) true_work(y-1, x-1, d, power-1);
        if (!isWall(y, x, 2) && !isWall(y, x+1, 1)) true_work(y-1, x+1, d, power-1);

    } else if (dir == 2) {
        if (!isWall(y, x, d))                       true_work(y,   x+1, d, power-1);
        if (!isWall(y, x, 1) && !isWall(y-1, x, 2)) true_work(y-1, x+1, d, power-1);
        if (!isWall(y, x, 3) && !isWall(y+1, x, 2)) true_work(y+1, x+1, d, power-1);

    } else if (dir == 3) {
        if (!isWall(y, x, d))                       true_work(y+1, x, d, power-1);
        if (!isWall(y, x, 0) && !isWall(y, x-1, 3)) true_work(y+1, x-1, d, power-1);
        if (!isWall(y, x, 2) && !isWall(y, x+1, 3)) true_work(y+1, x+1, d, power-1);

    }
}
void aircon_work() {
    for (int i = 0; i < (int)aircons.size(); i++) {
        memset(visited, 0x00, sizeof(visited));
        int y = aircons[i].y; int x = aircons[i].x; int dir = aircons[i].dir;        
        y += dy[dir]; x += dx[dir];
        true_work(y, x, dir, 5);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> wall_cnt >> want_cool;
    
    for (int i = 1 ; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 0) continue;  // 빈공간
            if (arr[i][j] == 1) works.push_back({i, j});
            else aircons.push_back({i, j, arr[i][j]-2});  // 0 좌 1 상 2 우 3 하
        }
    }
    for (int i = 0; i < wall_cnt; i++) {
        int y, x, dir;
        cin >> y >> x >> dir;
        walls.insert({y, x, dir});
    }

    int turn = 0;    
    while(turn++ <= 100) {
        aircon_work();
        cool_spread();
        side_down();
        if (isWorkSpaceCool()) {cout << turn << endl; return 0;}
    }

    cout << -1 << endl;
    return 0;
}
