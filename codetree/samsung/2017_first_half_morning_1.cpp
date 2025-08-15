#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

// depth 4개까지 dfs 진행 해서 이 때의 합 계속 생신하기
int n, m;
int arr[201][201];
bool visited[201][201];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int result = INT_MIN;

vector<pair<int,int>> shapes[20];

int check_idx(int y, int x, int idx) {
    int val = 0;
    for (int i = 0; i < 4; i++) {
        int ny = y + shapes[idx][i].first;
        int nx = x + shapes[idx][i].second;
        if (ny <= 0 || ny > n || nx <= 0 || nx > m) return -1;
        val += arr[ny][nx];
    }
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
        }
    }
    
    // 짝대기 2개
    // ㅗ 4개
    // ㄴ 8개
    // ㅁ 1개
    // ㄹ 4개
    shapes[0].push_back({0,0}); shapes[0].push_back({1,0}); shapes[0].push_back({2,0}); shapes[0].push_back({3,0});
    shapes[1].push_back({0,0}); shapes[1].push_back({0,1}); shapes[1].push_back({0,2}); shapes[1].push_back({0,3});

    shapes[2].push_back({0,0}); shapes[2].push_back({0,1}); shapes[2].push_back({0,2}); shapes[2].push_back({1,1});
    shapes[3].push_back({0,0}); shapes[3].push_back({0,1}); shapes[3].push_back({0,2}); shapes[3].push_back({-1,1});
    shapes[4].push_back({0,0}); shapes[4].push_back({1,0}); shapes[4].push_back({2,0}); shapes[4].push_back({1,1});
    shapes[5].push_back({0,0}); shapes[5].push_back({1,0}); shapes[5].push_back({2,0}); shapes[5].push_back({1,-1});


    shapes[6].push_back({0,0}); shapes[6].push_back({0,1}); shapes[6].push_back({0,2}); shapes[6].push_back({1,2});
    shapes[7].push_back({0,0}); shapes[7].push_back({0,1}); shapes[7].push_back({0,2}); shapes[7].push_back({-1,2});
    shapes[8].push_back({0,0}); shapes[8].push_back({1,0}); shapes[8].push_back({2,0}); shapes[8].push_back({2,1});
    shapes[9].push_back({0,0}); shapes[9].push_back({1,0}); shapes[9].push_back({2,0}); shapes[9].push_back({2,-1});
    shapes[10].push_back({0,0}); shapes[10].push_back({0,-1}); shapes[10].push_back({0,-2}); shapes[10].push_back({1,-2});
    shapes[11].push_back({0,0}); shapes[11].push_back({0,-1}); shapes[11].push_back({0,-2}); shapes[11].push_back({-1,-2});
    shapes[12].push_back({0,0}); shapes[12].push_back({-1,0}); shapes[12].push_back({-2,0}); shapes[12].push_back({-2,1});
    shapes[13].push_back({0,0}); shapes[13].push_back({-1,0}); shapes[13].push_back({-2,0}); shapes[13].push_back({-2,-1});

    shapes[14].push_back({0, 0}); shapes[14].push_back({0, 1}); shapes[14].push_back({1, 0}); shapes[14].push_back({1, 1});

    shapes[15].push_back({0, 0}); shapes[15].push_back({1, 0}); shapes[15].push_back({1, 1}); shapes[15].push_back({2, 1});
    shapes[16].push_back({0, 0}); shapes[16].push_back({1, 0}); shapes[16].push_back({1, -1}); shapes[16].push_back({2, -1});
    shapes[17].push_back({0, 0}); shapes[17].push_back({0, 1}); shapes[17].push_back({1, 1}); shapes[17].push_back({1, 2});
    shapes[18].push_back({0, 0}); shapes[18].push_back({0, 1}); shapes[18].push_back({-1, 1}); shapes[18].push_back({-1, 2});

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k <= 18; k++) {
                int val = check_idx(i,j,k);
                if (val != -1) result = max(result, val);
            }
        }
    }

    cout << result << endl;
    return 0;
}
