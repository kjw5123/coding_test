#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 오르막길은 점선, 내리막길은 실선
// 입구엔 숫자 0 부여
// 오르막길을 싫어함
// 오르막길 k번 오르면 피로도 k^2 됨
//
// 최대 피로도랑 최소 피로도 차를 출력해보자
// 수식 쓰기 귀찮은데, 간선은 최악의 경우에 모든 노드끼리 모두 길이 있을 수도 있다
//
// 음 조건 읽어보면 같은 경로 상 중복되는 경우는 없다 한다
// 
// 맘 같아선
// 1. 최소 피로도를 위해 내리막만 union find 하기
// 2. 다했으면, node 수 - 1 개의 간선에 대해 몇개가 부족한지 확인하기
// 3. 근데 이게 최적해일까?
// 모르겠지만 어쨌든 최적해일 수밖에 없을 거 같다
// 진행시켜

int n, m;

vector<pair<int,int>> down_edges;
vector<pair<int,int>> up_edges;
int parent[100001];  // 초기화 깜빡하지마 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
long long int minVal, maxVal;

int  find(int val) {
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

    cin >> n >> m;
    int min_edge_num = n;  // 0 node 때문에 1 더해줘야 한다

    int a,b,c;
    for (int i = 0; i < m+1; i++) {
        cin >> a >> b >> c;
        if (c == 1) down_edges.push_back({a,b});
        else up_edges.push_back({a,b});
    }
    
    for (int i = 0; i <= n; i++) parent[i] = i;
    for (int i = 0; i < (int)down_edges.size(); i++) {
        if (!isConnected(down_edges[i].first, down_edges[i].second)) {
            unite(down_edges[i].first, down_edges[i].second);
            // cout << " I unite " << down_edges[i].first << " " << down_edges[i].second << endl;
            // cout << "down" << endl;
            minVal++;
        }
    }
    minVal = (min_edge_num - minVal) * (min_edge_num - minVal);


    for (int i = 0; i <= n; i++) parent[i] = i;
    for (int i = 0; i < (int)up_edges.size(); i++) {
        if (!isConnected(up_edges[i].first, up_edges[i].second)) {
            unite(up_edges[i].first, up_edges[i].second);
            // cout << " I unite " << up_edges[i].first << " " << up_edges[i].second << endl;
            // cout << "up" << endl;
            maxVal++;
        }
    }
    maxVal *= maxVal;

    cout << maxVal - minVal << endl;
    return 0;
}
