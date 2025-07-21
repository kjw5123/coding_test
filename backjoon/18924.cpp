#include <iostream>

using namespace std;

int main() {
    int months[13] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
    int a , b;
    cin >> a >> b;

    int cnt = months[a] + b;
    // 나머지 1 -> MON ... 0는 SUN
    int day = cnt % 7;
    switch(day){
        case 0:
            cout << "SUN";
            break;
        case 1:
            cout << "MON";
            break;
        case 2:
            cout << "TUE";
            break;
        case 3:
            cout << "WED";
            break;
        case 4:
            cout << "THU";
            break;
        case 5:
            cout << "FRI";
            break;
        case 6:
            cout << "SAT";
            break;
            
    }
    return 0;
}
