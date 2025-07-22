#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

/* [규칙]
 * 1. 기본적으로 스티커를 회전시키지 않고 모눈종이에서 때어낸다
 * 2. 다른 스티커와 안 곂치고, 격자를 벗어나지 않는 위치 찾기
 *    격자 위부터 스티커를 채우고자 한다
 *    여러 곳에 붙일 수 있으면 가장 '위', 그 중에서도 '왼쪽'을 우선시 한다
 * 3. 붙일 수 있는 곳이 없다면 시계 방향으로 90도 돌리고 2번 다시 트라이
 *    0, 90, 180, 270 전부 안되면 해당 스티커 '폐기'
 * */

int n, m;  // arr size
int k;     // sticker quantity
int r, c;  // sticker size

bool arr[41][41];  // 오랜만에 0 base로 풀이해보자
bool sticker[11][11];

// 혹시 몰라서 스티커 r,c 저장용 (인덱스 동일해서 필요할 때 꺼내쓰면 됨)
pair<int, int> sticker_size[101];
vector<pair<int, int>> stickers[101];  // 좌표만 따서 넣을 생각

// 어쨌든 0 ~ N^2 완전 탐색 하면서 좌표 확인하는 식으로 진행하면 될듯 하다
// rotate_sticker랑 attach_sticker 정도로 함수 분리하면 잘 구현될듯 하다
// cnt 하나 선언하고 rotate_sticker 횟수 따라서 증가 시키다 안되면 걍 continue 하면 될듯

void print_arr_true() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j]) cnt++;
            // cout << arr[i][j] << " ";
        }
        // cout << endl;
    }
    // cout << endl;
    cout << cnt << endl;
}

void rotate_sticker(int idx) {
    for (int i = 0; i < (int)stickers[idx].size(); i++) {
        int temp_y = stickers[idx][i].first;
        stickers[idx][i].first = stickers[idx][i].second;
        stickers[idx][i].second = sticker_size[idx].first - temp_y - 1;
    }
    
    int temp_y = sticker_size[idx].first;
    sticker_size[idx].first = sticker_size[idx].second;
    sticker_size[idx].second = temp_y;
}

bool attach_sticker(int idx) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int cnt = 0;

            for (int p = 0; p < (int)stickers[idx].size(); p++) {
                int y = stickers[idx][p].first + i;
                int x = stickers[idx][p].second + j;
                if (y <= 0 || y > n || x <= 0 || x > m) break;
                if (arr[y][x]) break;
                cnt++;
            }

            if (cnt == (int)stickers[idx].size()) {
                for (int p = 0; p < (int)stickers[idx].size(); p++) {
                    int y = stickers[idx][p].first + i;
                    int x = stickers[idx][p].second + j;
                    arr[y][x] = true;
                }
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        cin >> r >> c;
        sticker_size[i] = {r, c};

        // i j k 봉인 당했다 이런
        for (int p = 0; p < r; p++) {
            for (int q = 0; q < c; q++) {
                bool val; cin >> val;
                if (val) stickers[i].push_back({p, q});
            }
        }
    }

    for (int i = 0; i < k; i++) {
        int cnt = 0;
        while (cnt++ <= 3) {
            if(attach_sticker(i)) break;
            rotate_sticker(i);
        }
    }    

    print_arr_true();    

    return 0;
}
