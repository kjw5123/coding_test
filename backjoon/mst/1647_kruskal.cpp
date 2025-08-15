#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
/* [문제]
 * 집 100,000개
 * 길 1,000,000개
 * 
 * 마을 2개로 나눌 생각이다
 * */
struct edge{
    int n1, n2, dist;
};

bool cmp(edge &e1, edge &e2)  {
    return e1.dist < e2.dist;
}

int n, m;
vector<edge> edges;
int parent[100001];
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
    else return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m; 

    int a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c ;
        edges.push_back({a,b,c});
    }

    sort(edges.begin(), edges.end(), cmp);
    
    for (int i = 1; i <= n; i++) parent[i] = i;
    int maxDist = INT_MIN;  // 어짜피 1줄로 연결돼있으니까 큰 값 하나만 빼버리면 그게 최단 거리제
    int result = 0;

    for (int i = 0; i < (int)edges.size(); i++) {
        if (!isConnected(edges[i].n1, edges[i].n2)) {
            result += edges[i].dist;
            unite(edges[i].n1, edges[i].n2);
            maxDist = max(maxDist, edges[i].dist);
        }
    }

    cout << result - maxDist << endl;
    return 0;
}
