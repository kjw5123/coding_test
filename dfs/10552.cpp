// 아니 왜 영어야 문제가
// 아니 위상 정렬도 안먹힐텐데 이거
// 크아악...!! 실버 2 주제에 왜이리 어렵냔 말이다-!!

#include <iostream>
#include <vector>

using namespace std;
int n, m, p;
int cnt = 0;
vector<int> v[100001];
bool visited[100001];

void dfs(int c)  {
    if (visited[c] == true) {
        cout << -1 << endl;
        exit(0);
    }
    visited[c] = true; cnt++;
    if (v[c].size() == 0) return;
    else dfs(v[c][0]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> p;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v[b].push_back(a);  // sort 필요 없다
    }
    
    dfs(p);
    cout << cnt - 1 << endl;
    return 0;
}
