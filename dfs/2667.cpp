#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n;

int arr[26][26];
vector<int> v;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
void check_arr(  ) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
int dfs(int y, int x, int count) {
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i]; int nx = x + dx[i];
        if (ny <= 0 || ny > n || nx <= 0 || nx > n) continue;
        if (arr[ny][nx] == 0) continue;
//        check_arr();
//        cout << endl;
        arr[ny][nx] = 0;
        count++;
        count = dfs(ny, nx, count);
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    string str;
    for (int i = 1; i <= n; i++) {
        cin >> str;
        for (int j = 1; j <= n; j++) {
            arr[i][j] = str[j-1] - 48;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (arr[i][j] == 1) {
                arr[i][j] = 0;
                int val = dfs(i, j, 1);
                v.push_back(val);
            }
        }
    }
    sort(v.begin(), v.end());

    cout << v.size() << '\n';
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << '\n';
    }
    return 0;
}
