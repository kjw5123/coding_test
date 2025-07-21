#include <iostream>

using namespace std;

int main() {
    string str;
    while (getline(cin, str)) {
        if(str[0] + str[2] - 96 != 0) cout << str[0] + str[2] - 96 << endl;
    }


    return 0;
}
