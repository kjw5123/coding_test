#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int a;
    cin >> a;
    long long int b = 0;
    for (int i = 1; i <= a; i++) {
        b += i;
    }
    cout << b << endl;
    return 0;
}
