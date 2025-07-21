#include <iostream>
using namespace std;


int main() {
    int total = 0;
    int a, a1, a2, a3, a4;
    cin >> a >> a1 >> a2 >> a3 >> a4;
    if (a <= 40) a = 40;
    if (a1 <= 40) a1 = 40;
    if (a2 <= 40) a2 = 40;
    if (a3 <= 40) a3 = 40;
    if (a4 <= 40) a4 = 40;
    total += a + a1 + a2 + a3 + a4;

    cout << total / 5 << endl;

    return 0;
}
