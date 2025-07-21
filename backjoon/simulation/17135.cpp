#include <iostream>
#include <cstring>
#include <vector>
#include <climits>
#include <set>
#include <algorithm>

using namespace std;

int n, m, d;
bool org[16][16];
bool arr[16][16];
vector<int> archor_idx;
vector<pair<int,int> > enemy;

void check_arr() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isEnemy() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j]) return true;
        }
    }
    return false;
}

void enemy_input() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] == true) enemy.push_back({i,j});
        }
    }
}

void enemy_move() {
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            if (i == n && arr[i][j] == true) arr[i][j] = 0;
            else if (arr[i][j] == true) {
                arr[i][j] = false;
                arr[i+1][j] = true;
            }     
        }
    }
}

bool cmp(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first == p2.first) return p1.second < p2.second;
    return p1.second < p2.second;
}

pair<int, int> find_to_kill(int ay, int ax) {
    vector<pair<int, int> > v;
    int min_diff = INT_MAX;
    for (int i = 0; i < (int)enemy.size(); i++) {
        int diff = abs(ay - enemy[i].first) + abs(ax - enemy[i].second);
        if (diff > d) continue;
        if (min_diff > diff) min_diff = diff;
    }

    for (int i = 0; i < (int)enemy.size(); i++) {
        int diff = abs(ay - enemy[i].first) + abs(ax - enemy[i].second);
        if (diff == min_diff) v.push_back(enemy[i]);
    }
    
    sort(v.begin(), v.end(), cmp);
    if (v.size() == 0) return {-1, -1};
    else return v[0];
}

int archor_shot() {
    int archor_y = n + 1;
    set<pair<int, int> > s;
    for (int i = 0; i < (int)archor_idx.size(); i++) {
        s.insert(find_to_kill(archor_y, archor_idx[i]));
    }
    bool minusFlag = false;
    for (set<pair<int, int> >::iterator it = s.begin(); it != s.end(); it++) {
        if(it->first == -1 && it->second == -1) minusFlag = true;
        else arr[it->first][it->second] = false;
    }

    if (!minusFlag) return s.size();
    else return s.size() - 1;
}

int dfs(int idx, int depth) {
    int val = INT_MIN;
    if (depth == 3) {
        val = 0;
        memcpy(arr, org, sizeof(arr));
        while(isEnemy()) {
            enemy.clear();
            enemy_input();
            // check_arr();
            val += archor_shot();
            // check_arr();
            enemy_move();
            // check_arr();
        }
        return val;
    }

    for (int i = idx + 1; i <= m; i++) {
        archor_idx.push_back(i);
        val = max(val, dfs(i, depth+1));
        archor_idx.pop_back();
    }

    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> d;
    for (int i = 1; i <= n ; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> org[i][j];
        }
    }
    
    cout << dfs(0, 0) << endl;
    return 0;
}
