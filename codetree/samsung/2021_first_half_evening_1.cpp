#include <iostream>
#include <climits>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace std;


/* [문제]
 * 
 * NxN에 나무 심을거다 
 * 특수 영양제로 키워야 하고, 1x1 땅에 있는 나무 높이 1 증가 
 * 만약 해당 땅에 씨앗만 있으면 높이 1로 만듦
 *
 * 좌하단 4칸에 영양제가 초기에 놓임 
 *
 * 각 특수 영양제는 이동 규칙 있음
 * 우측 기준 반시계 후루룩 총 8개
 *
 * 격자 밖은 연결돼있음 !!
 *
 * 1년동안 나무는 아래처럼 성장한다 
 * 1. 영양제는 이동
 * 2. 영양제 이동 후 해당 땅에 영양제 투입, 투입 후 영양제 사라짐
 * 3. 영양제 대각선으로 인접한 방향에 높이가 1 이상인 나무가 있으면 그만큼 성장
 *     단! 이 때 격자 벗으면 고려 안함
 * 4. 영양제 투입한 나무 제외하고 높이 2 이상인 나무는 2 베어서 영양제 사고 동일 위치에 영양제 둠
 */


int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int arr[16][16];
int n, m;
int dir, p;
int cdy[4] = {1, 1, -1, -1};
int cdx[4] = {1, -1, 1, -1};
bool skip[16][16];

vector<pair<int,int>> goods; // 이름 진짜 못짓네

// 영양제 이동
void goods_move() {
    p %= n;

    for (int i = 0; i < (int)goods.size(); i++) {
         goods[i].first = ((goods[i].first + dy[dir] * p) % n + n) % n;
         goods[i].second = ((goods[i].second + dx[dir] * p) % n + n) % n;
         if (goods[i].first == 0) goods[i].first = n;
         if (goods[i].second == 0) goods[i].second = n;
        arr[goods[i].first][goods[i].second]++;
    }
}

// 영양제 vector 확인해서 대각선 체크 후, 키워주기
void check_skip () {
    for (int i = 1; i <= n; i++) {
        for (int j =1; j <= n; j++) {
            cout << skip[i][j] <<  " ";
        }
        cout << endl;
    }
    cout << endl;
}

void tree_grow_up() {
    memset(skip, 0x00, sizeof(skip));

    for (int i = 0; i < (int)goods.size(); i++) {
        int y = goods[i].first; int x = goods[i].second;
        skip[y][x] = true;

        for (int j = 0; j < 4; j++) {
            int ny = y + cdy[j]; int nx = x + cdx[j];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
            if (arr[ny][nx] < 1) continue;
            arr[y][x]++;
        }
    }
    goods.clear();
    check_skip();
}

// 나무 자르고 새 영양제 채워넣기
void cut_tree_and_new_goods() {
    for (int i = 1; i<= n; i++) {
        for (int j = 1; j<= n; j++) {
            cout << arr[i][j] << " ";
            if (skip[i][j]) continue;
            if (arr[i][j] < 2) continue;
            arr[i][j] -= 2;
            goods.push_back({i, j});
        }
        cout << endl;
    }
    cout << endl;
}

// 최종 출력
void check_trees() {
    int cnt = 0;
    for (int i = 1 ; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cnt += arr[i][j];
        }
    }
    cout << cnt << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i++) {
        for (int j =1 ; j <= n; j++) {
            cin >> arr[i][j];
        }
    }

    goods.push_back({n-1, 1}); goods.push_back({n-1, 2});
    goods.push_back({n, 1}); goods.push_back({n,2});

    int turn = 1;
    while(m--) {
        cout << turn++ << endl;

        cin >> dir >> p;
        dir--; // 1 ~ 8 입력이네 ㅎ;

        goods_move();
        tree_grow_up();
        cut_tree_and_new_goods();
    }
    check_trees();
    return 0;
}
