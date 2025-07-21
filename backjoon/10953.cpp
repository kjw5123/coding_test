#include <iostream>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string a;
        cin >> a;
        int aa, bb;
        aa = a[0] - 48;
        bb = a[2] - 48;

        cout << aa + bb << endl;
    }




    return 0;
}
