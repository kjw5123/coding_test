#include <iostream>

using namespace std;
int n, num;
int arr[1000][1000];
int dir = 0;
int dy[4] = {1, 0, -1, 0};
int dx[4] = {0, 1, 0, -1};

int main() {
    cin >> n >> num;
    // 0 base 할거면 걍 /2, 1base면 1더하기인데 뭘로하지

    // 1 → N^2가 아니라 N^2 → 1로 생각하는게 더 맘 편할듯
    // 하 우 상 좌 
    // 어레이 경계거나, 이미 값이 있으면 회전시키기 (dy dx 0 1 2 3 에서 idx만 갈아치우기)
    //
    int val = n * n;
    int y = 1;
    int x = 1;
    int res_y, res_x;
    while(val != 0) {
        if (val == num) {
            res_y = y; res_x = x;
        }
        arr[y][x] = val;        
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (ny <= 0 || ny > n || nx <= 0 || nx > n) {
            dir = (dir + 1) % 4;

        } else if (arr[ny][nx] != 0) {
            dir = (dir + 1) % 4;
        }
        y = y + dy[dir]; x = x + dx[dir];
        val--;
    }

    


    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << res_y << " " << res_x << endl;
    return 0;
}
