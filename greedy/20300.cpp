#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long int> v;
int main() {
    int n;
    cin >> n;
    // 짝수든 홀수든 간에 그냥 양 사이드 값 비교해서 진행하면 되지 않겠나
    v.push_back(0);

    for (int i = 0; i < n; i++) {
        long long int val;
        cin >> val;
        v.push_back(val);
    }
    sort(v.begin(), v.end());

    long long int maxVal = 0;
    if (n % 2 == 0) {
        for (int i = 1; i <= n / 2; i++) {
            if (v[i] + v[n + 1 - i] > maxVal) maxVal = v[i] + v[n + 1 - i];
        }
        cout << maxVal << endl;

    } else {
        for (int i = 1; i <= (n-1)/2; i++) {
            if (v[i] + v[n - i] > maxVal) maxVal = v[i] + v[n - i];
        }
        if (v[n] > maxVal) maxVal = v[n];
        cout << maxVal << endl;
    }
    return 0;
}
