#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath> // 크아아아악 ~ !!! ! ! ! ! ! !

using namespace std;

int n, m;

struct edge{
    int n1, n2;
    double dist;
};

bool cmp(edge &e1, edge &e2) {
    return e1.dist < e2.dist;
}

int parent[1001];
pair<int,int> gods[1001];
vector<edge> edges;


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

    for(int i = 1; i <= n; i++) parent[i] = i;

    int x, y;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y;
        gods[i] = {x, y};
    }

    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        if (!isConnected(a, b)) {
            unite(a,b);
            edges.push_back({a,b,0.0});
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (!isConnected(i, j)) {
                // 얼탱;;
                long long int x_diff = (gods[i].first - gods[j].first); x_diff *= x_diff;
                long long int y_diff = (gods[i].second - gods[j].second); y_diff *= y_diff;
                edges.push_back({i, j, sqrt(x_diff + y_diff)});
            }
        }
    }

    sort(edges.begin(), edges.end(), cmp);

    double result = 0.0;
    for (int i = 0; i < (int)edges.size(); i++) {
        if (!isConnected(edges[i].n1, edges[i].n2)) {
            unite(edges[i].n1, edges[i].n2);
            result += edges[i].dist;
        }
    }
    
    cout << fixed;
    cout.precision(2);
    cout << result << endl;
    return 0;
}
