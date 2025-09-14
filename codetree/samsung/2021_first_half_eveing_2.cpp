#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <climits>
#include <cstdlib>

using namespace std;
// 2025 09 02 PM 0550
// [문제]
// NxN 나선형 미로에서 1,2,3번 유형 몬스터가 침략중이다 
//
// 플레이어는 격자 속 가운데 탑에서 몬스터를 제거할 것이다
//
// 1. 플레이어는 상하좌우중 주어진 공격 칸 수 만큼 몬스터 제거 가능
// 2. 비어있는 공간 만큼 몬스터는 앞으로 이동하여 빈공간을 체운다
// 3. 이때 몬스터 종류가 4번이상 반복해서 나오면 해당 몬스터도 삭제된다
// 4. 삭제된 이후, 몬스터들을 앞으로 당겨주고, 4번이상 또 나오면 또 삭제한다
// 이를 4번 나오는 몬스터가 없을 때 까지 반복시킨다
//
// 삭제가 끝난 이후, 몬스터를 차례대로 나열 했을 시 같은 숫자끼리 짝을 지어준다
// 이후 각 짝을 (총 개수, 숫자의 크기)로 바꿔서 다시 미로에 삽입한다...?
//
// 1 2 2 3 1 3 1 
//
// 1 1 
// 2 2
// 1 3
// 1 1
// 1 3 
// 1 1
//
// 단, 새로 생긴 배열이 기존 달팽이 격자 범위 넘으면 그건 싸그리 무시한다
//
// 위 과정이 끝나면 한 라운드가 종료 된다
//
// 1과 3과정에서 삭제되는 몬스터 번호는 점수에 합산된다
// 예로, 위 1번 과정에선 2x2, 3번 과정에서는 1x5, 3x4, 2x4 로 29점이 합산된다 
//
// 각 라운드별로 공격 방향, 공격 칸수가 주어질 때, 모든 라운드가 끝났을 시의 
// 스코어를 구해보거라
//
// 오우...
int dy[4] = {0, 1, 0, -1};  // 우 하 좌 상
int dx[4] = {1, 0, -1, 0};
int arr[26][26];
int n, m, p;  // 격자 크기, 라운드 수, 공격 칸수
int dir; // 공격 방향
int my, mx;
long long int score;

int direction[26][26];
int r_direction[26][26];

void direction_init() {
    for(int i = 1; i <= n; i++) { for(int j = 1; j <= n; j++) direction[i][j] = 4; }

    int y = 1; int x = 1;
    direction[y][x] = 0; // 우측 진행
    r_direction[y][x] = 2;
    int now_dir = 0;
    int r_now_dir = 2;

    bool isTurnFlag = false;
    while(!(y == my && x == mx)) {
        int ny = y + dy[now_dir]; int nx = x + dx[now_dir];  // 일단 다음 방향

        if (ny <= 0 || ny > n || nx <= 0 || nx > n) { now_dir = (now_dir + 1) % 4; isTurnFlag = true; continue; }
        if (direction[ny][nx] != 4) {now_dir = (now_dir + 1) % 4; isTurnFlag = true; continue;}

        direction[y][x] = now_dir;
        r_direction[y][x] = r_now_dir;
        if(isTurnFlag) {isTurnFlag = false; r_now_dir = (now_dir + 2) % 4; }
        y += dy[now_dir]; x += dx[now_dir];
    }
    r_direction[my][mx] = 2;
}


