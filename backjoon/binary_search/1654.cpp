#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
// 그리디 처럼 보이는데 이분탐색이라니..

int n, m;
vector<int> v;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;

    int val;
    for (int i = 0; i < n; i++) {
        cin >> val;
        v.push_back(val);
    }
    sort(v.begin(), v.end());
    long long int low = 1; long long int high = INT_MAX;  // idx가 아님.. 그냥 길이임...
    long long int res = 0;

    while(low <= high) {
        long long int mid = (low + high) / 2;
        long long int k = 0;
        for (int i = 0; i < (int)v.size(); i++) {
            k += v[i] / mid;
        }
        // cout << "mid is " << mid << " and count is " << k << endl;

        if (k >= m) {
            res = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    cout << res << endl;
    return 0;
}
