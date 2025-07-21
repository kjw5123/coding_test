#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
    int a, b, c, result;
    cin >> a >> b >> c;
    result = a * b * c;
    string str;
    str = to_string(result);
//    cout << result << endl;
//    cout << str << endl;
    int arr[10] = {0};
    for (int i = 0; i < str.length(); i++) {
        arr[str[i]-48]++;
    }
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << endl;
    }
    return 0;
}
