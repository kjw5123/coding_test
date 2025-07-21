#include <iostream>

using namespace std;



/* 2xN
 * 1  |                                                                       1
 * 2  || = ㅁ                                                                 2   1
 * 3  ||| =| ㅁ|                                                              5   3
 * 4  |||| =|| == ㅁ|| ㅁㅁ =ㅁ                                               11  6 
 * 5 ||||| =||| ==| ㅁ||| ㅁㅁ| =ㅁ|                                          21  10
 *   |||||| =|||| ==|| === ㅁ|||| ㅁㅁ|| ㅁㅁㅁ   ㅁㅁ= ㅁ==    =ㅁ||         43  22
 * 7                                                                   
 *
 *
 *
 * 
*/
int dp[1001]= {0};
int main() {
    int n ;
    cin >> n;

    dp[1] = 1;
    dp[2] = 3;
    for (int i = 3; i <= n; i++) {
        dp[i] = (dp[i-1] + 2 * dp[i-2]) % 10007;
    }

    cout << dp[n] << endl;




    return 0;
}
