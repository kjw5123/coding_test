 #include <iostream>
 #include <queue>
 #include <climits>
 #include <algorithm>
 #include <utility>
 using namespace std;

 struct robo {
     int y, x, d, t;
 };

 int dy[5] = {0, 0, 0, 1, -1}; 
 int dx[5] = {0, 1, -1, 0, 0};

 int arr[101][101];   
 bool visited[101][101][5]; 
 int n, m;
 int sy, sx, sd, ey, ex, ed;

 int turn_left(int d) {
     if (d == 1) return 4;
     if (d == 2) return 3;
     if (d == 3) return 1;
     if (d == 4) return 2;
     return -1;
 }

 int turn_right(int d) {
     if (d == 1) return 3;
     if (d == 2) return 4;
     if (d == 3) return 2;
     if (d == 4) return 1;
     return -1;
 }

 void bfs() {
     queue<robo> q;
     q.push({sy, sx, sd, 0});
     visited[sy][sx][sd] = true;


     while (!q.empty()) {
         int cy = q.front().y;
         int cx = q.front().x;
         int cd = q.front().d;
         int ct = q.front().t;
         q.pop();

         if (cy == ey && cx == ex && cd == ed) {
             cout << ct << '\n';
             return;
         }

         
         for (int k = 1; k <= 3; k++) {
             int ny = cy + dy[cd] * k;
             int nx = cx + dx[cd] * k;

             if (ny <= 0 || ny > n || nx <= 0 || nx > m) break;
             if (arr[ny][nx] == 1) break;

             if (!visited[ny][nx][cd]) {
                 visited[ny][nx][cd] = true;
                 q.push({ny, nx, cd, ct + 1});
             }
         }

         
         int ld = turn_left(cd);
         if (!visited[cy][cx][ld]) {
             visited[cy][cx][ld] = true;
             q.push({cy, cx, ld, ct + 1});
         }


         int rd = turn_right(cd);
         if (!visited[cy][cx][rd]) {
             visited[cy][cx][rd] = true;
             q.push({cy, cx, rd, ct + 1});
         }
     }
 }

 int main() {
     ios::sync_with_stdio(false);
     cin.tie(NULL);

     cin >> n >> m;
     for (int i = 1; i <= n; i++) {
         for (int j = 1; j <= m; j++) {
             cin >> arr[i][j];
         }
     }

     cin >> sy >> sx >> sd;
     cin >> ey >> ex >> ed;

     bfs();
     return 0;
 }

