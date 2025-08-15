#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

int n;  // 무조건 짝수 입력
int arr[21][21];
int result = INT_MAX;

// n C (n/2) 2개씩 생성될 것이다
// 최악의 경우에도 19 * 17 * 15 * 13 * 11 * 32 * 10

// n = 4
// 1 2 | 3 4
// 1 3 | 2 4
//
// 아!! 걍 depth로 제한해버리고
// 상대측 역할 할거를, n 범위 내에서 지금 vector랑 안곂치는것만 담은 vector 하나 생성하면 되겠네 
// 간단한 문제다
//
//
// 근데
// 너무 쓸데없이 복잡하게 푼 감이 없잖아 있다

vector<int> selected;
vector<int> unselected;
vector<int> idxs;

int mini_dfs(int idx, int depth, bool s_flag) {
    int val = 0;
    if (depth == 2) {
        /*
        if (s_flag) {cout << "Ok, I'm selected vector" << endl; cout << "And, I'll return " << arr[idxs[0]][idxs[1]] + arr[idxs[1]][idxs[0]] << endl; }
        else {cout << "Ok, I'm Unselected vector" << endl; cout << "And, I'll return " << arr[idxs[0]][idxs[1]] + arr[idxs[1]][idxs[0]] << endl; }
        cout << idxs[0] << " " << idxs[1] << endl; 
        */
        return arr[idxs[0]][idxs[1]] + arr[idxs[1]][idxs[0]];
    }
    
    if (s_flag) {  // selected
        for (int i = idx + 1; i < (int)selected.size(); i++) {
            idxs.push_back(selected[i]);
            val += mini_dfs(i, depth+1, s_flag);
            idxs.pop_back();
        }
    }
    else {
        for (int i = idx + 1; i < (int)unselected.size(); i++) {
            idxs.push_back(unselected[i]);
            val += mini_dfs(i, depth+1, s_flag);
            idxs.pop_back();
        }
    }
    return val;
}

void check_vectors() {
    cout << "selecteds: " << endl;
    for (int i = 0; i < (int)selected.size(); i++) {
        cout << selected[i] << " ";
    }
    cout << endl << endl;
    cout << "Unselecteds: " << endl;
    for (int i = 0; i < (int)unselected.size(); i++) {
        cout << unselected[i] << " ";
    }
    cout << endl << endl;
}

void dfs(int idx, int depth) {
    if (depth == n / 2) {
        bool visited[21] = {0};

        for (int i = 0; i < (int)selected.size(); i++) { visited[selected[i]] = true; }
        for (int i = 1; i <= n; i++) { if (!visited[i]) { unselected.push_back(i); } }
        // check_vectors();

        int morning_val = mini_dfs(-1, 0, true);
        int evening_val = mini_dfs(-1, 0, false);
        unselected.clear();
        result = min(result, abs(morning_val - evening_val));
        return;
    }

    for (int i = idx + 1; i <= n; i++) {
        selected.push_back(i);
        dfs(i, depth+1);
        selected.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }

    dfs(0, 0);

    cout << result << endl;
    return 0;
}
