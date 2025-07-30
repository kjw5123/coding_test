#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int n, m, k, x;
vector<int> v[300001];
int dist[300001];

struct cmp{
    bool operator() (pair<int,int> p1, pair<int,int> p2) {
        return p1.second > p2.second;  // 늘 말하지만 pq용 cmp는 이게 오름차순임
    }
};
void dijkstra(int start) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;
    pq.push({start, 0});  // 
    dist[start] = 0;

    while(!pq.empty()) {
        int c_idx = pq.top().first;
        int c_dist = pq.top().second;
        pq.pop();

        for (int i = 0; i < (int)v[c_idx].size(); i++) {
            int n_idx = v[c_idx][i]; int n_dist = c_dist + 1;
            if (dist[n_idx] > n_dist) {
                dist[n_idx] = n_dist;
                pq.push({n_idx, n_dist});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k >> x;
    for (int i = 0; i <= 300000; i++) dist[i] = INT_MAX;
    int s, e;
    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        v[s].push_back(e);
    }
    
    dijkstra(x);
    
    bool isExist = false;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == k) {
            cout << i << '\n';
            isExist = true;
        }
    }

    if (!isExist) cout << -1 << endl;
    return 0;
}
