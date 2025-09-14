#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <climits>

using namespace std;

int n, m;  // 격자 크기, 남길 병원 수 (depth 용)
int visited[51][51]; // dist용 struct 만들기 귀찮음.
int arr[51][51];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int minVal = INT_MAX;

vector<pair<int,int> > hos;  // 병원 좌표 (추후 백트래킹 할거임)
vector<pair<int,int> > people; // 사람 좌표 (각자 bfs 할 듯 하다)

/* 아니 굳이 bfs로 풀 이유가 없는데? 그냥 덧셈 뺄셈만 하면 되는데??
void bfs() {
    int result = 0;
    for (int i = 0; i < (int)people.size(); i++) {
        queue<pair<int,int> > q;
        memset(visited, 0x00, sizeof(visited));
        int y = people[i].first; int x = people[i].second;
        q.push({y, x});
        visited[y][x] = 1;  // 나중에 최종 거리 계산할 때는 1 빼줘야함
        
        while(!q.empty()) {
            int cy = q.front().first;
            int cx = q.front().second;
            int c_dist = visited[cy][cx];
            q.pop();

            if (arr[cy][cx] == 2) { result += c_dist - 1; break; }
            for (int i = 0; i < 4; i++) {
                int ny = cy + dy[i]; int nx = cx + dx[i];
                if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
                if (visited[ny][nx] != 0) continue;

                visited[ny][nx] = c_dist + 1;
                q.push({ny, nx});
            }
        }
    }
    minVal = min(minVal, result);
}
*/

vector<pair<int,int> > sels;

void calc_dist() {
    int result = 0;
    for (int i = 0; i < (int)people.size(); i++) {
        int py = people[i].first; int px = people[i].second;
        int min_dist = INT_MAX;
        for (int j = 0; j < (int)sels.size(); j++) {
            int dist = abs(py - sels[j].first) + abs(px - sels[j].second);
            min_dist = min(min_dist, dist);
        }
        result += min_dist;
    }

    minVal = min(minVal, result);
}

void dfs(int idx, int depth) {
    if (depth == m) {
        calc_dist();
        return;
    }

    for (int i = idx + 1; i < (int)hos.size(); i++) {
        int y = hos[i].first; int x = hos[i].second;
        sels.push_back({y, x});
        dfs(i, depth+1);
        sels.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    
    int val;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> val;
            if (val == 1) people.push_back({i, j});
            else if (val == 2) hos.push_back({i, j});
        }
    }

    dfs(-1, 0);
    cout << minVal << endl;
    return 0;
}
