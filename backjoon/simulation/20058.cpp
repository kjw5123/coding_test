#include <iostream>
#include <cstring>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;
int n, q, l;
int arr_size = 1;
int rotate_len = 1;
int arr[65][65];
int rotated[65][65];
bool visited[65][65];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int check_arr() {
    int cnt = 0;
    for (int i = 1; i <= arr_size; i++) {
        for (int j = 1; j <= arr_size; j++) {
            cnt += arr[i][j];
        }
    }
    return cnt;
}

void check_middle(int flag) {
    for (int i = 1; i <= arr_size; i++) {
        for (int j = 1; j <= arr_size; j++) {
            if (flag == 1) cout << rotated[i][j] << " ";
            else cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void real_rotate(int y, int x) {
    for(int i = 0; i < rotate_len; i++) {
        for (int j = 0; j < rotate_len; j++) {
            rotated[j + y][rotate_len - i - 1 + x] = arr[i+y][j+x];
        }
    }
}

void arrs_rotate() {
    for (int i = 1; i <= arr_size; i += rotate_len) {
        for (int j = 1; j <= arr_size; j += rotate_len) {
            real_rotate(i, j);
        }
    }
    // check_middle(1);
}

void defreeze() {
    for (int i = 1; i <= arr_size; i++) {
        for (int j = 1; j <= arr_size; j++) {
            if (rotated[i][j] > 0) {
                int cnt = 0;
                for (int k = 0; k < 4; k++) {
                    int ny = i + dy[k]; int nx = j + dx[k];
                    if (ny <= 0 || ny > arr_size || nx <= 0 || nx > arr_size) continue;
                    if (rotated[ny][nx] > 0) cnt++;
                }
                if (cnt < 3) arr[i][j] = rotated[i][j]-1;
                else arr[i][j] = rotated[i][j];

            } else arr[i][j] = rotated[i][j];
        }
    }
    // check_middle(0);
}

void visited_init() {
    for (int i = 1; i <= arr_size; i++) {
        for (int j = 1; j <= arr_size; j++) {
            if (arr[i][j] == 0) visited[i][j] = true;
        }
    }
}
int bfs(int y, int x) {
    queue<pair<int, int> > q;
    q.push({y, x});
    visited[y][x] = true;
    int dunguri = 1;

    while(!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        for (int i =0; i < 4; i++){
            int ny = cur_y + dy[i]; 
            int nx = cur_x + dx[i];
            if (ny <= 0 || ny > arr_size || nx <= 0 || nx > arr_size) continue;
            if (arr[ny][nx] == 0) continue;
            if (!visited[ny][nx]) {
                q.push({ny,nx});
                visited[ny][nx] = true;
                dunguri++;
            }
        }
    }
    return dunguri;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for (int i = 0; i < n; i++) arr_size *= 2;

    for (int i = 1; i <= arr_size; i++) {
        for (int j = 1; j <= arr_size; j++) {
            cin >> arr[i][j];
        }
    }
    for (int i = 0; i < q; i++) {
        rotate_len = 1;
        cin >> l;
        for (int i = 0; i < l; i++) rotate_len *= 2;
        arrs_rotate();
        defreeze();
    }

    int total = check_arr();
    cout << total << endl;
    int maxVal = 0;
    visited_init();
    for (int i = 1; i <= arr_size; i++) {
        for (int j = 1; j <= arr_size; j++) {
            if(!visited[i][j]) maxVal = max(maxVal, bfs(i,j));
        }
    }
    cout << maxVal << endl;
    return 0;
}
