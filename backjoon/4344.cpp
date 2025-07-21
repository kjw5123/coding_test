#include <iostream>
#include <cmath>
using namespace std;

int T;
int arr[1001] = {0};

int main() {
    cin >> T;

    for (int i = 0; i < T; i++) {
        int n = 0;
        cin >> n;
        int avg = 0;
        for (int j = 0; j < n; j++) {
            cin >> arr[j];
            avg += arr[j];
        }
        avg /= n;

        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] > avg) cnt++;
        }

        cout << fixed;
        cout.precision(3);
        cout << double(cnt) / double(n) * 100 << "%" << endl;
    }
    
    
    return 0;
}
