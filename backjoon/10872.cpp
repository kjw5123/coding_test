#include <iostream>

using namespace std;

long long int fact(long long int v) {
    if (v == 0) return 1;
    return v * fact(v-1);
}

int main() {
    int a = 0;
    cin >> a;
    cout << fact(a) << endl;



    return 0;
}
