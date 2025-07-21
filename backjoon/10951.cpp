#include <iostream>

using namespace std;

int main() {
    string a;
    while(getline(cin, a)) {
        cout << a[0] + a[2] - 96 << endl;
    }
    return 0;
}
