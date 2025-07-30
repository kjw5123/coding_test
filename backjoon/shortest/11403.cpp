#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

bool visited[101][101];
vector<int> v[101];
int n;

struct cmp {  // 아니 근데 dist 구하는게 아니라 방문 처리만 하는거라 굳이?
    bool operator() (pair<int,int> p1, pair<int,int> p2) {
        return p1.second > p2.second;
    }
};

void dijkstra(int start) {
    queue<int> q;
    q.push(start);

    while(!q.empty()) {
        int c_idx = q.front();
        q.pop();

        for (int i = 0; i < (int)v[c_idx].size(); i++) {
            int n_idx = v[c_idx][i];
            if (!visited[start][n_idx]) {
                visited[start][n_idx] = true;
                q.push(n_idx);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    bool val;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> val;
            if (val) v[i].push_back(j);
        }
    }
    for (int i = 1; i <= n; i++) {
        dijkstra(i);
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << visited[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
