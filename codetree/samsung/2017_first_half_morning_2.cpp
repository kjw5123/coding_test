#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

// DP 관상인데..
// n일 휴가동안 사이드 프로젝트를 만들어서 돈좀 만져볼까 한다
// 수행할 수 있는 작업은 하루에 하나씩 있고
// 각 외주 작업을 수행하는 데에는 기한 t, 완료 시 보상 p가 있다
// 2개 이상 못한다. (즉 하나 붙잡고 있으면 그거 하나만 가능하다)
// DP일텐데 분명
// 그리디 같기도 하고?
int n;
bool arr[16][16];
int vals[16];
int result = INT_MIN;

void dfs(int idx, int val) {
    result = max(result, val);

    for (int i = idx; i <= n; i++) {
        if (!arr[idx][i]) continue;
        dfs(i, val + vals[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    memset(arr, 0x00, sizeof(arr));

    cin >> n;
    int days;

    for (int i = 1; i <= n; i++) {
        cin >> days;
        if (i + days - 1 > n) { cin >> vals[i]; vals[i] = 0; continue; }
        for (int j = i + days; j <= n; j++) arr[i][j] = true;  // 어떤 특정한 날로부터, 가능한 이후 날들
        cin >> vals[i];
    }

    for(int i = 1; i <= n; i++) {
        dfs(i, vals[i]);
    }

    cout << result << endl;
    return 0;
}
