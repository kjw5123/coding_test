#include <iostream>

using namespace std;


int main() {
    int n;
    cin >> n;

    // 홀수면 5를 뺄까?
    // 나머지로 접근해보기
    // 5로 나눴을 때 0 -> 검거 완료 그냥 N / 5 return
    // 5로 나눴을 때 1 -> N / 5 - 1 + 3 return
    // 5로 나눴을 때 2 -> N / 5 + 1 return
    // 5로 나눴을 때 3 -> N / 5 -1 + 4 return
    // 5로 나눴을 때 4 -> N / 5 + 2 return
    
    if (n == 1 || n == 3) cout << -1 << endl; 
    else {
        if (n % 5 == 0)      cout << n / 5 << endl; 
        else if (n % 5 == 1) cout << n / 5 - 1 + 3 << endl;
        else if (n % 5 == 2) cout << n / 5 + 1 << endl;
        else if (n % 5 == 3) cout << n / 5 - 1 + 4 << endl;
        else if (n % 5 == 4) cout << n / 5 + 2 << endl;
    }

    return 0;
}
