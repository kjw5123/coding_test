#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
int n, m, t;
int arr[51][51];
int next_arr[51][51];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int upper;
int downer;

void dustBoom() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] > 0) {
                int minus_cnt = 0;
                for (int k = 0; k < 4; k++) {
                    int ny = i + dy[k]; int nx = j + dx[k];
                    if (ny <= 0 || ny > n || nx <= 0 || nx > m) continue;
                    if (arr[ny][nx] == -1) continue;
                    next_arr[ny][nx] += arr[i][j] / 5;
                    minus_cnt++;
                }
                next_arr[i][j] += arr[i][j] - arr[i][j]/5 * minus_cnt;
            }
        }
    }
}

void windBlow() {

    for (int i = upper - 1; i > 1; i--) arr[i][1] = arr[i - 1][1];
    arr[1][1] = arr[1][2]; 

    for (int j = 1; j <  m; j++) arr[1][j] = arr[1][j + 1];

    for (int i = 1; i <  upper; i++) arr[i][m] = arr[i + 1][m];

    for (int j = m; j > 2; j--) arr[upper][j] = arr[upper][j - 1];
    arr[upper][2] = 0;                   

    for (int i = downer + 1; i <  n; i++) arr[i][1] = arr[i + 1][1];
    arr[n][1] = arr[n][2];

    for (int j = 1; j <  m; j++) arr[n][j] = arr[n][j + 1];

    for (int i = n; i > downer; i--) arr[i][m] = arr[i - 1][m];

    for (int j = m; j > 2; j--) arr[downer][j] = arr[downer][j - 1];
    arr[downer][2] = 0;
}

int check_arr() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] != -1) cnt += arr[i][j];
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> t;
    bool isDone = false;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == -1 && !isDone) {
                upper = i;
                downer = i + 1;    
                isDone = true;
            }
        }
    }
    
    while(t > 0) {
        memset(next_arr, 0x00, sizeof(next_arr));
        next_arr[upper][1] = -1;
        next_arr[downer][1] = -1;
        dustBoom();
        memcpy(arr, next_arr, sizeof(arr));
        windBlow();
        t--;
    }

    cout << check_arr() << endl;
    return 0;
}
