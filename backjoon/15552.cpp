#include <iostream>

using namespace std;

int main() {
    int a;
    cin >> a;
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 0; i < a; i++) {
        int a, b;
        cin >> a >> b;
        cout << a + b << '\n';

    }

    return 0;
}
