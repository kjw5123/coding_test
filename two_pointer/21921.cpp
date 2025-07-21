#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int arr[250001];
int main() {    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n , m;
    cin >> n >> m;
    
    // slide window 방식으로 계산할깡
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int cnt = 0;
    int minIdx = 0;
    int currentVal = 0;
    int result = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (cnt != m) {
            currentVal += arr[i];
            cnt++;
            result = max(result, currentVal);
        } else {
            currentVal += arr[i] - arr[minIdx++];
            result = max(result, currentVal);
        }
    }
    
    int same_cnt = 0;
    cnt = 0; minIdx = 0; currentVal = 0;
    for (int i = 0; i < n; i++) {
        if (cnt != m) {
            currentVal += arr[i];
            if (currentVal == result) same_cnt++;
            cnt++; 
    
        } else {
            currentVal += arr[i] - arr[minIdx++];
            if (currentVal == result) same_cnt++;
        }
    }

    if (result == 0) cout << "SAD" << '\n';
    else {
        cout << result << '\n';
        cout << same_cnt << '\n';
    }
    return 0;
}
