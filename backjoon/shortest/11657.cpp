#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <cstdlib>

using namespace std;
struct edge {
    int s;
    int e;
    int d;
};

int n, m;
long long int dist[501];
vector<edge> edges;

bool bellman_ford() {
    dist[1] = 0;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < (int)edges.size(); j++) {
            int s = edges[j].s;
            int e = edges[j].e;
            int cost = edges[j].d;

            if (dist[s] == INT_MAX) continue;
            if (dist[e] > dist[s] + cost) dist[e] = dist[s] + cost;
        }
    }

    for (int i = 0; i < (int)edges.size(); i++) {
        int s = edges[i].s;
        int e = edges[i].e;
        int cost = edges[i].d;

        if (dist[s] == INT_MAX) continue;
        if (dist[e] > dist[s] + cost) { cout << -1 << endl; return false; }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= 500; i++) dist[i] = INT_MAX;
    
    int s, e, d;
    for (int i = 0; i < m; i++) {
        cin >> s >> e >> d;
        edges.push_back({s,e,d});
    }

    if(bellman_ford()) {
        for (int i = 2; i <= n; i++ ) {
            if (dist[i] != INT_MAX) cout << dist[i] << '\n';
            else cout << -1 << '\n';
        }
    }
    return 0;
}
