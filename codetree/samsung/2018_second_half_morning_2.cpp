#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

/* [문제]
 * 
 * nxn 격자가 있다, 1x1 크기 겨란들 담겨있다
 * 계란이 한데 쏠려있으면 기분이 안좋아서 모종의 변화를 주고자 한다
 *
 * [규칙]
 * 1. 하나의 선을 맞대고 있는 두 계란틀 간 양차이가 L 이상! R 이하!면 선을 긋는다
 * 2. 모든 계란 틀에 대해 검사를 진행 후, 위의 규칙에 해당하는 모든 계란틀의선을 분리한다
 * 3. 선의 분리를 통해 합쳐진 계란틀의 계란은 다 스깠다가 다시 나눈다
 * 4. 나눌 때, 합처진 총 합 / 계란틀 수로 처리 하며, 편의상 소수점은 다 버려버린다
 * 
 * [사견]
 *
 * 깔끔하게, 매 턴마다
 * bfs를 해서 
 *
 * */
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int n, l, r;
int arr[51][51];
int temp[51][51];
bool visited[51][51];
int array_num;

void bfs(int y, int x) {
    queue<pair<int,int> > q;
    vector<pair<int,int>> v;

    int total_val = arr[y][x];
    visited[y][x] = true;

    q.push({y, x});
    v.push_back({y, x});

    while(!q.empty()) {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;

            int diff = abs(arr[ny][nx] - arr[cy][cx]);
            if (diff < l || diff > r) continue;
            if (visited[ny][nx]) continue;

            visited[ny][nx] = true;
            total_val += arr[ny][nx];
            q.push({ny, nx});
            v.push_back({ny, nx});
        }
    }

    if(v.size() >= 2) {
        array_num++;
        // cout << "My y x is " << y << " " << x << endl;
        // cout << "value is " << total_val / v.size() << endl;
        for (int i = 0; i < (int)v.size(); i++) {
            temp[v[i].first][v[i].second] = total_val / v.size();
        }    
    }
}

void arr_check() {
    for (int i = 1; i <= n; i++) {
        for (int j =1; j <= n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> l >> r;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }
    
    int turn = 0;
    while(true) {
        memset(visited,0x00,sizeof(visited));
        array_num = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if(visited[i][j]) continue;
                temp[i][j] = arr[i][j];
                bfs(i, j);    
            }
        }

        if (array_num == 1) break;
        memcpy(arr, temp, sizeof(arr));
        // arr_check();
        turn++;
    }
    cout << turn << endl;
    return 0;
}
