#include <iostream>

using namespace std;
int n;
int arr[11];
int res[11];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        res[i] = 11;
    }

    
    for (int i = 1; i <= n; i++) {
        int left = i;
        int left_bigger = arr[left];
        int left_cnt = 0;
        for (int j = 1; j <= n; j++) {
            if (left_cnt == left_bigger && res[j] == 11) {
                res[j] = left;
                break;
            }
            if (left < res[j]) left_cnt++;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << " ";
    }
    return 0;
}
