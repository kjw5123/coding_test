#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int n;
int arr[11][11];
bool visited[11][11];

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

bool canPlant(int y, int x) {
    if (y <= 0 || y > n || x <= 0 || x > n) return false;
    if (visited[y][x]) return false;
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i]; int nx = x + dx[i];
        if (ny <= 0 || ny > n || nx <= 0 || nx > n) return false;
        if (visited[ny][nx]) return false;
    }
    return true;
}


int visit_check(int y, int x) {
    int result = 0;
    visited[y][x] = true;
    result += arr[y][x];

    for (int i = 0; i < 4; i++) {
        visited[y + dy[i]][x + dx[i]] = true;
        result += arr[y + dy[i]][x + dx[i]];
    }
    return result;
}


void visited_restore(int y, int x) {
    visited[y][x] = false;

    for (int i = 0; i < 4; i++) {
        visited[y+dy[i]][x+dx[i]] = false;
    }
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }
    
    long long int minVal = INT_MAX;   
    // 상당히 멍청해 보이네...
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            long long int val1 = 0;
            if (canPlant(i, j)) val1 = visit_check(i,j);
            else continue;

            for (int ii = 1; ii <= n; ii++) {
                for (int jj = 1; jj <= n; jj++) {
                    long long int val2 = 0;
                    if (canPlant(ii,jj)) val2 = visit_check(ii,jj);
                    else continue;

                    for (int iii = 1; iii <= n; iii++) {
                        for (int jjj = 1; jjj <= n; jjj++) {
                            long long int val3 = INT_MAX;
                            if (canPlant(iii,jjj)) val3 = visit_check(iii, jjj);
                            else continue;
                            minVal = min(minVal, val1 + val2 + val3);
                            visited_restore(iii,jjj);
                       }
                    }

                    visited_restore(ii,jj);
                }
            }
            visited_restore(i,j);

        }
    }

    cout << minVal << endl;
    return 0;
}
