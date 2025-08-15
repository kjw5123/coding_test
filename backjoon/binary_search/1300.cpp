#include <iostream>

using namespace std;

long long int n, k;
// 최대 element가 100억개짜리라서 , 배열 바탕으로 풀이할 문제는 절대 아니고 
// 음,,,
//
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    long long low = 1, high = k, res = k;

    while (low <= high) {
        long long mid = (low + high) / 2;
        long long cnt = 0;

        for (long long i = 1; i <= n; i++) {
            cnt += min(n, mid / i);
        }

        if (cnt >= k) {
            res = mid;
            high = mid - 1;

        } else low = mid + 1;
    }
    cout << res << '\n';

    return 0;
}
