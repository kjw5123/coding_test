#include <iostream>
#include <cstring>

using namespace std;

/* [문제]
 *
 * NxN 인도가 있다
 * 각 칸에 보도블럭의 높이가 있다 
 * 제대로 공사 안해 높이가 서로 다르고, 이는 위험하기에 경사로를 설치하고자 한다
 * 경사로 높이는 1, 길이는 L이고, 문제마다 다르다 
 *
 * [설치 가능 조건]
 * 높이가 1차이가 나는 보도블럭에 설치 가능, 낮은 칸에 설치된다
 * 경사로를 지탱하는 바닥은 서로 높이가 같아야 한다
 *
 * 이미 놓은 곳에 또 놓거나,
 * 높이 차이가 1 초과거나,
 * 지탱하는 부분이 부족하는 등, 그럴 순 없다
 *
 * 그리고 각 열과 행의 경사로는 상호 영향을 주지 않는다
 *
 * */

int n, l;
int arr[101][101];
bool visited[101][101];

void visited_check() {
    for (int i = 1; i<= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << visited[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> l;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }

    int cnt = 0;
    // 세로부터
    for (int j = 1; j <= n; j++) {
        bool isOkay = true;
        int now_height = arr[1][j];

        for (int i = 2; i <= n; i++) {
            if (arr[i][j] != now_height) {  // 사건 발생

                if (arr[i][j] > now_height) {  // 올라가야 할 때 
                    if (arr[i][j] - now_height > 1) { isOkay = false; break; }  // 차이 1 초과하는지 체크

                    for (int k = i - 1; k >= i - l; k--) {  
                        if (k < 1) { isOkay = false; break; }  // 배열 범위 넘어가는지 체크 

                        if (arr[k][j] != now_height) { isOkay = false; break; } // 높이 서로 균일한지 체크

                        if (visited[k][j]) { isOkay = false; break; }
                    }

                    if (!isOkay) break; // 더 볼 가치 없으니 종료 
                    now_height = arr[i][j];
                    for (int k = i - 1; k >= i - l; k--) visited[k][j] = true;
                    // visited_check();

                } else {  // 내려가야할 때
                    if (now_height - arr[i][j] > 1) { isOkay = false; break; }

                    for (int k = i; k <= i + l - 1; k++) {
                        if (k > n) { isOkay = false; break; }

                        if (arr[k][j] != arr[i][j]) { isOkay = false; break; }

                        if (visited[k][j]) { isOkay = false; break; }
                    }

                    if (!isOkay) break;
                    now_height = arr[i][j];
                    for (int k = i; k <= i + l - 1; k++) visited[k][j] = true;
                    // visited_check();
                }
            }
        }

        if (isOkay) { cnt++; }
    }
    
    memset(visited, 0x00, sizeof(visited));

    for (int i = 1; i <= n; i++) {
         bool isOkay = true;
         int now_height = arr[i][1];

         for (int j = 2; j <= n; j++) {
             if (arr[i][j] != now_height) {  // 사건 발생
                 if (arr[i][j] > now_height) {  // 올라가야 할 때
                     if (arr[i][j] - now_height > 1) { isOkay = false; break; }  // 차이 1 초과하는지 체크

                     for (int k = j - 1; k >= j - l; k--) {
                         if (k < 1) { isOkay = false; break; }  // 배열 범위 넘어가는지 체크

                         if (arr[i][k] != now_height) { isOkay = false; break; } // 높이 서로 균일한지 체크

                         if (visited[i][k]) { isOkay = false; break; }
                     }

                     if (!isOkay) break; // 더 볼 가치 없으니 종료
                     now_height = arr[i][j];
                     for (int k = j - 1; k >= j - l; k--) visited[i][k] = true;
                     // visited_check();

                 } else {  // 내려가야할 때
                     if (now_height - arr[i][j] > 1) { isOkay = false; break; }

                     for (int k = j; k <= j + l - 1; k++) {
                         if (k > n) { isOkay = false; break; }

                         if (arr[i][k] != arr[i][j]) { isOkay = false; break; }

                         if (visited[i][k]) { isOkay = false; break; }
                     }

                     if (!isOkay) break;
                     now_height = arr[i][j];
                     for (int k = j; k <= j + l - 1; k++) visited[i][k] = true;
                     // visited_check();
                 }
             }
         }

         if (isOkay) { cnt++; }
     }

    cout << cnt << endl;
    return 0;
 }
