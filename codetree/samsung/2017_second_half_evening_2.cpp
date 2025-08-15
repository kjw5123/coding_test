#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int n;

vector<int> nums;
vector<int> opers;
int ops[3];
int minVal = INT_MAX;
int maxVal = INT_MIN;


void dfs(int depth) {
    if (depth == n - 1) {
        int val = nums[0];
        for (int i = 1; i < (int)nums.size(); i++) {
            if (opers[i-1] == 0) {
                val += nums[i];

            } else if (opers[i-1] == 1) {
                val -= nums[i];

            } else {
                val *= nums[i];
            }
        }

        minVal = min(minVal, val);
        maxVal = max(maxVal, val);
        return;
    }

    for (int i = 0; i < 3; i++) {
        if (ops[i] != 0) {
            opers.push_back(i);
            ops[i]--;
            dfs(depth+1);
            ops[i]++;
            opers.pop_back();
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;

    int val;
    for (int i = 0; i < n; i++) {
        cin >> val;
        nums.push_back(val);
    }
    
    for (int i = 0; i < 3; i ++) {
        cin >> ops[i];
    }

    dfs(0);

    cout << minVal << " " << maxVal << endl;
    return 0;
}
