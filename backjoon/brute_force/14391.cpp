#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

/* [문제]
 * 
 * 숫자 씌인 직사각형 종이가 있다 
 * 각 칸에 정수 있음
 * 직사각형을 안곂치는 조각으로 자르고자 한다 
 *
 * 적당히 조각내서 그 합이 최댓값을 가지게 해보자
 *
 * [사견]
 * 가능한 최대 자릿 수 부터 찾는다거나?
 * 하는 식으로 진행해야 할 것 같은데..
 *
 * 아니 무조건 최대 자릿수로 덧셈 진행하는게 베스트 아닌가?
 * 라고 하기엔!
 *
 * 0 0 0 0
 * 0 0 0 0
 * 0 0 0 0
 * 0 0 1 0
 * 이거 10으로, 2칸 짤랐을 때 제일 크다 . . .
 * 흐음 
 *        str_d[1]   str_d[2]  str_d[3]   str_d[4]
 * str[1]    1          2         3           4
 * str[2]
 * str[3]
 * str[4]
 * 아오 여기선 1base로 적었는데 실제론 0 base로 할거다
 * */
int n, m;
int arr[5][5];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    char val;
    for (int i = 0; i < n; i++) {
        for (int j = 0;j < m; j++) {
            cin >> val;
            arr[i][j] = val - 48;
        }
    }
    
    int result = 0;
    for (int mask = 0; mask < (1 << (n * m)); mask++) {
        int sum = 0;

        for (int i = 0; i < n; i++) {
            int c = 0;
            for (int j = 0; j < m; j++) {
                int pos = i * m + j;
                if (mask & (1 << pos)) {
                    c = c * 10 + arr[i][j];
                } else {
                    sum += c;
                    c = 0;
                }
            }
            sum += c;
        }

        for (int j = 0; j < m; j++) {
            int c = 0;
            for (int i = 0; i < n; i++) {
                int pos = i * m + j;
                if (!(mask & (1 << pos))) {
                    c = c * 10 + arr[i][j];
                } else {
                    sum += c;
                    c = 0;  // 중간에 짤렸으니 초기화
                }
            }
            sum += c;
        }

        result = max(result, sum);
    }
    cout << result << endl;
    return 0;
}
