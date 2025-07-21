#include <iostream>

using namespace std;

/* 1: |                         1개
 * 2: || =                      2개
 * 3: ||| =|                    3개
 * 4: |||| =|| ==               5개
 * 5: ||||| =||| ==|            8개
 * 6: |||||| =|||| ==|| ===     13개
 * 7: ||||||| =||||| ==||| ===| 21개
 * */
int arr[1001];
int main() {
    int n;
    cin >> n;

    arr[1] = 1;
    arr[2] = 2;
    for (int i = 3; i <= 1000; i++) {
        arr[i] = (arr[i-1] + arr[i-2]) % 10007;
    }
    cout << arr[n] << endl;
    return 0;
}
