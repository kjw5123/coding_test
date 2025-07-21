#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int arr[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;

    cin >> n >> k;

    for (int i = 0; i < n; i++) cin >> arr[i];

    int cnt = 0; int maxVal = INT_MIN; int currentVal = 0; int frontIdx = 0;
    for (int i = 0; i < n; i++) {
        if (cnt != k) {
            currentVal += arr[i];
            cnt++;
            if (cnt == k) maxVal = max(maxVal, currentVal);

        } else {
            currentVal += arr[i] - arr[frontIdx++];
            maxVal = max(maxVal, currentVal);
        }
    }
    cout << maxVal << endl;
    return 0;
}
