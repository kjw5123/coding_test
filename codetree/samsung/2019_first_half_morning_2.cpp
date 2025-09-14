#include <iostream>
#include <utility>
#include <cstring>

using namespace std;

// N x M 이다
// 곰팡이한텐 크기, 속도가 있다
//
// 규칙
//
// 1. 첫번째 열부터 탐색
// 탐색할 때 제일 먼저 발견된 곰팡이 채취
// 곰팡이 채취 하면, 해당 칸은 빈칸이 된다
//
// 2. 채취 끝나면 곰팡이들은 이동 시작
//
// 3. 입력으로 주어진 방향과 속력으로 이동, 격자 판의 벽에 도달 시 방향 전환
//    방향 전환엔 시간 안쓴다
//
// 4. 모든 곰팡이 이동 마친 후, 한칸에 곰팡이가 2마리 이상일 때는 크기가 큰 곰팡이가 잡아먹음
//
// 5. 1초가 걸리며, 오른쪽 열로 이동하며 위 과정 반복
struct mold {
    int y, x;
    int speed;
    int dir;
    int msize;
};

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};
int n, m;
int arr[101][101];
int temp[101][101];
int now_c = 1;
int mold_num, my, mx, ms, md, msize;
int result = 0;

mold molds[10001];
bool isDie[10001];

void check_arr(int isTemp) {
    for (int i =1 ; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!isTemp) cout << arr[i][j] << " ";
            else cout << temp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int change_dir(int d) {
    if (d == 1) return 2;
    else if (d == 2) return 1;
    else if (d == 3) return 4;
    else return 3;
}

void arr_init() {
    for (int i = 1; i <= mold_num; i++) {
        if (!isDie[i]) arr[molds[i].y][molds[i].x] = i;
    }
}

void check_c() {
    for (int i = 1; i <= n; i++) {
        if (arr[i][now_c] != 0) { 
            isDie[arr[i][now_c]] = true;
            result += molds[arr[i][now_c]].msize;
            break;
        }
    }
}

void move_molds() {
    for (int i = 1; i <= mold_num; i++) {
        if (isDie[i]) continue;

        int ny = molds[i].y + dy[molds[i].dir-1] * molds[i].speed;
        int nx = molds[i].x + dx[molds[i].dir-1] * molds[i].speed;
        
        while ( !(1 <= ny && ny <= n) ) {
            if (ny <= 0) {
                ny = 2 - 1 * ny;
                molds[i].dir = change_dir(molds[i].dir);
            } else if (ny > n) {
                ny = 2 * n - ny;
                molds[i].dir = change_dir(molds[i].dir);
            }
        }

        while ( !(1 <= nx && nx <= m) ) {
            if (nx <= 0) {
                nx = 2 - 1 * nx;
                molds[i].dir = change_dir(molds[i].dir);

            } else if (nx > m) {
                nx = 2 * m - nx;
                molds[i].dir = change_dir(molds[i].dir);
            }
        }
        
        molds[i].y = ny; molds[i].x = nx;
        if (temp[ny][nx] == 0) temp[ny][nx] = i;
        else {
            int val = temp[ny][nx];
            if (molds[val].msize > molds[i].msize){ isDie[i] = true; }
            else if (molds[val].msize < molds[i].msize){ isDie[val] = true; temp[ny][nx] = i; }
        }
    }
    // cout << "temp" << endl;
    // check_arr(1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> mold_num;
    for (int i = 0; i < mold_num; i++) {
        cin >> my >> mx >> ms >> md >> msize;
        molds[i+1] = {my, mx, ms, md, msize};
    }
    
    while (now_c != m + 1) {
        memset(arr, 0x00, sizeof(arr));
        memset(temp, 0x00, sizeof(temp));
        arr_init();
        // cout << "Now column is " << now_c <<  " and arr" << endl;
        // check_arr(0);
        check_c();
        move_molds();
        now_c++;
    }
    cout << result << endl;
    return 0;
}
