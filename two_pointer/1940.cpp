#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// sort 함 하고 
// 좌 우 뭐 짝 맞는거 나오거나 대충 비교해서 idx 옮기면 되겠제 ㅋㅋ 
vector<int> v;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    int val;
    for (int i = 0; i < n; i++) {
        cin >> val;
        v.push_back(val);
    }

    sort(v.begin(), v.end());
    

    int l_idx = 0;
    int r_idx = v.size() - 1;

    int cnt = 0;
    while(true) {
        if (l_idx >= r_idx) break;

        int l_val = v[l_idx];
        int r_val = v[r_idx];

        if (l_val + r_val == m) {
            cnt++;
            l_idx++; r_idx--;
            continue;

        } else if (l_val + r_val < m) {
            l_idx++; continue;

        } else {
            r_idx--; continue;
        }
    }
    cout << cnt << endl;
    return 0;
}
