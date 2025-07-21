#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int m,n,k;
int arr[101][101];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
vector<int> v;
int dfs(int y, int x) {
    int cnt = 1;
    arr[y][x] = 1;
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i]; int nx = x + dx[i];
        if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
        if (arr[ny][nx] == 1) continue;
        arr[ny][nx] = 1;
        cnt += dfs(ny, nx);
    }  
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;

    int x1,y1,x2,y2;
    for (int i = 0; i < k; i++) {
        cin >> x1 >> y1 >> x2 >> y2;

        for (int p = y1; p < y2; p++) {
            for (int q = x1; q < x2; q++) {
                arr[p][q] = 1;
            }
        }
    }
/*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
*/
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 0) {
                int val = dfs(i,j);
                v.push_back(val);    
            }
        }
    }
    sort(v.begin(), v.end());
    cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    return 0;
}
