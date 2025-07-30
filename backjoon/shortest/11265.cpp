#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

/* [문제]
 * 앙 민호띠~
 *
 * N개의 파티장을 가진 놀이동산이다 
 * 증축할 대 마다 기존 파티장과 직접 연결되게끔 한다
 * 단방향이다 
 * 아 몰라 다익스트라다 이건 
 *
 * [입력]
 * 파티장 N 5 ~ 500
 * 서비스 요청 손님 M  1 ~ 10,000
 * 파티장은 1 ~ N 번호 붙어있다
 * T개 edge 있다
 *
 * */ 
int n, m;
vector<pair<int,int> > nodes[501];
int dist[501][501];
struct cmp {
    bool operator() (pair<int,int> p1, pair<int,int> p2) {
        return p1.second > p2.second;
    }
};

void check_dist() {
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << endl << endl;
}

void dijkstra(int start) {
    dist[start][start] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int> >, cmp> pq;
    pq.push({start, 0});

    while(!pq.empty()) {
        int c_idx = pq.top().first;
        int c_dist = pq.top().second;
        // cout << "now my index is " << c_idx << " and c_dist is " << c_dist << endl;
        pq.pop();

        for(int i = 0; i < (int)nodes[c_idx].size(); i++) {
            int n_idx = nodes[c_idx][i].first; int n_dist = c_dist + nodes[c_idx][i].second;
            if (dist[start][n_idx] > n_dist) {
                dist[start][n_idx] = n_dist;
                pq.push({n_idx, n_dist});
                // cout << "I insert idx " << n_idx << " and n_dist is " << n_dist << endl; 
            }
        }
    }
    // check_dist();
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = INT_MAX;
        }
    }

    int val;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> val;
            if(i != j) nodes[i].push_back({j,val});
        }
    }
    for (int i = 1; i <= n; i++) {
        dijkstra(i);
    }

    int s, e, d;
    for (int i = 0; i < m; i++) {
        cin >> s >> e >> d;
        if (dist[s][e] <= d) cout << "Enjoy other party\n";
        else cout << "Stay here\n";
    }

    return 0;
}
