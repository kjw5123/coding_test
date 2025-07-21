#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;
int arr[9];
bool visited[9] = {0};
vector<int> v;

void dfs(int depth, int val) {
    if (depth == 7 && val == 100) {
        for (int i = 0; i < 9; i++) {
            if (visited[i]) v.push_back(arr[i]);
        }
        sort(v.begin(), v.end());

        for (int i = 0; i < 7; i++) {
            cout << v[i] << '\n';
        }
        exit(0);

    } else if (depth == 7 && val != 100){
        return;
    }

    for (int i = 0; i < 9; i++) {
        if (visited[i]) continue;
        visited[i] = true;
        dfs(depth+1, val + arr[i]);
        visited[i] = false;
    }
}

int main() {
    for (int i = 0; i < 9; i++) {
        cin >> arr[i]; 
    }
    
    for (int i = 0; i < 9; i++) {
        visited[i] = true;
        dfs(1, arr[i]);
        visited[i] = false;
    }
    
    return 0;
}
