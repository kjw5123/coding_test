#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
int n, m;
vector<pair<int,int> > graphs[100001];
bool visited[100001];
long long int result = 0;
int maxVal = INT_MIN;

struct cmp {
    bool operator() (pair<int,int> &p1, pair<int,int> &p2) {
        return p1.second > p2.second;
    }
};

void prim() {
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;
    pq.push({1, 0});

    while(!pq.empty()) {
        int now_node = pq.top().first;
        int now_dist = pq.top().second;
        pq.pop();

        if (visited[now_node]) continue;
        visited[now_node] = true;
        result += now_dist;
        maxVal = max(maxVal, now_dist);

        for (int i = 0; i < (int)graphs[now_node].size(); i++) {
            int next_node = graphs[now_node][i].first;
            int next_dist = graphs[now_node][i].second;
            if (!visited[next_node]) {
                pq.push({next_node, next_dist});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    int a,b,c;  // start, end도 못쓰고 지나ㅉ 변수명 짓기 너무 애매한 이것들... 밉다 미워
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        graphs[a].push_back({b,c});
        graphs[b].push_back({a,c});
    }
    prim();

    cout << result - maxVal << endl;
    return 0;
}
