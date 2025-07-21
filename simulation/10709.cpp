#include <iostream>

using namespace std;
int n, m;
int arr[101][101];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char a; cin >> a;
            if (a == 'c') arr[i][j] = 0;
            else arr[i][j] = -1;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            if (arr[i][j] == -1 && arr[i][j-1] != -1) arr[i][j] = arr[i][j-1] + 1;
        }
    }


    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
