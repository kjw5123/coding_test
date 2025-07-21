#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};


int n, l, r;
int arr[51][51];
bool guild[51][51];


bool bfs(int y, int x) {
    queue<pair<int, int> > q;
    vector<pair<int, int> > v;
    q.push({y, x});
    v.push_back({y, x});
    guild[y][x] = 1;

    int total_val = arr[y][x];

    while(!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        for(int i = 0; i < 4; i++) {
            int ny = cur_y + dy[i];
            int nx = cur_x + dx[i];
            if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;
            if (guild[ny][nx] == 1) continue;

            int diff = abs(arr[cur_y][cur_x] - arr[ny][nx]);
            if (r < diff || diff < l) continue;

            guild[ny][nx] = 1;
            total_val += arr[ny][nx];
            q.push({ny, nx});
            v.push_back({ny, nx});
        }
    }
    if (v.size() == 1) return false;

    int div_val = total_val / (int)v.size();
    for (int i = 0; i < v.size(); i++) {
        arr[v[i].first][v[i].second] = div_val;
    }
    return true;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> l >> r;
    
    for(int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> arr[i][j];


   int cnt = 0;
   while(true) {
       memset(guild, 0x00, sizeof(guild));
       int isMoved = false;
       for (int i = 1; i <= n; i++) {
           for (int j = 1; j <= n; j++) {
               if (guild[i][j] == 0) {
                   if (bfs(i, j)) isMoved = true;   
               }
           }
       }


       if (!isMoved) break;
       cnt++;
   }

   cout << cnt << endl;
    return 0;
}
