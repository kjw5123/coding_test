#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int n;  // 드래곤 커브 개수
int arr[101][101];
int dy[4] = {0, -1, 0, 1};  // 우 상 좌 하
int dx[4] = {1, 0, -1, 0};

void check_squares() {
    int cnt = 0;
    for (int i = 0; i <= 99; i++) {
        for (int j = 0; j <= 99; j++) {
            if (arr[i][j] == 1 && arr[i][j+1] == 1 && arr[i+1][j] == 1 && arr[i+1][j+1] == 1) cnt++;
        }
    }
    cout << cnt << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    int y, x, dir,order;
    for (int i = 0; i < n; i++) {
        cin >> y >> x >> dir >> order;
        arr[y][x] = 1; vector<int> dirs; dirs.push_back(dir);
        for (int j = 0 ; j < order; j++) {
            vector<int> new_dirs;
            for (int k = 0; k < (int)dirs.size(); k++) {
                new_dirs.push_back(((dirs[k] + 1) % 4));
            }
            reverse(new_dirs.begin(), new_dirs.end());

            for (int k = 0; k < (int)dirs.size(); k++) {
                new_dirs.push_back(dirs[k]);
            }
            dirs = new_dirs;
            /*
            cout << "Now dirs: ";
            for (int k = 0; k < (int)dirs.size(); k++) {
                cout << dirs[k] << " ";
            }
            cout << endl << endl;
            */
        }
        reverse(dirs.begin(), dirs.end());

        for (int j = 0; j < (int)dirs.size(); j++) {
            // cout << "Now dir is " << dirs[j] << ", ";
            y += dy[dirs[j]]; x += dx[dirs[j]];
            // cout << "now y is " << y << " " << "now x is " << x << endl;
            arr[y][x] = 1;
        }
        // cout << endl;
    }
    /*
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 10; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */ 
    check_squares();
    return 0;
}
