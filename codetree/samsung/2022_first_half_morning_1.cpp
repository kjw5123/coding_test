#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <cstring>

using namespace std;

/* [문제]
 * 
 * 술래잡기를 해볼까 한다
 * n x n 격자에서 진행되며, 술래는 정중앙에 위치 ( 5 x 5 면 3x3이니 n / 2 + 1이겠다 )
 *
 * m명의 도망자 존재 
 * 도망자는 아무데나 위치 함 
 * 도망자는 '좌우로만 or 상하로만 도망치는 유형이 있다'
 * 좌우맨은 오른쪽보고 스타트, 상하맨은 아래 보고 스타트
 *
 * NxN 맵엔 나무도 존재한다
 * 나무에 초기에 도망자 곂쳐있을 수도 있다
 *
 * 도망자 이동  (동시에)
 * 술래 이동
 * 반복
 *
 * 도망자는 술래와 거리가 3 이하일 때만 이동 시도 (거리는 맨해튼 방식으로 측정, abs 사용 필수)
 *
 * [도망자들 움직일 때 규칙]
 * 1. 지금 바라 보는 방향으로 이동해고 격자를 벗어나지 않을때
 *    움직이려는 칸에 술래 있으면 이동 X
 *    없으면 해당칸 이동 (나무 있어도 이동 가능)
 *
 * 2. 움직일 때 격자를 벗어난다면
 *    1. 우선 방향을 틀어준다 반대로
 *    2. 방향 반대로 했을 때 술래 없으면 1칸 이동 한다
 *
 * [술래 이동 규칙]
 * 위부터 바라보며, 달팽이 모양 이동 시작 (상우하좌상우하좌)
 * 끝에 도달 시, 다시 (하우상좌 하우상좌) 이동
 *
 * 술래는 1번 턴 동안 정확히 1칸 이동한다 
 * 이동 후 위치가 이제 회전해야한다면, 방향 바로 틀어준다
 * 이동을 통해 1,1 or 정중앙에 도달한다면, 이 때도 마찬가지로 방향 바로 틀어줘야한다
 *
 * 이동 직후 술래는 턴 넘기기전에 시야에 있는 도망자를 잡게 된다 
 * 술래 시야는 '지금 바라보는 방향으로 자기자신 포함 3칸이다'
 *
 * 단, 나무가 있으면 해당 칸 도망자는 안보인다 (딱 그 칸만, 뒤를 가려주지 않음)
 * 도망자 잡히면 삭제되고, 지금 턴 * 잡은 도망자 수 만큼 점수 획득
 *
 * */

int n, m, h, k; // 격자 크기, 도망자 수, 나무 수, 턴 수
int arr_up[100][100]; // 1base로 할거다
int arr_down[100][100];
bool visited[100][100];  // 초기화 때 잠깐 쓸 배열

// 나무는 그냥 set<pair<int,int>> 마려운데
// 도망자는 set 쓰면 곂쳐서 큰일난다
struct runner {
    int y, x, dir;
};
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};


int sy, sx, s_dir; // 술래 좌표
bool isUp = true;
vector<runner> runners;
set<pair<int,int>> trees;
int score = 0;

void arr_init() {
    // 짜치지만, 내려갈때랑 올라갈때 배열 2개 따로 직접 쓸거다
    for (int i = 1; i <= n / 2 + 1; i++) {
        for (int j = 1; j <= n; j++) {
            if (j <= i) arr_up[i][j] = 0;
            else if ( j > n - i) arr_up[i][j] = 2;
            else arr_up[i][j] = 1;
        }
    }

    arr_up[1][1] = 2;
    arr_up[sy][sx] = 0;

    for (int i = n / 2 + 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > i) arr_up[i][j] = 2;
            else if (j <= n - i + 1) arr_up[i][j] = 0;
            else arr_up[i][j] = 3;
        }
    }

     for (int i = 1; i <= n / 2; i++) {
         for (int j = 1; j <= n; j++) {
             if (j <= i + 1) arr_down[i][j] = 2;
             else if (j > n - i + 1) arr_down[i][j] = 0;
             else arr_down[i][j] = 3;
         }
     }

     for (int j = 1; j <= n; j++) { // i = n / 2 + 1;
         int i = n / 2 + 1 ;
         if (j < i) arr_down[i][j] = 2;
         else arr_down[i][j] = 0; // 중심도 알아서 통일된다
     }

     for (int i = n / 2 + 2; i <= n; i++) {
         for (int j = 1; j <= n; j++) {
             if (j >= i) arr_down[i][j] = 0;
             else if (j <= n - i) arr_down[i][j] = 2;
             else arr_down[i][j] = 1;
         }
     }
}

