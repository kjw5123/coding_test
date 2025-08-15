#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int n, m;
int parent[201];
int arr[201][201];

vector<int> directions;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if(arr[i][j] == 1) unite(i, j);
        }
    }

    int d;
    for (int i = 0; i < m; i++) {
        cin >> d;
        directions.push_back(d);
    }

    bool isSame = true;
    int val = find(directions[0]);
    for (int i = 0; i < (int)directions.size(); i++) {
        if (val != find(directions[i])) isSame = false;
    }

    if (isSame) cout << "YES";
    else cout << "NO";
    return 0;
}
