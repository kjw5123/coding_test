#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;


int cnt[100001];
int arr[200001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n , k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        // count[arr[i]]++;
    }

    //N ^ 2 할 바에는 그냥 l 쭉 돌리기, r 쭉 돌리기 ... 이것도 애매하네


    // l, r 옮기면서 모든 문자열 조합 볼 방법이 있긴 한데
    // 수열이니까 끊기면 안되니까 
    // 오른쪽으로 넓히다가 문제 생기면
    // 문제 생긴 숫자 해결될 때 까지 l을 쪼이면 되잖아
    // 이걸로 r_idx가 n-1 이랑 같아지면 종료하고
 
    int l_idx = 0; int r_idx = 0;
    int maxVal = INT_MIN;
    cnt[arr[0]]++;
    while(true) {
        r_idx++;
        int addVal = arr[r_idx];
        cnt[addVal]++;
        if (cnt[addVal] > k) {
            while(cnt[addVal] > k) {
                int popVal = arr[l_idx++];
                cnt[popVal]--;
            }
        }
        maxVal = max(maxVal, r_idx - l_idx + 1);
        if (r_idx == n-1) break;
    }
    cout << maxVal << endl;
    return 0;
}
