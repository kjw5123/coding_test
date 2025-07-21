#include <iostream>

using namespace std;
int arr[15];
int main() {
    int a, b;
    cin >> a;
    b = a;

    for (int i = 1; i <= 14; i++) {
        cin >> arr[i];
    }
    int rising = 0, falling = 0;
    int a_cnt = 0, b_cnt = 0;

    a_cnt += a / arr[1];
    a %= arr[1];
    for (int i = 2; i <= 14; i++) {
        if (arr[i] > arr[i-1]) {
            rising++;
            falling = 0;
        } else if (arr[i] == arr[i-1]) {
            rising = 0;
            falling = 0;
        } else if (arr[i] < arr[i-1]) {
            falling++;
            rising = 0;
        }

        if (rising >= 3) {
            b += b_cnt * arr[i];
            b_cnt = 0;
        } else if (falling >= 3) {
            b_cnt += b / arr[i];
            b %= arr[i];
        }

        a_cnt += a / arr[i];
        a %= arr[i];
    }
    // cout << a + a_cnt * arr[14] << " " << b + b_cnt * arr[14] << endl;
    if (a + a_cnt * arr[14] > b + b_cnt * arr[14]) cout << "BNP" << endl;
    else if (a + a_cnt * arr[14] == b + b_cnt * arr[14]) cout << "SAMESAME" << endl;
    else cout << "TIMING" << endl;

    return 0;
}
