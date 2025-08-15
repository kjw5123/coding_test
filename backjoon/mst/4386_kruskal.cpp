#include <iostream>
#include <cmath> // 아오 씨 진짜 
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// 와 소수 정말 싫다

int n;
struct edge {
    int n1, n2;
    double dist;
};

vector<edge> edges;
pair<double,double> stars[101];
int parent[101];

bool cmp(edge &e1, edge &e2) {
    return e1.dist < e2.dist;
}

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

bool isConnected(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return true;
    else return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;

    double x, y;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y;
        stars[i] = {x, y};
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            double x_diff = (stars[i].first - stars[j].first);
            x_diff *= x_diff;
            double y_diff = (stars[i].second - stars[j].second);
            y_diff *= y_diff;
            edges.push_back({i, j, sqrt(y_diff + x_diff)});
        }
    }
    sort(edges.begin(), edges.end(), cmp);
    for (int i = 1; i <= n; i++) parent[i] = i;
    
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
