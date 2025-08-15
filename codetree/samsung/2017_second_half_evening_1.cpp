#include <iostream>
#include <deque>
#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

/* [문제]
 * 4개의 팔각 의자에 사람들이 앉았다
 * N, S로 나뉜다
 * 1 ~ 4로 팔각 의자에 번호가 메겨져 있다
 * 
 *
 * 각 의자를 k번 회전시키고자 하고, 45도 돌릴 것이다, 즉 1칸 이동한다
 * 시계, 반시계 방향 회전 전부 가능하다
 *
 * [회전 규칙]
 * 회전 시킬 의자의 방향, 번호가 입력됨
 * n번 째 의자가 회전하기 전에 인접한 의자에 있는 사람이 출신이 다르면 
 * 인접 의자는 반대ㅗㄹ 이동
 * 회전 시킨 후, 그로 인한 모든 회전이 끝날 때 까지 대기
 *
 * 회전 끝나고, 각 의자의 12시 방향에 앉아있는 ㄴ마쪽 사람 착석 여부를 알아내라
 *
 * */

deque<int> chairs[4];  // 0은 북쪽, 1은 남쪽
int k;
int c_num, dir; // 1은 시계, -1은 반시계

// 시계 방향 회전 == chairs[i].back을 push_front() 시키기
// 반시계 방향 최전 == chairs[i].front()를 push_back() 시키기

// idx = 2 (우), idx = 6 (좌)
// 나보다 작은 chair에 대해
// 내 좌랑 상대 우랑 비교
// 나보다 큰 chair에 대해
// 내 우랑 상대 좌랑 비교

bool rotated[4];

void rotate_init() {
    memset(rotated, 0x00, sizeof(rotated));
}

int d[2] = {-1, 1};

int reverse_dir(int direction) {
    if (direction == 1) return -1;
    else return 1;
}

void rotate_chair(int idx) {
    queue<pair<int,int>> q;
    q.push({idx, dir});
    rotated[idx] = true;
    vector<pair<int,int>> v;
    v.push_back({idx,dir});

    while(!q.empty()) {
        int c_idx = q.front().first;
        int c_dir = q.front().second;
        q.pop();

        
        for (int i = 0; i < 2; i++) {
            int n_idx = c_idx + d[i];
            if (n_idx < 0 || n_idx >= 4) continue;
            if (rotated[n_idx]) continue;
            rotated[n_idx] = true;

            if (i == 0) {  // 나보다 작을 때 
                if (chairs[c_idx][6] != chairs[n_idx][2]) {
                    q.push({n_idx, reverse_dir(c_dir)});
                    v.push_back({n_idx, reverse_dir(c_dir)});
                }
            } else {
                if (chairs[c_idx][2] != chairs[n_idx][6]) {
                    q.push({n_idx, reverse_dir(c_dir)});
                    v.push_back({n_idx, reverse_dir(c_dir)});
                }

            }
        }
    }

    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i].second == 1) {
            int temp = chairs[v[i].first].back();
            chairs[v[i].first].pop_back();
            chairs[v[i].first].push_front(temp);
        } else {
            int temp = chairs[v[i].first].front();
            chairs[v[i].first].pop_front();
            chairs[v[i].first].push_back(temp);
        }
    }
}

int main() { 
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    char val;
    for (int i = 0; i < 32; i++) {
        cin >> val;
        chairs[i/8].push_back((int)val - 48);
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> c_num >> dir;
        rotate_chair(--c_num);
        rotate_init();
    }

    cout << 1 * chairs[0][0] + 2 * chairs[1][0] + 4 * chairs[2][0] + 8 * chairs[3][0]  << '\n';

    return 0;
}
