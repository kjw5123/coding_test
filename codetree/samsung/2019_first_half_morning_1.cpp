#include <iostream>
#include <cstring>

using namespace std;

// NxM 격자 칸에 먼지가 있다
// 시공의 돌풍은 항상 1번 열에 있고, 두칸 차지함
//
// 1턴 당 이런 일이 생김
//
// 1. 먼지가 4방 향 확산됨 
//   인접 방향에 시공 돌풍 있거나 방 범위 벗어나면 해당 방향으로는 확산 안함
//   원래 양의 5를 나눈 값이고, 소수점 버림
//   확산될 때마다 원래 칸의 먼지 양은 확산된 먼지만큼 줄어든다
//   확산된 먼지는 방에 있는 모든 먼지 확산 끝낸 다음 해당 칸에 더해지게 된다
//
// 2. 시공 돌풍이 청소 진행
//   위는 반시계, 아래는 시계
//   바람 불면 먼지1칸 이동
//   시공 돌풍은 먼지 없음
//   시공 돌풍으로 들어간 먼지는 삭제됨

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int n, m, times;
int arr[51][51];
int temp[51][51];
int ty;

void dust_boom() {
    memset(temp, 0x00, sizeof(temp));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] > 0) {
                int booms = arr[i][j] / 5;
                for (int k = 0; k < 4; k++) {
                    int ny = i + dy[k]; int nx = j + dx[k];
                    if ( ny <= 0 || ny > n || nx <= 0 || nx > m ) continue;
                    if (arr[ny][nx] == -1) continue;
                    
                    arr[i][j] -= booms; temp[ny][nx] += booms;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] != -1) arr[i][j] += temp[i][j];
        }
    }
}

void push_dust() {
    for (int i = ty - 2; i >= 1; i--) arr[i+1][1] = arr[i][1];
    for (int j = 2; j <= m; j++) arr[1][j-1] = arr[1][j];
    for (int i = 2; i <= ty; i++) arr[i-1][m] = arr[i][m];
    for (int j = m; j >= 2; j--) arr[ty][j] = arr[ty][j-1];
    arr[ty][2] = 0;


    for (int i = ty + 3; i <= n; i++) arr[i-1][1] = arr[i][1];
    for (int j = 2; j <= m; j++) arr[n][j-1] = arr[n][j];
    for (int i = n; i >= ty+2; i--) arr[i][m] = arr[i-1][m];
    for (int j = m; j >= 2; j--) arr[ty+1][j] = arr[ty+1][j-1];
    arr[ty+1][2] = 0;
}

void calc_total_dust() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] > 0) cnt += arr[i][j];
        }
    }
    cout << cnt << endl;
}

void check_arr() {
    cout << "Now Turn is " << times + 1 << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() { 
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> times;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j]; if (arr[i][j] == -1) { ty = i-1; }
        }
    }    
    
    while(times--) {
        dust_boom();
        // check_arr();
        push_dust();
        // check_arr();
    }

    calc_total_dust();
    return 0;
}
