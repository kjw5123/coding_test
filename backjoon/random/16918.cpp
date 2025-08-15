#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

/* [문제]
 * 폭탄은 3초 뒤 폭발, 폭탄 있던 칸과
 * 인접 4칸 전부 빈칸 된다
 * 폭탄 폭발시,ㅡ 인접 칸 폭탄도 소멸해서 연쇄 반응 없다
 * 봄버맨은 폭탄 맞아도 안죽는다
 *
 * 처음에 봄버맨은 일부칸에 폭탄 설치
 * 다음 1초 동안 봄버맨은 아무것도 안한다
 * 다음 1초동안 폭탄 설치안된 모든칸에 설치된다
 * 1초가 지난후에 모두 폭발한다
 *
 *
 * */
int n, m, t;
int arr[201][201];
int times[201][201];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void print_arr() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << ((arr[i][j] == 1) ? 'O' : '.');
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> t;
    char c;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> c;
            arr[i][j] = (c == 'O') ? 1 : 0;
            times[i][j] = (arr[i][j] == 1) ? 1 : 0;
        }
    }

    int cnt = 1;
    while (cnt++ != t) {
        vector<pair<int,int> > v;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (arr[i][j] == 0) {
                    arr[i][j] = 1;
                    times[i][j] = 0;

                } else {
                    times[i][j]++;
                    if (times[i][j] == 3) {
                        v.push_back({i, j});
                        for (int k = 0; k < 4; k++) {
                            int ny = i + dy[k]; int nx = j + dx[k];
                            if (ny <= 0 || ny > n || nx <= 0 || nx > m) continue;
                            v.push_back({ny, nx});
                        }
                    }
                }
            }
        }

        for (int i = 0; i < (int)v.size(); i++) {
            int y = v[i].first; int x = v[i].second;
            arr[y][x] = 0; times[y][x] = 0;
        }
    }
    print_arr();
    return 0;
}
