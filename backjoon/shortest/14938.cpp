#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <utility>

using namespace std;

/* [문제]
 * 하나의 지여겡 낙하산 타고 이동해서
 * 그 지역에 떨어진 아이템 줍는 게임 한다 
 *
 * 1등 하면 치킨 주는데 한번도 못해봐서 서운하다 
 *
 * 운이 없어서 그런거라고 생각하니, 
 * 어디에 낙하해야 운이 좋아질지 계산하는 프로그램 만들거다
 *
 * 각 지역은 일정한 길이 ( 1 ~ 15 ) 만큼 떨어져 있고 (다익스트라 ON)
 * 양뱡향 통행이 가능하다 !!!!!!!!!!!!!!!!!!!!!
 * 낙하한 지역 중심으로 수색 범위 ( 1 ~ 15 ) 내 노드들 탐색 가능하니
 * 얻을 수 있는 최대 아이템 개수를 구해보자잇
 * */

int n, m, r; // 지역 개수, 수색범위, 길 개수
int items[101];
vector<pair<int,int> > nodes[101];
int dist[101];
int result[101];
struct cmp {
    bool operator() (pair<int,int> p1, pair<int,int> p2) {
        return p1.first > p2.first;
    }
};

void dijkstra(int start) {
    dist[start] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int> >, cmp> pq;
    pq.push({start, 0});

    while(!pq.empty()) {
        int c_idx = pq.top().first;
        int c_dist = pq.top().second;
        pq.pop();

        for (int i = 0; i < (int)nodes[c_idx].size(); i++) {
            int n_idx = nodes[c_idx][i].first; int n_dist = c_dist + nodes[c_idx][i].second;
            if (n_dist > m) continue;
            if (dist[n_idx] > n_dist) {
                dist[n_idx] = n_dist;
                pq.push({n_idx, n_dist});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dist[i] != INT_MAX) result[start] += items[i];
    }
    // cout << " So result[" << start << "] is " << result[start] << endl << endl;
}

int main() {    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> r;
    for (int i = 1; i <= n; i++) {
        cin >> items[i];
    }
    
    int s, e, w;
    for (int i = 0; i < r; i++) {
        cin >> s >> e >> w;
        nodes[s].push_back({e,w});
        nodes[e].push_back({s,w});
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) dist[j] = INT_MAX;
        dijkstra(i);
    }

    int maxVal = INT_MIN;
    for (int i = 1; i <= n; i++) {
        maxVal  = max(maxVal, result[i]);
    }

    cout << maxVal << endl;
    return 0;
}
