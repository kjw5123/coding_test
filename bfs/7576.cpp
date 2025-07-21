#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
int n, m;
int arr[1001][1001];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void arr_print() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    } 
    cout << endl;
}
bool isZero() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] == 0) return true;
        }
    } 
    return false;
}

int maxVal() {
    int maxi = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            maxi = max(arr[i][j], maxi);
        }
    } 
    return maxi;
}

void bfs(vector<pair<int, int> > v) {
    queue<pair<int, int> > q;
    for (int i = 0; i < v.size(); i++) {
        q.push({v[i].first, v[i].second});
    }

    while(!q.empty()) {
        int now_y = q.front().first;
        int now_x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now_y + dy[i];
            int nx = now_x + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > m) continue;
            if (arr[ny][nx] == 0) {
                arr[ny][nx] = arr[now_y][now_x] + 1;
                q.push({ny, nx});
            }
        }
//        arr_print();
    }

    if (isZero()) cout << -1 << endl;
    else cout << maxVal() -1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> m >> n;
    vector<pair<int, int> > v;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 1) {
                v.push_back({i, j});
            }
        }
    }
    
    bfs(v);
    return 0;
}
