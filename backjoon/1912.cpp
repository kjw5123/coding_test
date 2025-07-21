#include <iostream>
#include <algorithm>


using namespace std;

int arr[100001] = {0};
int dp[100001] = {0};

int main() {
    int n ;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    
    dp[1]  = arr[1];
    int res = dp[1];

    for (int i = 2; i <= n; i++) {
        dp[i] = max(arr[i], dp[i-1] + arr[i]);
        res = max(res, dp[i]);
    }

    cout << res << endl;

    return 0;
}
