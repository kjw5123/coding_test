#include <iostream>
#include <algorithm>
using namespace std;

int n , m;
int parent[1000001];

int find(int val) {
    if (val == parent[val]) return val;  // 최종 목적지에 도착했으면 걍 return
    return parent[val] = find(parent[val]);  // 최종 목적지에서 return 된거 일괄 적용 
}

void unite(int a, int b) {
    a = find(a);  // 어쨌든 부모 찾아오기
    b = find(b);  // 위와 동
    if (a > b) swap(a,b);  // 걍 작은 부모로 통일
    parent[b] = a;  // 작은 값으로 최종 부모 통일
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    
    // init
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }
    
    int flag, a, b;
    for (int i = 0; i < m; i++) {
        cin >> flag >> a >> b;
        if (flag == 0) {
            if (find(a) != find(b)) unite(a, b);  // 이거 안하면 cycle 생길 수도 있음

        } else {
            if (find(a) == find(b)) cout << "YES\n";
            else cout << "NO\n";
        }
        // cout << "Parents: ";
        // for (int i = 0; i <= n; i++) cout << parent[i] << " ";
        // cout << endl;
    } 
    
    return 0;
}
