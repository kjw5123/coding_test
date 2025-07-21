#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    double a , b;

    cin >> a >> b;
    cout << fixed;
    cout.precision(10);
    cout << a / b << endl;
    return 0;
}
