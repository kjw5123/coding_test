#include <iostream>
using namespace std;

int arr[1001];
int dp[1001];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        dp[i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = max(result, dp[i]);
    }

    cout << result << '\n';
    return 0;
}

