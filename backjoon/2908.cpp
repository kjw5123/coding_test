#include <iostream>

using namespace std;

int main() {
    string a;
    getline(cin, a);
    int aa = (a[2]-48) * 100 + (a[1]-48) * 10 + a[0] - 48;
    int bb = (a[6]-48) * 100 + (a[5]-48) * 10 + a[4] - 48;
    if (aa > bb) {
        cout << aa;
    } else {
        cout << bb; 
    }





    return 0;
}
