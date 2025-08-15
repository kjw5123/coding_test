#include <iostream>
#include <algorithm>

using namespace std;

// 코딩 문제가 아니라 국어 문제 같은데 이 쯤 되면


int g, p;  // 공항 개수, 비행기 개수
int parent[100001];

int find(int val) {
    if (val == parent[val]) return val;
    return parent[val] = find(parent[val]);
}

void unite(int a, int b)  {
    a = find(a);
    b = find(b);
    if (a > b) swap(a,b);
    parent[b] = a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> g >> p;
    
    for (int i = 0; i <= g; i++) {
        parent[i] = i;
    }
    
    int cnt = 0; int val;
    for (int i = 0; i < p; i++) {
        cin >> val;
        val = find(val);
        if (val == 0) break;
        unite(val, val-1);
        cnt++;
    }
    
    cout << cnt << endl;
    return 0;
}
