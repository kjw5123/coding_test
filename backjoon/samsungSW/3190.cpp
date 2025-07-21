#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include <deque>
#include <cstring>

using namespace std;

int n, k, y, x, l;
int arr[101][101];
deque<pair<int, char> > dir;
int playing_time = 1;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

struct parts {
    int y;
    int x;
    int dir;
};

deque<parts> body;
parts head = {1, 1, 1};   // 좌상단 오른쪽 direction 가진채로 스타트

bool isBody() {
    for (int i = 0; i < body.size(); i++) {
        if(body[i].y == head.y && body[i].x == head.x) return true;
    }
    return false;
}

void isTimeToChangeDir() {
    if (!dir.empty()) {
        if (dir.front().first == playing_time) {
            if (dir.front().second == 'L')
                head.dir = (head.dir + 3) % 4;
            else
                head.dir = (head.dir + 1) % 4;
            dir.pop_front();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    memset(arr, 0xFF, sizeof(arr));

    cin >> n >> k;
    for(int i = 0; i < k; i++) {
        cin >> y >> x;
        arr[y][x] = 5; // 사과
    }

    cin >> l;
    for (int i = 0; i < l; i++) {
        int times; char direction;
        cin >> times >> direction;
        dir.push_back({times, direction});
    }

    body.push_back(head); // 시작 위치도 몸통에 포함

    while(true) {
        int ny = head.y + dy[head.dir];
        int nx = head.x + dx[head.dir];

        // 벽 충돌 체크
        if (ny <= 0 || ny > n || nx <= 0 || nx > n) break;

        head.y = ny;
        head.x = nx;

        // 몸통 충돌 체크
        if (isBody()) break;

        bool isApple = false;
        if (arr[ny][nx] == 5) isApple = true;

        if (isApple) {
            body.push_front(head);
            arr[ny][nx] = -1;
        } else {
            body.push_front(head);
            body.pop_back();
        }

        isTimeToChangeDir();  // dir 정보에 따라 head.dir 변경

        playing_time++;
    }

    cout << playing_time << endl;
    return 0;
}

