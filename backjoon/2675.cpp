#include <iostream>

using namespace std;
int n;
int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        int times; string str;
        cin >> times >> str;
        for (int j = 0; j < str.length(); j++) {
            for (int k = 0; k < times; k++) {
                cout << str[j];
            }
        }
        cout << endl;
    }

    return 0;
}
