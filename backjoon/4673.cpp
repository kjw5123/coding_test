#include <iostream>
#include <string>
using namespace std;
bool arr[10001];
int val(string str) {
    int value = 0;
    for (int i = 0; i < str.length(); i++) {
        value += str[i] - 48;
    }
    return value;
}

void find_it(int n) {
    int nn = n;
    while(n <= 10000) {
        if (nn != n) arr[n] = false;
        n += val(to_string(n));
    }
}

int main() {
    fill(arr, arr + 10001, true);
    for (int i = 1; i <= 10000; i++) {
        find_it(i);
    }    
    
    for (int i = 1; i < 10000; i++) {
        if (arr[i] != 0) cout << i << '\n';
    }
    
    return 0;
}
