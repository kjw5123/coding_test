#include <iostream>
// 오버플로우가 발생하기 전에 미리미리 잘 정리하자.
using namespace std;

long long int fact(long long int v) {
    if (v == 0) return 1;
    return v * fact(v-1);
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int left, right;
        cin >> left >> right;
        // permutation이넹
        // 아니네 combination이넹
        long long int result = 1;
        for (int j = 1; j <= left; j++) {
            result *= (right - j + 1);
            result /= j;
        }
        cout << result << endl;
    }
    return 0;
}
