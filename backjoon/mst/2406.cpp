#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

// 딴 문젠 몰라도, 귀찮아도 얘는 프림으로도 풀어보자잉
using namespace std;

int n, m; // 컴퓨터 개수, 컴퓨터 쌍 개수
// 일단 1번 컴이랑은 무조건 연결돼있으니까
// 1번 빼고 싹다 union find 함 해주면 될듯? ㅋㅋㅋ
// ㅇㅈ? ㅇ ㅇㅈ

int cost[1001][1001];
int parent[1001];
long long int x; // 컴퓨터 쌍 개수 k는 그냥 나중에 k 따로 파서 처리하자
struct edge {
    int n1, n2;
    long long int cost;
};

bool cmp(edge &e1, edge &e2) {
    return e1.cost < e2.cost;
}

vector<edge> edges;
vector<edge> add_edges;

int find(int val) {
    if (val == parent[val]) return val;
    return parent[val] = find(parent[val]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a > b) swap(a,b);
    if (a == 1) return;
    parent[b] = a;
}


bool isConnected(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return true;
    else return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    
    int a, b;
    for (int i = 0; i <= n; i++) parent[i] = i;

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        edges.push_back({a, b, 0});
        unite(a,b);
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {  // j 초기값 건드리면 cin 꼬임;;
            cin >> cost[i][j];
            if (i != 1 && j != 1 && j > i) edges.push_back({i, j, cost[i][j]});  // 1번 노드의 편린도 남기지 않겠다.
        }
    }

    // 입력 받았는데 이제 머함 ?
    sort(edges.begin(), edges.end(), cmp);
    // 아 근데 이거 짜다 보니 프림이 맞는거 같은데 인생 망했네
    for (int i = 0; i < (int)edges.size(); i++) {
        if (!isConnected(edges[i].n1, edges[i].n2)) {
            add_edges.push_back(edges[i]);
            unite(edges[i].n1, edges[i].n2);
            x += edges[i].cost;
        }
    }
    cout << x << " " << add_edges.size() << '\n';
    for (int i = 0; i < (int)add_edges.size(); i++) {
        cout << add_edges[i].n1 << " " << add_edges[i].n2 << '\n';
    }
    return 0;
}
