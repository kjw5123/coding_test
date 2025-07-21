#include <iostream>

using namespace std;

int main() {
    string a;
    getline(cin, a);
    int cnt = 0;
    bool flag = true;
    for (int i = 0; i < a.length(); i++) {
        if (flag == true && a[i] != ' ') cnt++;
        flag = false;
        if (a[i] == ' ') flag = true;
    }
    cout << cnt << endl;

    return 0;
}
