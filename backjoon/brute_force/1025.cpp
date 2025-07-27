#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include <cmath>
using namespace std;

int n, m;
char arr[10][10];

bool isInt(int val) {
    int root = (int)sqrt(val);
    return val == root * root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
        }
    }

    int maxVal = -1;
    for (int di = -n; di <= n; di++) {
        for (int dj = -m; dj <= m; dj++) {
            if (di == 0 && dj == 0) continue;

            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    int y = i; int x = j;
                    string str;

                    while (y >= 1 && y <= n && x >= 1 && x <= m) {
                        str += arr[y][x];
                        int val = stoi(str);
                        // cout << val << endl;
                        if (isInt(val)) maxVal = max(maxVal, val);
                        y += di;
                        x += dj;
                    }
                }
            }
        }
    }
    
    cout << maxVal << endl;
    return 0;
}
