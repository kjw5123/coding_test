#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


class Edge {
public:
    int n1, n2;
    int dist;
};

bool cmp(Edge &e1, Edge &e2) {
    return e1.dist < e2.dist;
}

int v, e;
vector<Edge> edges;
int parent[100001];

int find(int val) {
    if (val == parent[val]) return val;
    return parent[val] = find(parent[val]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a > b) swap(a,b);
    parent[b] = a;
}

bool isParent(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 1;
    else return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> v >> e;

    int x, y, d;
    for (int i = 0; i < e; i++) {
        cin >> x >> y >> d;
        edges.push_back({x, y, d});
    }    

    sort(edges.begin(), edges.end(), cmp);
    
    for(int i = 1; i <= v; i++) parent[i] = i;
    
    long long int result = 0;
    
    for (int i = 0; i < (int)edges.size(); i++) {
        if (!isParent(edges[i].n1, edges[i].n2)) {
            result += edges[i].dist;
            unite(edges[i].n1, edges[i].n2);
        }
    }

    cout << result << endl;
    return 0;
}
