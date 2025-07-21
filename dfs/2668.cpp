#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n;
int arr[3][101];  // 뭐 이런 바보같은 짓을..
bool visited[101];
vector<int> same;
vector<int> result;
vector<int> mid;

void visited_init() {
    for (int i = 1; i <= n; i++) visited[i] = false;
}

bool dfs(int idx, int first) {
    bool cycle = false;
    mid.push_back(idx);
    visited[idx] = true;
    int next = arr[2][idx];
    if (next == first) cycle = true;  // 어짜피 이미 같은 수들이면 visited 돼서 아래 조건이랑 안곂침
    if (!visited[next]) {  // cycle이면 알아서 true 들고 와준다 
        cycle = dfs(next, first);
    }
    return cycle;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        arr[1][i] = i;
        cin >> arr[2][i];
        if(i == arr[2][i]) same.push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        visited_init();
        mid.clear();
        bool cycle = dfs(i, i);
        if (cycle == true) {
            for (int j = 0; j < mid.size(); j++) {
                result.push_back(mid[j]);
            }
        }
    }
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    cout << result.size() << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << '\n';
    }
    return 0;
}
