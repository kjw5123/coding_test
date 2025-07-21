#include <iostream>

using namespace std;
int n, m;
int arr[501][501];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    int h;
    for (int i = 1; i <= m; i++) {
        cin >> h;
        for (int j = n; j > n - h; j--) {
            arr[j][i] = 1;
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    // cout << endl;
    */
    int result = 0;
    for (int i = 1; i <= n; i++) {
        int left = 0;
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] == 1) {
                if (left == 0) left = j;
                else {
                    result += j - left - 1;
                    left = j; 
                }
            }
        }
    }
    cout << result << endl;
    return 0;
}
