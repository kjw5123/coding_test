#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>

using namespace std;

/* [문제]
 * NxN 격자에 바이러스를 배양할 것이다
 * 초기엔, 각 칸에 5만큼 양분이 있으며,
 * m개의 바이러스로 시작한다
 *
 *
 * [1 사이클 당 규칙]
 * 1. 각 바이러스는 본인이 위치한 1x1에서 양분 섭취
 *    본인 나이만큼 양분을 먹음
 *    같은 칸에 여러개의 바이러스가 있을 수 있음
 *    양분을 먹고 나면 나이가 1 증가
 *    양분이 부족해서 본인 나이만큼 먹을 수 없으면 사망
 *
 * 2. 모든 바이러스가 양분을 먹은 후, 죽은 바이러스는 양분으로 변화
 *    죽은 바이러스 마다 나이를 2로 나눈 값이 바이러스가 있던 칸에 양분으로 추가됨 
 *    정수임
 *
 * 3. 이후 바이러스 번식 진행
 *    5 배수의 바이러스만 진행하며, 인접 8칸 위치에 나이가 1인 바이러스가 생성된다
 *
 * [입력]
 * 첫번 째 줄엔 arr 크기 n
 * 바이러스 개수 m
 * 총 사이클 수 k가 입력된다
 * 그 다음으로 매 턴 종료시 추가할 양분 양 정보
 * 그리고 y, x, 바이러스 나이 정보 준다
 * */

int hdy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
int hdx[8] = {1, -1, 1, -1, 0, 0, -1, 1};
int n , m, turn;
int arr_adder[11][11];  //  매턴 증가시킬 값
int food[11][11];  //  실제 저장된 양분 값
vector<int> virus[11][11];  // 바이러스 정보
vector<pair<int,int>> copys;
int temp[11][11];

void vector_init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (virus[i][j].size() < 2) continue;
            sort(virus[i][j].begin(), virus[i][j].end());
        }
    }
    copys.clear();
}

void eat_food() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (virus[i][j].empty()) continue;
            for (vector<int>::iterator it = virus[i][j].begin(); it != virus[i][j].end();) {
                if (food[i][j] - *it < 0) {
                    temp[i][j] += (*it) / 2;
                    it = virus[i][j].erase(it);

                } else {
                    food[i][j] -= *it;
                    *it += 1;
                    if (*it % 5 == 0) copys.push_back({i, j});
                    it++;
                }
            }
        }
    }
}

void explode() {
    for (int i = 0; i < (int)copys.size(); i++) {
        int y = copys[i].first; int x = copys[i].second;
        for (int j = 0; j < 8; j++) {
            int ny = y + hdy[j]; int nx = x + hdx[j];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
            virus[ny][nx].push_back(1);
        }
    }
}

void food_up() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            food[i][j] += temp[i][j];
        }
    }
}

int check_remain_virus() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cnt += virus[i][j].size();    
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> turn;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr_adder[i][j];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            food[i][j] = 5;
        }
    }

    int y , x, val;
    for (int i = 0; i < m; i++) {
        cin >> y >> x >> val;
        virus[y][x].push_back(val);
    }
    
    while(turn--) {
        memcpy(temp, arr_adder, sizeof(temp));
        vector_init();
        
        eat_food();
        explode();
        food_up();
    }
    
    cout << check_remain_virus() << endl;
    return 0;
}
