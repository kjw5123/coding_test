#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

/* [문제]
 * N개의 컴퓨터 가 있다 ( 1 ~ 1000 )
 * 간선별로 성능 차이 있다 
 * 직접 연결된 회선이 느려서 다른 컴 쓰는게 더 빠를수도 있다
 *
 * 어휴 조건을 왜 이렇게 덕지덕지 붙여놨어
 * 네트워크가 돌아가게끔 하되,...
 *
 * 아 1번 노드 찍고 목적지 갈 때의 최단거리 구하기인듯 하다
 * */
struct edge {
    int n1, n2;
    int dist;
};

bool cmp(edge& e1, edge& e2) {
    return e1.dist < e2.dist;
}

vector<edge> edges;
vector<edge> results; // pair<int,int> 쓰는게 맞긴 한데 삽입할 때 make_pair 하기 귀찮아서 그냥 edge 넣는다
int n, m;
int parent[1001];

int find(int val) {
    if (val == parent[val]) return val;
    return parent[val] = find(parent[val]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a > b) swap(a, b);
    parent[b] = a;
}

bool isConnected(int a, int b) { 
    a = find(a);
    b = find(b);
    if (a == b) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    
    int a,b,c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        edges.push_back({a,b,c});
    }

    for (int i = 1; i <= n; i++) parent[i] = i;
    sort(edges.begin(), edges.end(), cmp);

    for (int i = 0; i < (int)edges.size(); i++) {
        if (!isConnected(edges[i].n1, edges[i].n2)) {
            unite(edges[i].n1, edges[i].n2);
            results.push_back(edges[i]);
        }
    }

    cout << results.size() << endl;
    for (int i = 0; i < (int)results.size(); i++) {
        cout << results[i].n1 << " " << results[i].n2 << '\n';
    }
    return 0;
}
