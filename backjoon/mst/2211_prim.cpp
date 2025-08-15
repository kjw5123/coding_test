#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>
#include <cstring>

using namespace std;

int n, m;
vector<pair<int,int> > graphs[1001];
bool visited[1001];
int dist[1001];

struct edge {
    int n1, n2;  // before node idx, now node idx
    int dist;
    int one_dist;
};

struct cmp {
    bool operator() (edge& p1, edge& p2) {
        return p1.dist > p2.dist;
    }
};

struct cmp_dijkstra {
    bool operator() (pair<int,int>& p1, pair<int,int>& p2) {
        return p1.second > p2.second;
    }
};

vector<pair<int,int>> results;  // 이게 맞나? 암튼 노드 2개 정보 담지 싶다
void prim() {
    priority_queue<edge, vector<edge>, cmp> pq;
    pq.push({1, 1, 0, 0});  // init 이렇게 해도 문제 없겠지 뭐

    while(!pq.empty()) {
        int bef_node = pq.top().n1;
        int now_node = pq.top().n2;
        // int now_dist = pq.top().dist;
        int one_dist = pq.top().one_dist;
        pq.pop();
        if (one_dist > dist[now_node]) continue;
        if (visited[now_node]) continue;
        visited[now_node] = true;
        if (!(bef_node == 1 && now_node == 1)) results.push_back({bef_node, now_node});
        
        for (int i = 0; i < (int)graphs[now_node].size(); i++) {
            int next_node = graphs[now_node][i].first;
            int next_dist = graphs[now_node][i].second;

            if (!visited[next_node]) {
                pq.push({now_node, next_node, next_dist, one_dist + next_dist});
            }
        }
    }
}

void dijkstra() {
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp_dijkstra> pq;
    pq.push({1, 0}); // 1번 노드 기준 최단 거리이니 ㅇㅇ
    dist[1] = 0;

    while(!pq.empty()) {
        int cur_node = pq.top().first;
        int cur_cost = pq.top().second;
        pq.pop();

        for (int i = 0; i < (int)graphs[cur_node].size(); i++) {
            int next_node = graphs[cur_node][i].first; int next_cost = graphs[cur_node][i].second + cur_cost;
            if (dist[next_node] > next_cost) {
                dist[next_node] = next_cost;
                pq.push({next_node, next_cost});
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    
    int a,b,c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        graphs[a].push_back({b,c});
        graphs[b].push_back({a,c});
    }
    
    for(int i = 0; i <= n; i++) dist[i] = INT_MAX;
    dijkstra();
    prim();

    cout << results.size() << endl;
    for (int i = 0; i < (int)results.size(); i++) {
        cout << results[i].first << " " << results[i].second << '\n';
    }
    return 0;
}
