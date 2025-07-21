#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
int n;
long long int arr[100001];
int cnt[100001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    
    
    int l_idx = 1; int r_idx = 1;
    long long int maxVal = 0;
    int nums = 0;
    while (r_idx <= n) {
        int now_val = arr[r_idx];
        cnt[now_val]++;
        nums++;

        while (cnt[now_val] > 1) {
            cnt[arr[l_idx]]--;
            nums--;
            l_idx++;
        }

        maxVal += nums;
        r_idx++;
    }
    cout << maxVal << endl;
    return 0;
}
