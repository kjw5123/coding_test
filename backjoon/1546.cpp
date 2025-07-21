#include <iostream>

using namespace std;

int arr[1001] = {0};
int main() {
    int n;
    cin >> n;
    int total = 0;
    int minVal = -1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        total += arr[i];
        if (arr[i] > minVal) minVal = arr[i];
    }

    cout << double(total) / double(n) / minVal * 100 << endl;

    return 0;
}
