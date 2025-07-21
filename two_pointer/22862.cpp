#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<int> v;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    int cnt = 0;
    int val;

    for (int i = 0; i < n; i++) {
        cin >> val;
        if (val % 2 == 0) cnt++;
        else {
            if(cnt != 0) v.push_back(cnt);
            cnt = 0;
            v.push_back(cnt);
        }
    }
    if (cnt != 0) v.push_back(cnt);

    // v 안에 0 1 0 1 0 1  뭐 이렇게 돼 있을 거다 
    // minIdx = 0 뭐 늘 하던 그거 ㄱ 
    cnt = 0;
    int l_idx = 0; int r_idx = 0;
    int maxVal = INT_MIN; int currentVal = 0;

    while(true) {
        if (r_idx == (int)v.size()) break;

        if (v[r_idx] == 0) cnt++;
        currentVal += v[r_idx];
        r_idx++;

        if (cnt > k) {
            while (cnt > k) {
                currentVal -= v[l_idx];
                if(v[l_idx] == 0) cnt--;
                l_idx++;
            }
        }
        maxVal = max(maxVal, currentVal);
    }
    cout << maxVal << endl;
    return 0;
}
