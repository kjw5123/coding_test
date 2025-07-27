#include <iostream>
#include <cstring>
#include <set>
#include <queue>

using namespace std;
/* [문제]
 * 2차원 배열에 여러 색의 뿌요를 놓고
 * 뿌요는 중력 영향 받아서 아래로 떨어진다
 * 뿌요 놓고 나면, 같은 색 뿌요가 4개 이상 상하좌우로 연결 돼있으면 없어진다
 * 이 때를 1연쇄라 지칭
 *
 * 뿌요 없어진 후, 위에 다른 뿌요 있으면 중력 영향 받아서 아래로 떨어진다 
 *
 * 아래로 떨어진 후 다시 터진다
 * 연쇄 cnt 증가 
 *
 * 터질 수 있는 뿌요가 여러 그룹이 있으면, 동시에 터지며, 동시에 터지니 연쇄는 1 증가한다
 *
 *
 * [입력]
 * 12 x 6 격자에 
 * .는 빈공간
 * R G B P Y 5색 입력된다
 *
 * */
struct puyo {
    int y, x, c; // color
};

int arr[13][7];
bool visited[13][7];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int combo = -1;
bool isCombo = true;

void arr_print() {
    for (int i = 1; i <= 12; i++) {
        for (int j = 1; j <= 6; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void bfs(int y, int x, int c) {
    queue<puyo> q;
    vector<puyo> puyos; // 그냥 pair 써도 되는뎅..

    q.push({y, x, c});
    puyos.push_back({y,x,c});
    visited[y][x] = true;
    
    while(!q.empty()) {
        int cy = q.front().y;
        int cx = q.front().x;
        int cc = q.front().c;
        visited[cy][cx] = true;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i]; int nx = cx + dx[i];
            if ( ny <= 0 || ny > 12 || nx <= 0 || nx > 6 ) continue;
            if (arr[ny][nx] != cc) continue;
            if (visited[ny][nx]) continue;

            visited[ny][nx] = true;
            q.push({ny, nx, cc});
            puyos.push_back({ny, nx, cc});
        }
    }

    if (puyos.size() >= 4) {
        isCombo = true;
        for (int i = 0; i < (int)puyos.size(); i++) {
            arr[puyos[i].y][puyos[i].x] = 0;
        }
    }
}

void arr_check() {
    for (int j = 1; j <= 6; j++) {
        int air = 0; 
        for (int i = 12; i >= 1; i--) {
            if (arr[i][j] == 0) {
                air++;  
            } else if (air > 0) {
                arr[i + air][j] = arr[i][j];
                arr[i][j] = 0;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    char input;
    for (int i = 1; i <= 12; i++) {
        for (int j = 1; j <= 6; j++) {
            cin >> input;
            if (input == '.') arr[i][j] = 0;
            else if (input == 'R') arr[i][j] = 1;
            else if (input == 'G') arr[i][j] = 2;
            else if (input == 'B') arr[i][j] = 3;
            else if (input == 'P') arr[i][j] = 4;
            else arr[i][j] = 5;  // Y
        }
    }
    
    // 어...
    // 아니 bfs 유형 문제로 적혀져 있긴 한데...
    // 시뮬적 관점으로 생각해보자 
    // 12x6 사이즈 판때기라 그냥
    // set<pair<int,int>> 에다가 좌표 싹 넣을까?
    
    // dy dx로 보면서 나랑 같은 애들만 있으면 queue에 추가하면서
    // 나중에 set을 털어버릴까 싶은데
    // visited도 당연히 하고
    //
    // 해서 다 erase 하고 나면 
    // it 써서 arr에다가 다시 값 입력하고?
    
    // 1. 2중 for문으로 전체 범위 탐색
    // 2. 만약에 0이 아니다?
    //    -> bfs 시도 (같은 색 있는지, 없으면 continue) (어디 벡터에 저장)
    //    -> 4개 이상이면 vector에 저장된 값을 set에 삽입하지 않는다 (1 combo 증가)
    //       삭제되는 행, 렬 정보 바탕으로 갱신?
    //
    //    -> 4개 이하면 저장
    // 
    // 3. set 바탕으로 arr 갱신
    // 4. combo 변화 없을 때까지 반복

    while(isCombo) {
        // cout << " ============ trun " << combo << " ============== " << endl; 
        isCombo = false;
        memset(visited, 0x00, sizeof(visited));

        for (int i = 1; i <= 12; i++) {
            for (int j = 1; j <= 6; j++) {
                if (arr[i][j] != 0 && !visited[i][j]) bfs(i , j, arr[i][j]);
            }
        }
        // arr_print();
        arr_check();
        // arr_print();
        combo++;
    }
    cout << combo << endl;
    return 0;
}
