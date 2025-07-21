#include <iostream>
#include <climits>
#include <utility>

using namespace std;
int n, m;
int arr[11][11];
int after_50[11][11];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

// arr 보고 after_50에 값 넣는 함수
void after() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 1) {
                int cnt = 0;
                for (int k = 0; k < 4; k++) {
                    int ny = i + dy[k]; int nx = j + dx[k];
                    if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
                        cnt++;
                        continue;
                    }
                    if (arr[ny][nx] == 0) cnt++;
                }

                if (cnt >= 3) after_50[i][j] = 0;
                else after_50[i][j] = 1;
            }
        }
    }
}

// after_50의 젤 작은 y,x랑 젤 큰 y,x 구해서 
// 해당 범위 출력 진행시키는 함수
void print_isLand() {
    pair<int,int> min_idx = {INT_MAX, INT_MAX};
    pair<int,int> max_idx = {INT_MIN, INT_MIN};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // cout << after_50[i][j];
            if (after_50[i][j] == 1) {
                min_idx = {min(i, min_idx.first), min(j, min_idx.second)};
                max_idx = {max(i, max_idx.first), max(j, max_idx.second)};
            }
        }
        // cout << endl;
    }
    // cout << min_idx.first << " " << min_idx.second << " " << max_idx.first << " " << max_idx.second << endl;
    for (int i = min_idx.first; i <= max_idx.first; i++) {
        for (int j = min_idx.second; j <= max_idx.second; j++) {
            cout << ((after_50[i][j] == 1) ? 'X' : '.');
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    string str;
    for (int i = 0; i < n; i++) {
        cin >> str;
        for (int j = 0; j < m; j++) {
            arr[i][j] = (str[j] == '.') ? 0 : 1;
        }
    }
    
    // dy, dx 검사해서 인접 0의 cnt 3 or 4면 침몰 ㅇㅇ
    after();
    print_isLand();

    return 0;
}
