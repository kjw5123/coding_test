#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <climits>

using namespace std;

/* [문제]
 * N개의 노드가 있고, 그 사이에 M개의 도로와 W개의 웜홀이 있다
 * 도로는 무향, 웜홀은 유향
 * 웜홀은 시작 위치에서 도착 위치로 가는 하나의 경로다
 * 도착을 하게되면 시작 했을 때 보다 시간이 뒤로간다 (!!)
 * 
 * 한 지점에서 출발해서 다시 돌아왔을 때 시간이 되돌아가는 경우가 있는지 궁금하다
 *
 * [입력]
 * tc 1 ~ 5
 * 지점 N 수 (1 ~ 500)
 * 도로 수 M ( 1 ~ 2,500 )
 * 웜홀 수 W ( 1 ~ 200 )
 *
 * 벨만 포드.. 해야겠지 ?
 * */
struct edge {
    int s, e, w;
};

int tc, n, m, w;
vector<edge> edges;
int dist[501];

void dist_init() {
    for (int i = 1; i <= n; i++) dist[i] = INT_MAX;
}

void print_dist() {
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << endl << endl;
}

void bellman_ford() {
    // dist[1] = 0;  // 모두 연결 돼있으리란 보장이 없구나
    dist[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)edges.size(); j++)  {
            int from = edges[j].s;
            int to = edges[j].e;
            int cost = edges[j].w;
            // cout << "from: " << from << " to: " << to << " cost: " << cost << endl; 
            if (dist[from] == INT_MAX) continue;
            if (dist[to] > dist[from] + cost) {
                // cout << "Now dist[" << to << "] is " << dist[from] + cost << endl;
                dist[to] = dist[from] + cost;
            }
        }
        // print_dist();
    }
    // cout << endl;
    for (int i = 0; i < (int)edges.size(); i++) {
        int from = edges[i].s;
        int to = edges[i].e;
        int cost = edges[i].w;
            // cout << "from: " << from << " to: " << to << " cost: " << cost << endl; 
            // cout << "dist[to] is " << dist[to] << " and dist[from] + cost is " << dist[from] + cost << endl; 
        if (dist[from] == INT_MAX) continue;
        if (dist[to] > dist[from] + cost) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> tc;
    int s, e, weight;
    for (int t = 0; t < tc; t++) {
        edges.clear();
        cin >> n >> m >> w;

        for (int i = 1; i <= n; i++) {
            edges.push_back({0,i,0});
        }

        for (int i = 0; i < m; i++) {
            cin >> s >> e >> weight;
            edges.push_back({s,e,weight});
            edges.push_back({e,s,weight});
        }

        for (int i = 0; i < w; i++) {
            cin >> s >> e >> weight;
            edges.push_back({s,e,-1 * weight});
        }
        dist_init();
        bellman_ford();
    }    
    return 0;
}
