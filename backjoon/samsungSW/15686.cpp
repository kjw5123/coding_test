#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

// 1. NxN 도시가 있다
//    각 칸은 빈칸, 치킨발사대, 집 있음
//
// 2. 열 길이 / 행 길이 정보부터 준다 ( 1base )
//
// 3. 각 집들은 치킨 가게와 집 간의 x,y 거리 차이인 '치킨 거리'를 가짐
//
int n , m;
int arr[51][51];
vector<pair<int, int>> h; // 집 (1)
vector<pair<int, int>> c; // 치킨집 (2)
vector<int> selected;
int result = INT_MAX;

int get_chicken_dist() {
    int total = 0;

    for (int i = 0; i < h.size(); i++) {
        int hy = h[i].first;
        int hx = h[i].second;

        int min_dist = INT_MAX;
        for (int j = 0; j < selected.size(); j++) {
            int cy = c[selected[j]].first;
            int cx = c[selected[j]].second;

            int dist = abs(hy - cy) + abs(hx - cx);
            if (dist < min_dist) min_dist = dist;
        }

        total += min_dist;
    }

    return total;
}

void dfs(int idx, int cnt) {
    if (cnt == m) {
        int d = get_chicken_dist();
        if (d < result) result = d;
        return;
    }

    for (int i = idx; i < c.size(); i++) {
        selected.push_back(i);
        dfs(i + 1, cnt + 1);
        selected.pop_back();
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 1) h.push_back({i, j});
            else if (arr[i][j] == 2) c.push_back({i, j});
        }
    }
    
    dfs(0,0);
    cout << result << endl;
    
    
    return 0;
}
