#include <iostream>
#include <queue>
#include <vector>

using namespace std;
int n, a, b, m;
vector<int> v[101];
int visited[101];
int dist[101];
void bfs(int idx) {
    // cout << "My idx is " << idx << endl;
    queue<int> q;
    if (visited[idx] == 0) {
        q.push(idx);
        visited[idx] = idx;
    }

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < v[now].size(); i++) {
            int next = v[now][i];
            if (visited[next] == 0) {
                visited[next] = idx;
                dist[next] = dist[now] + 1;  // bfs에서 거리계산은 이렇게 이어가며 해라..
                q.push(next);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> a >> b >> m;    
    int start, end;

    for (int i = 0; i < m; i++) {
        cin >> start >> end;
        v[start].push_back(end);
        v[end].push_back(start);
    }

    bfs(a);
    /*
    for (int i = 1; i <= n; i++) {
        cout << visited[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;
    */
    if (visited[a] == visited[b]) {
        cout << dist[b] << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
