#include <iostream>

using namespace std;
int arr[10001];
int n, x;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> x;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] < x) cout << arr[i] << " ";
    }


    return 0;
}
