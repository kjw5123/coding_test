#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

// 음~ 맛있는 backtracking 문제~
// 무난~하게 depth = 1 ~ n 해서
// 탐색 슥슧긋긋긌ㄲ쓲쓲 진행하자

using namespace std;
int n;
int minVal = INT_MAX;
int max_depth = 1;
pair<int,int> food[11]; // 1 base 할거다
void dfs(int idx, int depth, int shin, int ssun) {
    if (max_depth == depth) {
        minVal = min(minVal, abs(shin- ssun));
        return;
    }

    for (int i = idx + 1; i <= n; i++) {
        dfs(i, depth+1, shin * food[i].first, ssun + food[i].second);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> food[i].first >> food[i].second;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            max_depth = j;
            dfs(i, 0, 1, 0);
        }
    }
    cout << minVal << endl;
    return 0;
}
