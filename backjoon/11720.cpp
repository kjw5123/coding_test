#include <iostream>

using namespace std;

int main() {
    char a;
    int n = 0; int cnt = 0;
    cin >> n;
    cin.ignore();  // n 입력 받으면서 같이 들어오는 \n 무시
    for (int i = 0; i < n; i++) {
        cin.get(a);  // 한글자만 입력받기 무슨 일이 있어도
        cnt += a - 48;  // Embedded Magic
    }
    cout << cnt << endl; 

    return 0;
}
