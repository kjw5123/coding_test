#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
int n;
int arr[100001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    
    for (int i = 1; i <= n; i++) cin >> arr[i];

    int l_idx = 1; int r_idx = n;
    int maxVal = INT_MIN;

    while(l_idx < r_idx) {
        maxVal = max(maxVal, (r_idx - l_idx - 1) * min(arr[l_idx], arr[r_idx]));
        if (arr[l_idx] < arr[r_idx]) l_idx++;
        else r_idx--;
    }

    cout << maxVal << endl;
    return 0;
}
