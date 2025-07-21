#include <iostream>

using namespace std;

int main() {
    string a;
    cin >> a;
    for (int i = 0; i < a.length(); i++) {  // 아오 c++은 strlen 아니라고
        cout << a[i];
        if (i % 10 == 9) cout << '\n';
    }
    return 0;
}
