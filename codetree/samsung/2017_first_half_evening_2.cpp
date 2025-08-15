#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int n, m;
// 불: 2, 벽: 1, 빈칸: 0
vector<pair<int,int>> fires;
vector<pair<int,int>> zeros;
int arr[9][9];
int temp[9][9];
bool visited[9][9];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int result = INT_MIN;

int count_not_fired() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] != 1 && !visited[i][j]) cnt++;
        }
    }
    return cnt;
}

void bfs() {
    queue<pair<int,int> > q;
    for (int i = 0; i < (int)fires.size(); i++) {
        visited[fires[i].first][fires[i].second] = true;
        q.push({fires[i].first, fires[i].second});
    }
    
    while(!q.empty()) {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > m) continue;
            if (visited[ny][nx]) continue;
            if (arr[ny][nx] == 1) continue;
            visited[ny][nx] = true;
            q.push({ny, nx});
        }
    }

    result = max(result, count_not_fired());
}

vector<pair<int,int>> walls;
void dfs(int idx, int depth) {
    if (depth == 3) {
        for (int i = 0; i < (int)walls.size(); i++) arr[walls[i].first][walls[i].second] = 1;
        bfs();
        for (int i = 0; i < (int)walls.size(); i++) arr[walls[i].first][walls[i].second] = 0;
        memset(visited, 0x00, sizeof(visited));
        return;
    } 

    for (int i = idx + 1; i < (int)zeros.size(); i++) {
        walls.push_back(zeros[i]);
        dfs(i, depth+1);
        walls.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 2) { fires.push_back({i,j}); arr[i][j] = 0; }
            else if (arr[i][j] == 0) zeros.push_back({i,j});
        }
    }

    dfs(-1, 0);

    cout << result << endl;
    return 0;
}
