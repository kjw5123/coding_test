#include <iostream>

using namespace std;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
double per[4];
int n;
double total = 0;
bool visited [100][100];

void dfs(int y, int x, int depth, double pers) {
    if (depth == n) {
        total += pers;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i]; int nx = x + dx[i];
        if (visited[ny][nx]) continue;
        visited[ny][nx] = true;
        dfs(ny,nx,depth+1,pers*per[i]);
        visited[ny][nx] = false;
    }

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> per[1] >> per[3] >> per[2] >> per[0];  // 동서남북
    per[0] /= 100; per[1] /= 100; per[2] /= 100; per[3] /= 100;
    
    visited[50][50] = true;
    dfs(50,50,0,1.0);
    

    cout.precision(10);
    cout << total << endl;
    return 0;
}
