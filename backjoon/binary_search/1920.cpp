#include <iostream>

// 이걸 왜 못풀었을까 예전엔
// 아니 범위가 INT 범위였구나 1 ~ 100,000이 아니라 
// 에전에 내가 빠가가 아니였네 휴 
#include <vector>
#include <algorithm>
using namespace std;
int n, m;
// bool arr[100001];
vector<int> v;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;

    int val;
    for (int i = 0; i < n; i++) {
        cin >> val;
        v.push_back(val);
    }
    sort(v.begin(), v.end());

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> val;
        int low = 0; int high = n - 1;
        int res = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (v[mid] == val) { res = 1; break; }
            else if (v[mid] < val) low = mid + 1;
            else high = mid - 1;
        }
        cout << res << '\n';
    }

    return 0;
}
