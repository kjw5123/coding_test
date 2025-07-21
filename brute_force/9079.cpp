#include <iostream>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int arr[3][3];
// 시도 가능한 뒤집기는 총 8가지 아닌가? 가로 3개 세로 3개 대각선 2개
int flip [8][3][3];
int real_flip[3][3];
bool visited[8];

void visited_init() {
    memset(visited, 0x00, sizeof(visited));
}

void real_flip_init() {
    memset(real_flip, 0x00, sizeof(real_flip));
}


void ff(int idx) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (flip[idx][i][j] == 1) real_flip[i][j] = real_flip[i][j] ^ 1;
        }
    }
}

void apply() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (real_flip[i][j] == 1) arr[i][j] = arr[i][j] ^ 1;
        }
    }
}

bool check_arr() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(arr[i][j] != arr[0][0]) return false;
        }
    }
    return true;
}

int dfs(int idx, int depth) {
    if (depth == 8) {
        return INT_MAX;
    }
    if (check_arr()) {
        return depth;
    }
    int cnt = INT_MAX;
    for (int i = 0; i < 8; i++) {
        if (!visited[i])  {
            visited[i] = true;
            ff(i);
            apply();
            cnt = min(cnt, dfs(i, depth+1));
            apply();
            ff(i);
            visited[i] = false;
        }
    }
    return cnt;
}

int main() {
    flip [0][0][0] = 1; flip[0][0][1] = 0; flip[0][0][2] = 0;
    flip [0][1][0] = 1; flip[0][1][1] = 0; flip[0][1][2] = 0;
    flip [0][2][0] = 1; flip[0][2][1] = 0; flip[0][2][2] = 0;

    flip [1][0][0] = 0; flip[1][0][1] = 1; flip[1][0][2] = 0;
    flip [1][1][0] = 0; flip[1][1][1] = 1; flip[1][1][2] = 0;
    flip [1][2][0] = 0; flip[1][2][1] = 1; flip[1][2][2] = 0;

    flip [2][0][0] = 0; flip[2][0][1] = 0; flip[2][0][2] = 1;
    flip [2][1][0] = 0; flip[2][1][1] = 0; flip[2][1][2] = 1;
    flip [2][2][0] = 0; flip[2][2][1] = 0; flip[2][2][2] = 1;

    flip [3][0][0] = 1; flip[3][0][1] = 1; flip[3][0][2] = 1;
    flip [3][1][0] = 0; flip[3][1][1] = 0; flip[3][1][2] = 0;
    flip [3][2][0] = 0; flip[3][2][1] = 0; flip[3][2][2] = 0;

    flip [4][0][0] = 0; flip[4][0][1] = 0; flip[4][0][2] = 0;
    flip [4][1][0] = 1; flip[4][1][1] = 1; flip[4][1][2] = 1;
    flip [4][2][0] = 0; flip[4][2][1] = 0; flip[4][2][2] = 0;

    flip [5][0][0] = 0; flip[5][0][1] = 0; flip[5][0][2] = 0;
    flip [5][1][0] = 0; flip[5][1][1] = 0; flip[5][1][2] = 0;
    flip [5][2][0] = 1; flip[5][2][1] = 1; flip[5][2][2] = 1;

    flip [6][0][0] = 0; flip[6][0][1] = 0; flip[6][0][2] = 1;
    flip [6][1][0] = 0; flip[6][1][1] = 1; flip[6][1][2] = 0;
    flip [6][2][0] = 1; flip[6][2][1] = 0; flip[6][2][2] = 0;

    flip [7][0][0] = 1; flip[7][0][1] = 0; flip[7][0][2] = 0;
    flip [7][1][0] = 0; flip[7][1][1] = 1; flip[7][1][2] = 0;
    flip [7][2][0] = 0; flip[7][2][1] = 0; flip[7][2][2] = 1;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        visited_init();
        real_flip_init();
        int cnt = 0;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                char val;
                cin >> val;

                if (val == 'H') arr[j][k] = 1;
                else arr[j][k] = 0;  // tail아!! 진화시켜줘!
            }
        }
        
        cnt = dfs(-1, 0);
        if (cnt == INT_MAX) cout << -1 << endl;
        else cout << cnt << endl;
    }
    
    
        
    return 0;
}
