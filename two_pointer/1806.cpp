#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int n, s;
int arr[100001];  // int 써도 문제 없다 10,000 이하 자연수라

// 음... 직관으로 풀 문제는 아닌데 이거?
// 누적합... (맞는진 모르겠지만) 으로 접근한다거나 ?
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> s;
    
    arr[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] += arr[i-1];
    }

    int minLength = INT_MAX;
    int l_idx = 0;
    int r_idx = 0;
    int currentSum = 0;
    while(true) {
        if (r_idx == n + 1) break;
        
        currentSum = arr[r_idx];
        while(currentSum - arr[l_idx] >= s) {
            minLength = min(minLength, r_idx - l_idx);
            // cout << "min Length is " << minLength << " and r index is " << r_idx << " and l index is " << l_idx << endl;
            l_idx++;
        }


        
        r_idx++;
    }

    if (minLength != INT_MAX) cout << minLength << endl;
    else cout << 0 << endl;
    return 0;
}
