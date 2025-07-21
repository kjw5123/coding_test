#include <iostream>

using namespace std;

int main() {
    int A, B;
    cin >> A >> B;

    // A *= 2 혹은 A * 10 + 1이 가능
    // 뒤집어서 생각해보면 B /= 2  혹은 (B - 1) / 10 (단 B 끝자리가 1일 때만) 가능

    // 그럼 그냥 무지성으로 첫자리 1 될 때 까지 2로 나누고 
    // 그 담에 - 1 / 10을 하면 되잖아
    // 만들 수 없는 경우는 음 ...
    // 초기에 block 해버리고 싶은데 아직 규칙을 모르겠음
    int cnt = 1;
    while (B != A) {
        if (B < A) {
            cout << -1 << endl;
            return 0;
        }

        if (B % 10 == 1) {
            B = (B - 1) / 10;

        } else if (B % 2 == 0) {
            B /= 2;

        } else {  // 일단 역탐색이다보니, 입력에서 홀수가 나오는 경우, 약간 고장나서 이렇게 -1 조건 적용 범위넓힘
            cout << - 1 << endl;
            return 0;
        }

//        cout << B << " ";
        cnt++;
    }
    
    cout << cnt << endl;
    return 0;
}
