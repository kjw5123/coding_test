#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

int v, e, start;
long long int dist[20001];
vector<pair<int,int> > edges[20001];
struct cmp {
    bool operator() (pair<int,int> p1, pair<int,int> p2) {
        return p1.second > p2.second;
    }
};

void dijkstra(int start) {
    dist[start] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int> >, cmp> pq;
    pq.push({start, 0});

    while(!pq.empty()) {
        int ce = pq.top().first;
        int cd = pq.top().second;
        pq.pop();

        for (int i = 0; i < (int)edges[ce].size(); i++) {
            int ne = edges[ce][i].first;
            int nd = edges[ce][i].second + cd;
            if (dist[ne] > nd) {
                pq.push({ne, nd});
                dist[ne] = nd;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> v >> e >> start;
    int from, to, weight;
    for (int i = 1; i <= v; i++) dist[i] = INT_MAX;

    for (int i = 0; i < e; i++) {
        cin >> from >> to >> weight;
        edges[from].push_back({to, weight});
    }
    
    dijkstra(start);
    for (int i = 1; i <= v; i++) {
        if (dist[i] != INT_MAX) cout << dist[i] << '\n';
        else cout << "INF\n";
    }
    return 0;
}
