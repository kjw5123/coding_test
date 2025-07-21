#include <iostream>

using namespace std;


long long int dp[101] = {0};
int main() {
   dp[1] = 0;
   dp[2] = 1;
   dp[3] = 1;

   for (int i = 4 ; i <= 91; i++) {
       dp[i] = dp[i-1] + dp[i-2];
   }
    int a;
    cin >> a;
    cout << dp[a+1] << endl;


    return 0;
}
