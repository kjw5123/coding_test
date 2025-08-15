#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// 토막 칠만치 치고 남은 찌끄래기만 집에 들고 갈 것이다
// 이 때 최대로 토막칠 수 있는 길이의 값은 ?

long long int n, m;  // 문제에서 느껴지는 순수한 악의...!!
vector<long long int> v;
int main () {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    long long int val;
    long long int maxVal = INT_MIN;
    for (int i = 0; i < n; i++) {
        cin >> val;
        v.push_back(val);
        maxVal = max(maxVal, val);
    }

    long long int low = 1; long long int high = maxVal;
    long long int result = 0;
    while (low <= high) {
        long long mid = (low + high) / 2;
        long long cnt = 0;
        for (int i = 0; i < (int)v.size(); i++) if (v[i] - mid >= 0) { cnt += v[i] - mid; }
        // cout << "mid is " << mid << " and cnt is " << cnt << endl;
        if (cnt >= m) { 
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << result << endl;
    return 0;
}
