#include <iostream>

using namespace std;
int n;
int cnt = 0;
int arr[101][101];
int arr2[101][101];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};


void dfs(int y, int x, int val) {
    arr[y][x] = 'X';
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i]; int nx = x + dx[i];
        if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
        if (arr[ny][nx] != val) continue;
        dfs(ny, nx, val);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    string str;
    for (int i = 1; i <= n; i++) {
        cin >> str;
        for (int j = 1; j <= n; j++) {
            arr[i][j] = arr2[i][j] = str[j-1];
            if (arr2[i][j] == 'G') arr2[i][j] = 'R';
        }
    }

    for(int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if(arr[i][j] != 'X') {
                cnt++;
                dfs(i,j, arr[i][j]); 
            }
        }
    }

    cout << cnt << " ";

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            arr[i][j] = arr2[i][j];
        }
    }
    cnt = 0;

    for(int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if(arr[i][j] != 'X') {
                cnt++;
                dfs(i,j, arr[i][j]); 
            }
        }
    }

    cout << cnt << endl;

    return 0;
}
