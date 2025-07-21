#include <iostream>
#include <utility>
#include <climits>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
int n;
int arr[21][21];
bool visited[21][21];
int total_val = 0;
int minVal = INT_MAX;
int cnt[6] = {0};
bool flag = true;
// 독재자 구재현 씨를 견제해야하는 문제다.
// 독재는 용서못함.
// 2차원 배열을 5개의 선거구로 나눠야 한다
// 각 구역은 전부 어떤 선거구 중 하나라도 포함되어야 한다
// 한 선거구의 모든 지역은 다 연결되어야 한다
// 경계선은 4종류로 구분된다
// 1번: / (중심에서 출발)
// 2번: \ (중심에서 출발)
// 3번: \ ()
// 4번: 
//
// 고려할 수 있는건 시작 점 y, x
// 끝점 d1, d2다
//
// 선이 아니라 점으로 생각을 해보자 
// 1번 점: x ~ x + d1,
//         y - d1 ~ y
//
// 2번 점: x ~ x + d2,
//         y + d2
//
// 3번 점: x + d1 ~ x + d1 + d2,
//         y - d1 ~ y - d1 + d2
//
// 4번 점: x + d2 ~ x + d1 + d2,
//         y + d2 ~ y + d2 - d1
//
// 이러하다
//
// 뭐... 당연하지만 1,2,3,4 점이 서로 곂치면 안된다
//
// 다른거 다 제치고 위 조건만 생각해보자 일단
// 전체 탐색해서 모든 점이 다 x, y가 되게끔 하자
// x + d1 + d2가 N 초과면 말안됨
// y + d2가 N 초과면 말안됨
// y - d1이 1 미만이면 말안됨
//
// 격자가 작아서 사실 러프하게 잡아도 문제 될 건 없으리라.
// 
// 아 걍 4중 반복문 돌려????????????????????????
// 끽해야 20^4 = 160,000 번 호출이고, 와중에 조건 안되면 그냥 다 무시 시킬거다
// 매우 가능한 방법이라 본다

void print_visited() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << visited[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void print_cnt() {
    for (int i = 1; i <= 5; i++) cout << cnt[i] << " ";
    cout << endl << endl;
}

int dy[4]  = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int bfs(int y, int x, int yy, int xx, int d1, int d2, int idx) {
    queue<pair<int, int> > q;
    q.push({y, x});
    visited[y][x] = true;
    int cnt = 0;

    while(!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        cnt += arr[cur_y][cur_x];
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = cur_y + dy[i]; int nx = cur_x + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
            if (idx == 0 && (ny >= yy + d1 || nx >  xx)) continue;
            if (idx == 1 && (ny >  yy + d2 || nx <= xx)) continue;
            if (idx == 2 && (ny < yy + d1 || nx >=  xx - d1 + d2)) continue;
            if (idx == 3 && (ny <=  yy + d2 || nx < xx - d1 + d2)) continue;
            if (!visited[ny][nx]) {
                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }
    }
    return cnt;
}
void findVal(int y, int x, int d1, int d2) {
    // 아예 말도 안되는 조건은 여기서 바로 무시한다
    if (y + d1 + d2 > n) return;
    if (x + d2 > n) return;
    if (x - d1 < 1) return;

    /*
    pair<int,int> fir =  {y,        x};      // 좌
    pair<int,int> se =   {y-d1,      x+d1};  // 상
    pair<int,int> thir = {y+d2-d1, x+d2+d1}; // 우 
    pair<int,int> four = {y+d2,    x+d2};    // 하
    */

    //좌-상, 좌-하 곂치는지만 검사하면 ok일듯 하다 (아마도)

    // if ((fir.first == se.first && fir.second == se.second) || (fir.first == thir.first && fir.second == thir.second)) return;

    // 이제 어쨌든 간에 사각형 박스가 생성된다
    // 이제 경계면을 visited 처리 하고 
    // 각 점의 max 값을 바탕으로 사각 범위에 대한 합을 구한 다음에 
    // total_val에 빼서 5번 영역 구한 다음에 
    // 최대 최소를 구하자
    memset(visited, 0x00, sizeof(visited));

    for (int i = 0; i <= d1; i++) visited[y + i][x - i] = true;

    for (int i = 0; i <= d2; i++) visited[y + i][x + i] = true;

    for (int i = 0; i <= d2; i++) visited[y + d1 + i][x - d1 + i] = true;

    for (int i = 0; i <= d1; i++) visited[y + d2 + i][x + d2 - i] = true; 

    for (int i = 1; i <= n; i++) {
        vector<int> bound;
        for (int j = 1; j <= n; j++) {
            if (visited[i][j]) bound.push_back(j);
        }
        if (bound.size() >= 2) {
            for (int j = bound.front(); j <= bound.back(); j++) {
                visited[i][j] = true;
            }
        }
    }

    memset(cnt, 0x00, sizeof(cnt));
    /*
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (visited[r][c]) {
                cnt[5] += arr[r][c];
                continue;
            }
            if (r <  y + d1 && c <= x)                 cnt[1] += arr[r][c];
            else if (r <= y + d2 && c > x)             cnt[2] += arr[r][c];
            else if (r >= y + d1 && c <  x - d1 + d2)  {
                cnt[3] += arr[r][c];
                if (y == 1 && x == 2 && d1 == 1 && d2 == 7) {
                cout << r << " " << c << "   ";
                
                }
            }
            // else if (r >  y + d2 && c >= x - d1 + d2)  cnt[4] += arr[r][c];
            else cnt[4] += arr[r][c];
        }
    }
    int max_cnt = max({cnt[1], cnt[2], cnt[3], cnt[4], cnt[5]});
    int min_cnt = min({cnt[1], cnt[2], cnt[3], cnt[4], cnt[5]});

    minVal = min(minVal, max_cnt - min_cnt);
    if (minVal == 82 && flag == true) {print_visited(); print_cnt(); flag = false; cout << y << " " << x << " "<< d1 << " " << d2 << endl;}
    */
    cnt[1] = bfs(1, 1, y, x, d1, d2, 0);
    cnt[2] = bfs(1, n, y, x, d1, d2, 1);
    cnt[3] = bfs(n, 1, y, x, d1, d2, 2);
    cnt[4] = bfs(n, n, y, x, d1, d2, 3);
     cnt[5] = total_val - cnt[1] - cnt[2] - cnt[3] - cnt[4];
     int max_cnt = max({cnt[1], cnt[2], cnt[3], cnt[4], cnt[5]});
     int min_cnt = min({cnt[1], cnt[2], cnt[3], cnt[4], cnt[5]});


     minVal = min(minVal, max_cnt - min_cnt);
     // if (y == 1 && x == 2 && d1 == 1 && d2 == 7) {print_visited(); print_cnt(); flag = false; cout << y << " " << x << " "<< d1 << " " << d2 << endl;}
     
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
            total_val += arr[i][j];  // 5번 선거구 값은 이걸로 처리하자
        }
    }

    // 함수 하나 만들어서 가능한 모든 좌표 탐색을 시킬거다
    // 조건에 주어진대로 매번 범위 탐색 시키면 될 것 같은데 
    // 이걸 모든 점을 대상으로 진행 시키면 되지 않나 싶다
    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= n; x++) {
            for (int d1 = 1; d1 <= n; d1++) {
                for (int d2 = 1; d2 <= n; d2++) {
                    findVal(y, x, d1, d2);
                }
            }
        }
    }

    cout << minVal << endl;
    return 0;
}
