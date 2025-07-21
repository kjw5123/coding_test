#include <iostream>
// 자주 헷갈리는 getline 사용법은 잘 염두하자
using namespace std;

int main() {
    string a = "a";
    while(a != "\0") {
        getline(cin, a);
        cout << a << endl;
    }
    return 0;
}
