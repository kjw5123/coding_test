 #include <iostream>
 #include <algorithm>
 #include <vector>
 #include <utility>
 #include <cstdlib>
 using namespace std;

 // 재탕 문제
 struct piece {
     int y;
     int x;
     int dir;
 };
 int n, k;
 int arr[13][13];  // 그냥 판 정보만 기입할거다 (흰,빨,파)
 int turn = 1;
 vector<int> v[13][13];  // 말 인덱스 정보는 여기서 관리하자
 piece mal[11]; // v를 전체 탐색하는 건 바보 같은 짓이니 여기서 좌표 관리 하자
 int dy[5] = {0,0,0,-1,1};
 int dx[5] = {0,1,-1,0,0};  // 우 좌 상 하

 int change_dir(int dir) {
     switch(dir){
         case 1:
             return 2;
         case 2:
             return 1;
         case 3:
             return 4;
         case 4:
             return 3;
     }
     return -1;
 }

 void move(int idx) {
     // cout << turn << endl;
     // if (v[mal[idx].y][mal[idx].x].front() != idx) return;
    int cy = mal[idx].y;
    int cx = mal[idx].x;
    int dir = mal[idx].dir;
    int ny = cy + dy[dir];
    int nx = cx + dx[dir];

    if(ny <= 0 || ny > n || nx <= 0 || nx > n || arr[ny][nx] == 2){
        mal[idx].dir = dir = change_dir(dir);
        ny = cy + dy[dir];
        nx = cx + dx[dir];
        if(ny <= 0 || ny > n || nx <= 0 || nx > n || arr[ny][nx] == 2) return;
    }

    int pos = 0;
    while(pos < (int)v[cy][cx].size() && v[cy][cx][pos] != idx) pos++;

    vector<int> tmp;
    for(int i = pos; i < (int)v[cy][cx].size(); i++) {
        tmp.push_back(v[cy][cx][i]);
    }

    v[cy][cx].resize(pos);

    if(arr[ny][nx] == 1) reverse(tmp.begin(), tmp.end());

    for(int i = 0; i<(int)tmp.size(); i++) {
        int t = tmp[i];
        mal[t].y = ny;
        mal[t].x = nx;
        v[ny][nx].push_back(t);
    }

    if((int)v[ny][nx].size()>=4){
        cout << turn << endl;
        exit(0);
    }
 }

 int main() {
     ios::sync_with_stdio(false);
     cin.tie(NULL);

     cin >> n >> k;

     for (int i = 1; i <= n; i++) {
         for (int j = 1; j <= n; j++) {
             cin >> arr[i][j];
         }
     }

     for (int i = 1; i <= k; i++) {
         int y, x, d; cin >> y >> x >> d;
         mal[i] = {y, x, d};
         v[y][x].push_back(i);
     }

     while(turn <= 1000) {
         for(int i = 1; i <= k; i++) {
            move(i);
         }

         turn++;
     }
     cout << -1 << endl;
     return 0;
 }