void remove_emptys() {
    vector<int> vals;

    // 중앙 왼쪽에서 r_direction으로 바깥으로 읽기
    int y = my, x = mx - 1;
    while (y >= 1 && y <= n && x >= 1 && x <= n) {
        if (arr[y][x] != 0) vals.push_back(arr[y][x]);
        int ri = r_direction[y][x];
        y += dy[ri]; x += dx[ri];
    }

    // 경로 초기화(0으로)
    y = my; x = mx - 1;
    while (y >= 1 && y <= n && x >= 1 && x <= n) {
        arr[y][x] = 0;
        int ri = r_direction[y][x];
        y += dy[ri]; x += dx[ri];
    }

    // 앞에서부터 다시 채우기
    y = my; x = mx - 1;
    int k = 0;
    while (y >= 1 && y <= n && x >= 1 && x <= n && k < (int)vals.size()) {
        arr[y][x] = vals[k++];
        int ri = r_direction[y][x];
        y += dy[ri]; x += dx[ri];
    }
}

bool check_fours() {
    // r_direction 순서로 경로를 1차화
    vector<int> v;
    int y = my, x = mx - 1;
    while (y >= 1 && y <= n && x >= 1 && x <= n) {
        if (arr[y][x] != 0) v.push_back(arr[y][x]);
        int ri = r_direction[y][x];
        y += dy[ri]; x += dx[ri];
    }
    if (v.empty()) return false;

    // 한 번의 폭발 수행
    bool exploded = false;
    vector<int> nv;
    for (int i = 0; i < (int)v.size(); ) {
        int j = i;
        while (j < (int)v.size() && v[j] == v[i]) j++;
        int cnt = j - i;
        if (cnt >= 4) {
            exploded = true;
            score += 1 * v[i] * cnt; // 번호 * 개수
        } else {
            for (int t = i; t < j; t++) nv.push_back(v[t]);
        }
        i = j;
    }

    // 결과를 다시 쓰기(경로 초기화 후 채움)
    y = my; x = mx - 1;
    while (y >= 1 && y <= n && x >= 1 && x <= n) {
        arr[y][x] = 0;
        int ri = r_direction[y][x];
        y += dy[ri]; x += dx[ri];
    }
    y = my; x = mx - 1;
    int idx = 0;
    while (y >= 1 && y <= n && x >= 1 && x <= n && idx < (int)nv.size()) {
        arr[y][x] = nv[idx++];
        int ri = r_direction[y][x];
        y += dy[ri]; x += dx[ri];
    }

    return exploded;
}

void insert_new() {
    vector<pair<int,int> > nums; // (개수, 값)

    // 중앙 왼쪽부터 r_direction으로 그룹화
    int y = my, x = mx - 1;
    while (y >= 1 && y <= n && x >= 1 && x <= n && arr[y][x] != 0) {
        if (nums.empty() || nums.back().second != arr[y][x]) nums.push_back(make_pair(1, arr[y][x]));
        else nums.back().first++;
        int ni = r_direction[y][x];
        y += dy[ni]; x += dx[ni];
    }

    // 경로 초기화(0으로)
    y = my; x = mx - 1;
    while (y >= 1 && y <= n && x >= 1 && x <= n) {
        arr[y][x] = 0;
        int ni = r_direction[y][x];
        y += dy[ni]; x += dx[ni];
    }

    // (개수, 값) 시퀀스로 다시 기입 (넘치면 중단)
    y = my; x = mx - 1;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (y < 1 || y > n || x < 1 || x > n) return;
        arr[y][x] = nums[i].first;
        int ni = r_direction[y][x];
        y += dy[ni]; x += dx[ni];

        if (y < 1 || y > n || x < 1 || x > n) return;
        arr[y][x] = nums[i].second;
        ni = r_direction[y][x];
        y += dy[ni]; x += dx[ni];
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

    my = mx = (n+1)/2;
    direction_init();    

    while(m--) {
        cin >> dir >> p;
        for (int i = 1; i <= p; i++) { score += arr[my+i*dy[dir]][mx+i*dx[dir]]; arr[my+i*dy[dir]][mx+i*dx[dir]] = 0; }  // 없애버리는 루틴
        remove_emptys();
        while (check_fours()) {remove_emptys();}    
        insert_new();
    }

    cout << score << endl;
    return 0;
}
