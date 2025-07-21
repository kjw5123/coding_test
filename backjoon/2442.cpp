#include <iostream>

using namespace std;

int main() {
    int a = 0;
    cin >> a;

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a -1 - i; j++) {
            cout << " ";
        }
        cout << "*";
        for (int j = 0; j < i; j++)  {
            cout << "**";
        }
        cout << '\n';
    }
    return 0;
}
