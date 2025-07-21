#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> v[101];
bool visited[101] = {0};

void dfs(int val, int idx) {
    // visited[val] = true;
    for (int i = 0; i < v[val].size(); i++) {
        int next = v[val][i];
        if (!visited[next]) {
            visited[next] = true;
            dfs(next, idx);
            v[idx].push_back(next);
        }
    }
}

void visited_init() {
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }
}

int arr[101][101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    int a;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a;
            if (a == 1) v[i].push_back(j);
        }
    }

    for(int i = 1; i <= n; i++) {
        visited_init();
        dfs(i, i);
    }
 
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < v[i].size(); j++) {
            arr[i][v[i][j]] = 1;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << '\n';
    }
    return 0;
}
