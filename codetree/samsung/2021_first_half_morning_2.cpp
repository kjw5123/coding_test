#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

/* [문제]
 * -1, 0, m으로 이루어진 nxn 격자가 있다
 *  -1엔 검은 돌, 0은 빨간 폭탄, 1~m은 빨간색이 아닌 서로 다른 색 폭탄이 있다
 * 폭탄 묶음이 더이상 없을 때 까지 특정 행동을 반복할 것이다
 *
 * 1. 현재 격자에서 크기가 가장 큰 폭탄 묶음 찾기
 *    폭탄 묶음은 2개 이상 폭탄으로 이루어진 것
 *    모두 같은 색으로 이루어지거나, 빨간색 폭탄 포함해서 정확히 2개의 색으로만 이루어진 폭탄을 의미한다
 *    단, 빨간색 폭탄으로만 이루어진 건 올바른 폭탄 묶음이 아니다.
 *    모든 폭탄들이 전부 격자 상 연결 되어야 한다
 *    상하좌우 인접을 의미한다
 *
 *    크기가 가장 큰 폭탄 묶음이 여러개라면 우선 수누이를 따른다
 *    1. 빨간색이 가장 적은걸 고른다
 *    2. 폭탄 묶음의 기준점 중 가장 행이 큰 폭탄 묶음을 선택한다 (기준점이란, 폭탄 묶음을 이루는 폭탄 중 빨간색이 아니며 행이 젤 큰 칸, 열이 가장 작은 칸)
 * 
 * 2. 선택한 폭탄 묶음을 제거하고, 폭탄을 떨어져야 하는데, 돌은 안떨어진다
 * 3. 반시계방향으로 격자 회전
 * 4. 다시 중력 작용하고, 돌은 안떨어지고 고정됨
 *
 * 더 이상 폭탄 없을 때 까지 반복한다
 * 한 라운드 마다 폭탄 묶음 터지면서, 이때의 묶음 크기를 C라 하면, C * C 만큼 점수 획득한다
 * */
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int arr[21][21];
int temp[21][21];
bool visited[21][21];

int n, m;
long long int score;

void arr_ccw() {
    memset(temp,0x00,sizeof(temp));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            temp[n-j+1][i] = arr[i][j];
        }
    }
    memcpy(arr,temp,sizeof(arr));
}

bool check_arr() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (arr[i][j] == -1 || arr[i][j] == INT_MIN) continue;
            return false;  // 뭔가 있음
        }
    }
    return true;  // 다 비었다
}

// 폭탄 처리 로직을 고민해봐야 하는 시점이다 
// 빨간색은 visited 처리 안할거다 (arr 사이즈 작아서 문제 없을듯 근데 빨간색만이면? 흠)

vector<pair<int,int>> to_boom;
int b_r_cnt;
int b_size;
int b_b_row;
int b_s_col;

void bfs(int y, int x) {
    int nc = arr[y][x];  // now color
    queue<pair<int,int>> q;
    q.push({y, x});
    visited[y][x] = true;
    int r_cnt = 0;  // 1순위 비교 조건 때문에 추가
    vector<pair<int,int>> r_idx;
    int total_size = 1; // 이번 bfs로 얻을 묶음 사이즈
    int big_row = y;
    int small_col = x;
    
    vector<pair<int,int>> idxs;
    idxs.push_back({y, x});

    while(!q.empty()) {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue; // 벽
            if (arr[ny][nx] == -1) continue; // 돌
            if (visited[ny][nx]) continue; // 방문 무시
            
            if (arr[ny][nx] == 0) {  // 빨간색
                r_idx.push_back({ny, nx});  // 할 일 끝나면 visited 취소 해줘야한다
                visited[ny][nx] = true;
                r_cnt++;
                total_size++;
                idxs.push_back({ny, nx});

                q.push({ny, nx});

            } else if (arr[ny][nx] == nc) {  // 동일 색상
                total_size++;
                visited[ny][nx] = true;
                idxs.push_back({ny, nx});

                q.push({ny, nx});
                if (ny > big_row) {big_row = ny; small_col = nx; }
                else if (ny == big_row) { if (nx < small_col) small_col = nx; }

            }
        }
    }

    for (int i = 0; i < (int)r_idx.size(); i++) visited[r_idx[i].first][r_idx[i].second] = false;  // 빨폭만 초기화

    // 할거 다했을 때 조건 검사
    if (total_size > b_size) {b_r_cnt = r_cnt; b_size = total_size; b_b_row = big_row; b_s_col = small_col; to_boom = idxs; } 
    else if (total_size == b_size) {
        if (b_r_cnt > r_cnt) {
            b_r_cnt = r_cnt; b_size = total_size; b_b_row = big_row; b_s_col = small_col; to_boom = idxs;

        } else if (b_r_cnt == r_cnt) {
            if ( big_row > b_b_row ) {
                b_r_cnt = r_cnt; b_size = total_size; b_b_row = big_row; b_s_col = small_col; to_boom = idxs;

            } else if ( big_row == b_b_row && small_col < b_s_col ) {
                b_r_cnt = r_cnt; b_size = total_size; b_b_row = big_row; b_s_col = small_col; to_boom = idxs;
            }
        }
    }
}

void boom_booms() {
    if (b_size < 2) return;

    score += b_size * b_size;
    for (int i = 0; i < (int)to_boom.size(); i++) {
        arr[to_boom[i].first][to_boom[i].second] = INT_MIN;
    }
}

void gravity() {
    for (int j = 1; j <= n; j++) {
        int floor_idx = n;

        for (int i = n; i >= 1; i--) {
            if (i == floor_idx && arr[i][j] != INT_MIN) { floor_idx--; }
            else if (arr[i][j] != INT_MIN && arr[i][j] != -1) {arr[floor_idx][j] = arr[i][j]; arr[i][j] = INT_MIN; floor_idx--; }
            if (arr[i][j] == -1) floor_idx = i - 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }


    while(true) {
        memset(visited, 0x00, sizeof(visited));
        b_size = INT_MIN; b_r_cnt = INT_MAX;
        b_b_row = INT_MIN; b_s_col = INT_MAX; to_boom.clear();

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (visited[i][j]) continue;  // 방문한 곳은 무시
                if (arr[i][j] == -1 || arr[i][j] == 0 || arr[i][j] == INT_MIN) continue;  // 돌 무시, 빨강 무시
                bfs(i, j);
            }
        }

        if (b_size < 2) break;
        boom_booms();
        gravity();
        arr_ccw();
        gravity();
        
    }
    
    cout << score << endl;
    return 0;
}
