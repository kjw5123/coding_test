#include <iostream>

using namespace std;

int arr[1001] = { 0 };
int main() {
    int n ;
    cin >> n;
    int cnt = 0;

    for (int i = 1; i <= 99; i++) {
        arr[i] = 1;
    }

    for (int i = 100; i <= 999; i++) {
        int num1 = i / 100; int num2 = (i - num1 * 100) / 10; int num3 = i % 10;
        if (num1 - num2 == num2 - num3) arr[i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (arr[i] == 1) cnt++;
    }
    cout << cnt << endl;
    return 0;
}
