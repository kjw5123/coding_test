#include <iostream>
using namespace std;

int main() {
    string a = "A";
    while (a != "") {
        getline(cin, a);
        cout << a;
    }

    return 0;
}