int get_dist(int ry, int rx) {
    return abs(ry - sy) + abs(rx - sx);
}
int change_runner_dir(int dir) {
    return (dir + 2) % 4;  // 우 1 하 2 좌 3 상 0
}

bool isOutBound(int ny, int nx) {
    if (ny <= 0 || ny > n || nx <= 0 || nx > n) return true;
    else return false;
}

void print_runners() {
    cout << "So, Now Runners: " << endl;
    for (int i = 0; i <(int)runners.size(); i++) {
        cout << "(" << runners[i].y << ", " << runners[i].x << ") and dir is " << runners[i].dir << endl;
    }
    cout << endl;
}

// dir = 1이면 우측, dir = 2면 하측
void runner_move() {
    // cout << "Before Move: " << endl;
    // print_runners();

    // 1. 만약 술래와의 거리가 3 이하인지
    for (int i = 0; i < (int)runners.size(); i++) {
        int ry = runners[i].y; int rx = runners[i].x; int dir = runners[i].dir;
        if (get_dist(ry, rx) > 3) continue; // 거리 3 초과인 건 무시하기

        int ny = ry + dy[dir]; int nx = rx + dx[dir];
        if (!isOutBound(ny, nx)) {  // 이동해도 격자 안나가면
            if (ny == sy && nx == sx) continue;  // 담칸에 술래 있으면 그냥 안움직이기
            
            runners[i].y = ny; runners[i].x = nx;  // 그게 아니라면 상태 갱신

        } else {
            dir = (dir + 2) % 4; runners[i].dir = dir;
            int ny = ry + dy[dir]; int nx = rx + dx[dir];
            if (ny == sy && nx == sx) continue;

            runners[i].y = ny; runners[i].x = nx;
        }
    }
    // cout << "After Move: " << endl;
    // print_runners();
}

// 얘는 그냥 이동해야하는 판을 깔아버리자 
// 1,1이나 정중앙에 도착시엔 지금 값 따라서 toggle 시키고

int check_runners() {
    vector<pair<int,int>> v;
    int ny = sy; int nx = sx;
    if (!trees.count({ny, nx})) v.push_back({ny,nx}); 
    ny += dy[s_dir]; nx += dx[s_dir];
    if (!(ny <= 0 || ny > n || nx <= 0 || nx > n) && !trees.count({ny, nx})) v.push_back({ny, nx});
    ny += dy[s_dir]; nx += dx[s_dir];
    if (!(ny <= 0 || ny > n || nx <= 0 || nx > n) && !trees.count({ny, nx})) v.push_back({ny, nx});

    int erase_cnt = 0;
    for (vector<runner>::iterator it = runners.begin(); it != runners.end();) {
        bool isErase = false;
        for (int i = 0; i < (int)v.size(); i++) {
            if (v[i].first == it->y && v[i].second == it->x) {
                it = runners.erase(it);
                isErase = true;
                erase_cnt++;
                break;
            }
        }
        if (!isErase) it++;
    }

    return erase_cnt;
}

void mover_move(int turn) {
    // cout << sy << " " << sx << endl;
    sy += dy[s_dir]; sx += dx[s_dir];
    if (isUp) s_dir = arr_up[sy][sx];
    else s_dir = arr_down[sy][sx];

    if (sy == 1 && sx == 1 && isUp) {isUp = false; s_dir = arr_down[sy][sx]; }
    else if (sy == n / 2 + 1 && sx == n / 2 + 1 && !isUp) { isUp = true; s_dir = arr_up[sy][sx]; }
    // cout << "So Now 술래 위치 is " << sy << " " << sx << endl << endl;

    int val = check_runners();
    // cout << " val is " << val << endl;
    score += val * turn;

    // cout << "After 술래 움직인 후: " << endl;
    // print_runners();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> h >> k;
    sy = sx = n / 2 + 1; 
    arr_init();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << arr_up[i][j] << " ";
        }
        cout << endl;
    }    
    cout << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << arr_down[i][j] << " ";
        }
        cout << endl;
    }    
    cout << endl;
    int y, x, dir;
    for (int i = 0; i < m; i++) {
        cin >> y >> x >> dir;
        runners.push_back({y,x,dir});
    }

    for (int j = 0; j < h; j++) {
        cin >> y >> x;
        trees.insert({y,x});
    }

    for (int i = 1; i <= k; i++) {
        runner_move();
        mover_move(i);
        if (runners.empty()) break;
    }

    cout << score << endl;
    return 0;
}
