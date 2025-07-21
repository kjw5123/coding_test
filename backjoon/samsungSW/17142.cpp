#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
#include <climits>

using namespace std;
int n, m;
int arr[51][51];
bool visited[51][51];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int zero_cnt;

struct ad {
    int y;
    int x;
    int turn;
};

vector<pair<int, int> > virus_list;
vector<pair<int, int> > selected_virus;


int bfs() {
    if (zero_cnt == 0) return 0;
    queue<ad> q;
    for (int i = 0; i < (int)selected_virus.size(); i++) {
        q.push({selected_virus[i].first, selected_virus[i].second, 0});
        visited[selected_virus[i].first][selected_virus[i].second] = true;
    }
    
    int turn = 0;
    int zeros = zero_cnt;
    while(!q.empty()) {
        int cur_y = q.front().y;
        int cur_x = q.front().x;
        int cur_turn = q.front().turn;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = cur_y + dy[i];
            int nx = cur_x + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
            if (arr[ny][nx] == 1 || visited[ny][nx] == true) continue;

            visited[ny][nx] = true;
            q.push({ny, nx, cur_turn + 1});
            turn = cur_turn + 1;
            if(arr[ny][nx] == 0) {
                zeros--;
                if (zeros == 0) return cur_turn + 1;
            }
        }
    }

    if(zeros == 0) return turn;
    else return -1;
}

int dfs(int idx, int depth) {
    if (depth == m) {
        memset(visited, 0x00, sizeof(visited));
        int now_val = bfs();
        return now_val;
    }
    int minVal = INT_MAX;
    for (int i = idx; i < (int)virus_list.size(); i++) {
        selected_virus.push_back({virus_list[i].first, virus_list[i].second});
        int return_val = dfs(i+1, depth+1);
        if (return_val != -1) minVal = min(minVal, return_val);
        selected_virus.pop_back();
    }

    if (minVal == INT_MAX) return -1;
    else return minVal;
}

void zero_cnt_insert() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (arr[i][j] == 0) zero_cnt++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 2) virus_list.push_back({i, j});
        }
    }
    zero_cnt_insert();
    int minmin = dfs(0, 0);
    cout << minmin << endl;
    return 0;
}
