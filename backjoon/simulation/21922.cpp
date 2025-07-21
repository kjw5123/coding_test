#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;
// 종이 안들고왔네 맙소사
// 1. 에어컨 바람은 자기가 위치한 곳 + 상하좌우 5방향에 바람 붐
// 난 에어컨 바람 지나가는 경로에 앉고 싶다
//
// 근데 다양한 물건들이 바람 방향을 바꿔버린다 . . .
// 물건 종류는 4가지 
//
// | 반사 함
// - 반사함
// / 반사함
// \ 반사함 
//
// 민상이 아무데나 앉을 수 있다
// 물건 있는 자리든 에어컨 바로 밑이든
//
// 입력이 2001 2001임
// 1 2 3 4가 물건 번호 
// 9는 에어컨
// 0은 empty space 

// dy dx 쓸거임
// while문으로 쭉 할거고
// dir 인자 넣어서 유연하게 바뀌게끔 할거임 
// 뭐 수식이야 짱구굴리면 나올 것 같음
//
int n, m;
int arr[2001][2001];
int wind[2001][2001];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
// 난 항상 상우하좌로 표현한다
// 물건 1 | 1 ← → 3 만
// 물건 2 - 0 ← → 2 만
// 물건 3 / 0 -> 1, 1 -> 0, 2 -> 3, 3 -> 2
// 물건 4 \ 0 -> 3, 3 -> 0, 1 -> 2, 2 -> 1

void check_wind() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if(wind[i][j] == 1) cnt++;
        }
    }
    cout << cnt << endl;
}


int dir_change(int val, int dir) {
    switch(val){
        case 1:
            if (dir % 2 == 1) return (dir + 2) % 4;
            else return dir;
            break;

        case 2:
            if (dir % 2 == 0) return (dir + 2) % 4;
            else return dir;
            break;

        case 3:
            if (dir % 2 == 0) return (dir + 1);
            else return (dir - 1);
            break;

        case 4:
            if (dir % 2 == 1) return (dir + 1) % 4;
            else return (dir + 3) % 4;
            break;
    }
    return 0;
}

queue<pair<int , int> > aircon;
void check_wind_arr() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << wind[i][j] << " ";
        }
        cout << endl;
    }
}

void send_wind(int y, int x, int dir) {
    int cnt = 0;
    while(true) {
        y += dy[dir]; x += dx[dir];
        if (y <= 0 || y > n || x <= 0 || x > m) break;
        if (arr[y][x] == 9) break;
        wind[y][x] = 1;
        if (arr[y][x] != 0) dir = dir_change(arr[y][x], dir);
        cnt++;
        // if (cnt <= 10) check_wind_arr();
    }
}

void aircon_on() {
    while(!aircon.empty()) {
        int cur_y = aircon.front().first;
        int cur_x = aircon.front().second;
        aircon.pop();
        wind[cur_y][cur_x] = 1;

        for (int dir = 0; dir < 4; dir++) {
            send_wind(cur_y, cur_x, dir);
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
            if (arr[i][j] == 9) aircon.push({i, j});
        }
    }
    
    aircon_on();
    check_wind();
    return 0;
}
