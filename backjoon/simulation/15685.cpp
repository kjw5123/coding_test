#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n;
int y, x, dir, gen;                       //   회전 시
int dy[4] = {0, -1, 0, 1}; // 우 상 좌 하 -> 상 좌 하 우
int dx[4] = {1, 0, -1, 0};
int arr[102][102];  // 0 base로 풀이하는게 정배인듯
vector<int> d;
vector<int> d_reverse;
void count_nemo() {
    int cnt = 0;
    for (int i = 0; i <= 99; i++) {
        for (int j = 0; j <= 99; j++) {
            if (arr[i][j] == 1 && arr[i+1][j] == 1 && arr[i][j+1] == 1 && arr[i+1][j+1] == 1) cnt++;
        }
    }
    cout << cnt << endl;
}


void d_init() {
    d_reverse.clear();
    for (int i = (int)d.size() - 1; i >= 0; i--) {
        d_reverse.push_back((d[i] + 1) % 4);
    }
    for (int i = 0; i < (int)d_reverse.size(); i++) {
        d.push_back(d_reverse[i]);
    }
}

// 0 1 2 1 2 3 2 1
// 0 1 2 1 2 3 2 1 2 3 0 3 2 3 2 1
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x >> y >> dir >> gen;
        arr[y][x] = 1;
        y += dy[dir]; x += dx[dir];
        arr[y][x] = 1;
        d.clear();
        d.push_back(dir);

        for (int i = 0; i < gen; i++) {
            d_init();
            for (int i = 0; i < (int)d_reverse.size(); i++) {
                y += dy[d_reverse[i]]; x += dx[d_reverse[i]];
                arr[y][x] = 1;
            }
        }

    }
    
    
    count_nemo(); 
    return 0;
}
