#include <iostream>
#include <cmath>

using namespace std;

long long int tc, x, y;


/*
 * 거리차
 * 1 : 1                    1
 * 2 : 1 1                  2
 * 3 : 1 1 1                3
 * 4 : 1 2 1                3
 * 5 : 1 2 1 1
 * 6 : 1 2 2 1
 * 7 : 1 2 2 1 1            
 * 8 : 1 2 2 2 1           
 * 9 : 1 2 3 2 1        
 * 10: 1 2 3 2 1 1
 * 11: 1 2 3 2 2 1
 * 12: 1 2 3 3 2 1
 * 13: 1 2 3 3 2 1 1
 * 14: 1 2 3 3 2 2 1
 * 15: 1 2 3 3 3 2 1
 * 16: 1 2 3 4 3 2 1
 * 17: 1 2 3 4 3 2 1 1
 * 18: 1 2 3 4 3 2 2 1
 * 19: 1 2 3 4 3 3 2 1
 * 20: 1 2 3 4 4 3 2 1
 * 21: 1 2 3 4 4 3 2 1 1
 * 22: 1 2 3 4 4 3 2 2 1
 * 23: 1 2 3 4 4 3 3 2 1
 * 24: 1 2 3 4 4 4 3 2 1
 * 25: 1 2 3 4 5 4 3 2 1
 * 26: 1 2 3 4 5 4 3 2 1 1
 * */

// 제곱이거나, 제곱 + sqrt(제곱)일 때 증가
bool isZegob(int num) {
    int val = (int)sqrt(num);
    return num == val * val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tc;

    for (int t = 0; t < tc; t++) {
        cin >> x >> y;

        int diff = y - x;
        int n = (int)sqrt(diff);

        if (n * n == diff) {
            cout << 2 * n - 1 << '\n';

        } else if (diff <= n * n + n) {
            cout << 2 * n << '\n';
            
        } else {
            cout << 2 * n + 1 << '\n';
        }
    }
    
    
    return 0;
}
