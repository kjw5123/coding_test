#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
int t;
int arr[501][501];
int temp[501][501];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t;
    int n, deg;
    for (int tc = 0; tc < t; tc++) {
        memset(arr, 0x00, sizeof(arr));
        memset(temp, 0x00, sizeof(temp));

        cin >> n >> deg;
        int mid = n / 2 + 1 ;
        if (deg < 0) deg += 360;
        int rot_time = (deg / 45) % 8;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> arr[i][j];
            }
        }
        for (int k = 0; k < rot_time; k++) {
            memcpy(temp, arr, sizeof(arr));
            for (int i = 1; i <= n; i++) {
                arr[i][mid] = temp[i][i];

                arr[i][i] = temp[mid][i];

                arr[mid][i] = temp[n - i + 1][i];

                arr[n - i + 1][i] = temp[n - i + 1][mid];

                arr[n - i + 1][mid] = temp[n - i + 1][n - i + 1];

                arr[n - i + 1][n - i + 1] = temp[mid][n - i + 1];

                arr[mid][n - i + 1] = temp[i][n - i + 1];

                arr[i][n - i + 1] = temp[i][mid];
            }
            
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cout << arr[i][j] << " ";
            }
            cout << '\n';
        }
    }
    
    
    
    return 0;
}
