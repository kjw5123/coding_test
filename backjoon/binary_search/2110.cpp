#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

// 집이 N개 있다 
// 어디서든 와이파이 즐기려고 한다
// 공유기 C개 있음 
//
// 공유기간 거리를 최대한 크게 해볼 생각이다
int n, m;
vector<int> v;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    int val;
    for (int i = 0; i < n; i++) { cin >> val; v.push_back(val); }

    sort(v.begin(), v.end());

    int low = 0; int high = v[n-1]-v[0];
    int dist = 0;

    while ( low <= high ) {
        int cnt = 1;

        int mid = (low + high) / 2;
        int start = v[0];

        for (int i = 1; i < n; i++) {
            int end = v[i];

            if (end - start >= mid) {
                cnt += 1;
                start =end;
            }
        }
        if (cnt >= m) {
            dist = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << dist << endl;
    return 0;
}
