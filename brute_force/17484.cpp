#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int arr [7][7];
int n , m;

int dy[3] = {1,  1, 1};
int dx[3] = {-1, 0, 1};

int unlucky_dfs(int y, int x, int dir) {
    int val = arr[y][x];
    if (y == n) {
        return val;
    }
    int minVal = INT_MAX;
    for (int i = 0; i < 3; i++) {
        if (dir == i) continue;
        int ny = y + dy[i]; int nx = x + dx[i];
        if (nx <= 0 || nx > m) continue;
        minVal = min(minVal , unlucky_dfs(ny, nx, i));
    }
    return val + minVal;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
        }
    }
    int minVal = INT_MAX;
    for (int j = 1; j <= m; j++) {
        minVal = min(minVal, unlucky_dfs(1, j, -1));
    }
    cout << minVal << endl;
    return 0;
}
