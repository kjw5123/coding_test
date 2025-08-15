#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
int v, e;
vector<pair<int,int>> graphs[100001];
bool visited[100001];  // 노드 방문 여부
struct cmp {
    bool operator() (pair<int,int>& p1, pair<int,int>& p2) {
        return p1.second > p2.second;
    }
};

long long int prim() {
    long long int result = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;
    pq.push({1,0});  // 시작 노드와 가중치

    while (!pq.empty()) {
        int now_node = pq.top().first;
        int now_dist = pq.top().second;
        pq.pop();
        if (visited[now_node]) continue;  // 밑에 반복문에서 관리하면 최소가 뭔지 몰라서 망한다
        visited[now_node] = true;
        result += now_dist;
        for (int i = 0; i < (int)graphs[now_node].size(); i++) {
            int next_node = graphs[now_node][i].first;
            int next_dist = graphs[now_node][i].second;
            if (visited[next_node]) continue;
            pq.push({next_node, next_dist});
        }
    }
    

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> v >> e;
    int x, y, dist;
    for (int i = 0; i < e; i++) {
        cin >> x >> y >> dist;
        graphs[x].push_back({y, dist});
        graphs[y].push_back({x, dist});
    }

    cout << prim() << endl;
    return 0;
}
