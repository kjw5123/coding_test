#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> v[1001];
bool visited[1001];
bool dfs(int num) {
    if (!visited[num]) {
        visited[num] = true;
        for (int i = 0; i < v[num].size(); i++) {
            dfs(v[num][i]);
        }
        return 1;
    }
    return 0;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    int cnt = 0;
    for (int i = 1; i <=n; i++) {
        bool new_root = dfs(i);
        if (new_root) {
            cnt++;
//            cout << i << " is new root " << endl;
        }
/*
        for(int j = 0; j < v[i].size();j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
        */
    }   
    cout << cnt << endl;

    return 0;
}
