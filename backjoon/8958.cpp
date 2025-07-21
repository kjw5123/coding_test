#include <iostream>

using namespace std;

int T = 0;
int main() {
    cin >> T;
    for (int i = 0; i < T; i++) {
        string str;
        cin >> str;
        int pdf = 1;
        int result = 0;
        for (int j = 0; j < str.length(); j++) {
            if (str[j] == 'O') {
                result += pdf;
                pdf++;
            } else {
                pdf = 1;
            }
        }
        cout << result << endl;
    }


    return 0;
}
