#include <iostream>
#include <algorithm>

using namespace std;
// 걍 번호 9를 6으로 통합시켜서 처리시키고
// 한 세트에 6이 2개 있는 셈으로 진행하면 된다 
//
int main() {
    string str;
    cin >> str;
    int arr[10] = {0};
    for (int i = 0; i < str.length(); i++) {
        arr[str[i]-48]++;
    }

    arr[6] += arr[9];
    arr[9] = 0;
    
    if (arr[6] % 2 == 1) arr[6] = arr[6] /2 + 1;
    else arr[6] /= 2;
    
    int maxVal = -1;
    for (int i = 0; i < 10; i++) {
        if (maxVal < arr[i]) maxVal = arr[i];
    }
    cout << maxVal << endl;
    return 0;
}
