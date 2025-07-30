#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
/* [문제]
 *
 * 상우는 dy dx 이동 한다 (위 아래 왼쪽 오른쪽 순)
 * 
 * 2차원 격자 특정 위치에 세이프 존이 있다 
 * 거기선 상우 오더를 듣지 않는다 
 *
 * 성우가 정한 방향을 분석해서 최소 개수의 세이프 존을 만들자
 *
 * [입력]
 * N, M (1 ~ 1000)
 * 지도 밖으로 나가는 명령은 안주어진다
 * 
 * [출력]
 * 필요한 SAFE ZONE 최소 개수
 *
 * [사견]
 * bfs로 일단 간 지역에 대한 순환 뭉탱이를 구하자 
 * 그리고 그 순환 뭉탱이 중에 하나가 SAFE ZONE이다 == 더이상 순환안한다
 * == 그럼 순한뭉탱이 하나당 SAFE ZONE이 하나만 필요하다
 * 라는 삼단논법이 가능하다 본다 
 * 이대로 ㄲㄲㄲ
 *
 * 생각을 좀 잘못한게 
 * 저렇게 무지성으로 할 게 아니라 
 * visited는 매번 초기화 하고 
 * 가다가 갑자기 다음번에 visited가 나온다? 하면 그 visited를 -1로 
 * 처리하고, 다른 위치에서도 저거 마주치면 이번 회차는 cycle_num 안 높히는 식으로
 * 해야겠는데
 * */
int n, m;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int arr[1001][1001];  // 방향 정보 저장
bool visited[1001][1001];
bool total_visited[1001][1001];
int sf = 0;

void check_arr() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] == 0) cout << "↑";
            else if (arr[i][j] == 1) cout << "→";
            else if (arr[i][j] == 2) cout << "↓";
            else if (arr[i][j] == 3) cout << "←";
            else cout << "S";
        }
        cout << endl;
    }
    cout << endl;
}

bool dfs(int y, int x) {
    visited[y][x] = true;
    total_visited[y][x] = true;

    int d = arr[y][x];
    int ny = y + dy[d]; int nx = x + dx[d];
    // 어짜피 ny, nx 밖으로 안벗어난다
    
    bool cycle = false;

    if (!total_visited[ny][nx]) {
        cycle = dfs(ny, nx);
    } else if (visited[ny][nx]) {
        cycle = true;
    }

    visited[y][x] = false;
    return cycle;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    char val;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> val;
            if (val == 'U') arr[i][j] = 0;
            else if (val == 'D') arr[i][j] = 2;
            else if (val == 'L') arr[i][j] = 3;
            else if (val == 'R') arr[i][j] = 1;
        }
    }
    // check_arr();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if(!total_visited[i][j]) {
                if(dfs(i,j)) sf++;
            }
        }
    }
    
    // check_arr();
    cout << sf << endl;    
    return 0;
}
