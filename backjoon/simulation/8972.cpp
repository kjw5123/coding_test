#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set> // 이거는 어떻게 생각하지?
#include <cstdlib>
#include <climits>
#include <cstring>

using namespace std;

int n , m;
int turn = 0;
string str;
int arr[101][101];
int dy[10] = {0, 1, 1, 1, 0, 0, 0, -1, -1, -1};
int dx[10] = {0, -1, 0, 1, -1, 0, 1, -1, 0, 1};
// 1 ~ 9만 유효한 입력

// 1. I의 좌표에 있는 아두이노가 이동
// 
// 2. I가 R 칸에 이동 시 게임 종료, 종수 패배
//
// 3. R은 dir[5] 빼고 8방위 이동 가능
//    I랑 가까워지는 방향으로 이동 진행
//
// 4. R이 종수 있는 칸으로 도달할 시 게임 종료, 종수 패배
//
// 5. 2개 혹은 그 이상의 R이 같은 칸에 위치하게 되면 R들 소멸 (-1,-1)로 처리하자

// 어짜피 pair<int, int> 좌표로 풀 것인데
// set 쓰면 set.count() 써서 true면 erase로 폭발 시키는 식으로 처리 가능하다...
// 그 외에는 iterator로 접근 해야하는데 
// 고민이네 이건 ㄹㅇ

pair<int ,int> I;
set<pair<int, int> > R;

void lose(int turn) {
    cout << "kraj " << turn << '\n';
    exit(0);
}

void R_move() {
    set<pair<int, int> > new_R;
    vector<pair<int, int> > to_erase;
    for (set<pair<int,int>>::iterator it = R.begin(); it != R.end(); it++) {
        int minDist = INT_MAX;
        int minIdx = -1;
        for (int i = 1; i <= 9; i++) {
            if (i == 5) continue;  // 혹시 모르니 제자리 대기는 skip
            pair<int, int> p = *it;
            int y = p.first; int x = p.second;
            int ny = y + dy[i]; int nx = x + dx[i];
            if (ny <= 0 || ny > n || nx <= 0 || nx > m) continue;
            int diff = abs(I.first - ny) + abs(I.second - nx);
            if (diff < minDist) {
                minDist = diff;
                minIdx = i;
            }
        }
        int new_y = it->first + dy[minIdx];
        int new_x = it->second + dx[minIdx];

        if (new_y == I.first && new_x == I.second) lose(turn);
        if(new_R.count({new_y, new_x}) == false) new_R.insert({new_y, new_x});
        else to_erase.push_back({new_y, new_x});
    }
    for (int i = 0; i < (int)to_erase.size(); i++) new_R.erase(to_erase[i]);
    R = new_R;
}

void print_arr() {
    memset(arr, 0x00, sizeof(arr));
    arr[I.first][I.second] = 1;
    for (set<pair<int, int>>::iterator it = R.begin(); it != R.end(); it++) {
        arr[it->first][it->second] = 2;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] == 0) cout << '.';
            else if (arr[i][j] == 1) cout << 'I';
            else cout << 'R';
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> str;
        for (int j = 1; j <= m; j++) {
            arr[i][j] = str[j-1];
            if(arr[i][j] == 'I') I = {i, j};
            else if (arr[i][j] == 'R') R.insert({i, j});
        }
    }
    
    cin >> str;
    for (int i = 0; i < (int)str.length(); i++) {
        int order = str[i] - 48;

        // 1, 2. I 이동 및 set.count 진행
        I.first += dy[order]; I.second += dx[order];
        turn++;
        if (R.count(I)) lose(turn);

        // 3, 4, 5. R 이동 진행 및 set.count 진행 
        R_move();
        if (R.count(I)) lose(turn);
    }
    print_arr();
    
    return 0;
}
