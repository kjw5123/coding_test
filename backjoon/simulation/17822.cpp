#include <iostream>
#include <deque>
#include <algorithm>
#include <utility>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

/* [규칙]
 * 반지름이 1~N인 원판이 작아지는 순으로 놓여있다
 * 원판의 중심은 전부 동일
 * 원판의 반지름이 i 면 해당 원판을 i번째 원판이라 지칭
 *
 * 각 원판에는 M개의 정수가 적힘
 * i번째 원판에 적힌 j번째 수의 위치는 i, j라고 표현 (1 <= j <= M)
 * i,1은 i,2와 i,j에 인접하다  (한 원판 좌우)
 * 1,j는 2,j랑 인접하다 (두 원판 상하)
 *
 * 이제 원판을 시계, 반시계로 회전 시킬 수 있다 (독립적으로다가) (deque 당선!!)
 * 
 * 회전 방법은 미리 정해져있고, 규칙이 있다
 * 1. 번호가 x의 배우신 원판을 d 방향으로 k칸 회전시킨다
 *    d가 0이면 시계 방향, 1이면 반시계
 * 2. 원판에 수가 남아있으면 인접하면서 수가 같은걸 찾는다 (수 없애면 INT_MIN로 처리하던가 할듯)
 *    수가 남아있으면 인접하면서 같은 수를 지운다 
 *    없으면 원판에 적인 수의 평균을 구하고, 평균보다 큰 수는 1을 빼고 작은 수는 1을 더한다
 *    원판을 T 번 회전 시킨 후, 원판에 적힌 수 총합을 구하자 (INT_MIN 무시)
 *
 * */
int n, m;
int t;
deque<int> dq[51];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void print_dq() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (dq[i][j] != INT_MIN) cout << dq[i][j] << " ";
            else cout << -1 << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void rotate_dq(int x, int dir, int r_num) {
    int mul_x = 0;
    if (dir == 0) {  // 시계 방향
        for (int i = 1; i <= n; i++) {
            mul_x = x * i;
            if (mul_x > n) break;

            for (int j = 0; j < r_num; j++) {
                int val = dq[mul_x].back();
                dq[mul_x].pop_back();
                dq[mul_x].push_front(val);
            }
        }

    } else {
        for (int i = 1; i <= n; i++) {
            mul_x = x * i;
            if (mul_x > n) break;

            for (int j = 0; j < r_num; j++) {
                int val = dq[mul_x].front();
                dq[mul_x].pop_front();
                dq[mul_x].push_back(val);
            }
        }
        
    }
}

// 2중 for문으로 검사하자
// dy dx 비스무리한 무언가를 해보자
// 흠...
//
// 그거랑 별개로 예외 처리할 게 4모서리, 4꼭지, 그외 다수 이다
// 왼윗꼭지: last, 1, 아래랑 비교
// 오윗꼭지: 0, last - 1, 아래
// 왼아랫꼭지: last, 1, 위랑 비교
// 오아랫꼭지: front, last - 1, 위
//
// 윗모서리: j - 1, j + 1, 아래
//
bool to_delete[51][51];
void check_nums() {
    memset(to_delete, 0x00, sizeof(to_delete));
    int last = m - 1;
    int total_val = 0;
    int actived = 0;
    bool is_no_delete = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (dq[i][j] == INT_MIN) continue;  // 지울거면 굳이 볼 필요도 없지 -> 아니 봐야하긴 하겠다
            // 아니 근데 아래 로직 굳이 반복문에 넣을 필요 없지 않나 ? 에휴 됐다..
            if (i == 1 && j == 0) {
                if (dq[i][j] == dq[i][last]) {
                    to_delete[i][j] = true;
                    to_delete[i][last] = true;
                    is_no_delete = false;
                }
                if (dq[i][j] == dq[i][1]) {
                    to_delete[i][j] = true;
                    to_delete[i][1] = true;
                    is_no_delete = false;
                }
                if (dq[i][j] == dq[i+1][j]) {
                    to_delete[i][j] = true;
                    to_delete[i+1][j] = true;
                    is_no_delete = false;
                }

            } else if (i == 1 && j == last) {
                if (dq[i][j] == dq[i][0]) {
                    to_delete[i][j] = true;
                    to_delete[i][0] = true;
                    is_no_delete = false;
                }
                if (dq[i][j] == dq[i][last-1]) {
                    to_delete[i][j] = true;
                    to_delete[i][last-1] = true;
                    is_no_delete = false;
                }
                if (dq[i][j] == dq[i+1][j]) {
                    to_delete[i][j] = true;
                    to_delete[i+1][j] = true;
                    is_no_delete = false;
                }

            } else if (i == n && j == 0) {
                if (dq[i][j] == dq[i][last]) {
                    to_delete[i][j] = true;
                    to_delete[i][last] = true;
                    is_no_delete = false;
                }
                if (dq[i][j] == dq[i][1]) {
                    to_delete[i][j] = true;
                    to_delete[i][1] = true;
                    is_no_delete = false;
                }
                if (dq[i][j] == dq[i-1][j]) {
                    to_delete[i][j] = true;
                    to_delete[i-1][j] = true;
                    is_no_delete = false;
                }

            } else if (i == n && j == last) {
                if (dq[i][j] == dq[i][last-1]) {
                    to_delete[i][j] = true;
                    to_delete[i][last-1] = true;
                    is_no_delete = false;
                }
                if (dq[i][j] == dq[i][0]) {
                    to_delete[i][j] = true;
                    to_delete[i][0] = true;
                    is_no_delete = false;
                }
                if (dq[i][j] == dq[i-1][j]) {
                    to_delete[i][j] = true;
                    to_delete[i-1][j] = true;
                    is_no_delete = false;
                }

            } else {
                for (int k = 0; k < 4; k++) {
                    int ny = i + dy[k]; int nx = j + dx[k];
                    if (nx == m) nx = 0;
                    if (ny <= 0 || ny > n || nx < 0 || nx > last) continue;

                    if (dq[i][j] == dq[ny][nx]) {
                        to_delete[i][j] = true;
                        to_delete[ny][nx] = true;
                        is_no_delete = false;
                    }
                }
            }

            if (dq[i][j] != INT_MIN) {
                total_val += dq[i][j];
                actived++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (to_delete[i][j]) dq[i][j] = INT_MIN;
        }
    }

    if (is_no_delete) {
        double avg = (double)total_val / (double)actived;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                if (dq[i][j] == INT_MIN) continue;  // 깜빡하고 오버플로우 시킬뻔;
                if (dq[i][j] > avg) dq[i][j]--;
                else if (dq[i][j] < avg) dq[i][j]++;
            }
        }
    }
}

void print_nums() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (dq[i][j] != INT_MIN) cnt += dq[i][j];
        }
    }
    cout << cnt << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> t;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int val; cin >> val;
            dq[i].push_back(val);
        }
    }
    int x, d, k;
    for (int i = 0; i < t; i++) {
        cin >> x >> d >> k; // 회전 원판 대상(배수), 방향, 회전 칸 수
        // 1. 회전부터
        rotate_dq(x, d, k);
        // 2. 수 처리
        check_nums();
        // cout << i + 1 << " delete done " << endl;
        // print_dq();
    }

    print_nums();
    return 0;
}
