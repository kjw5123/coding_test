#include <iostream>

using namespace std;

int main() {
    int first_num;
    cin >> first_num;

    int prev_num = first_num;
 //   if (first_num < 10) prev_num *= 10;
    int middle_num = prev_num / 10 + prev_num % 10;
    int next_num = prev_num % 10 * 10 + middle_num % 10;
    int cnt = 1;

    while (next_num != first_num) {
        prev_num = next_num;
//        if (prev_num < 10) prev_num *= 10;
        middle_num = prev_num / 10 + prev_num % 10;
        next_num = prev_num % 10 * 10 + middle_num % 10;
        /*
        cout << prev_num << endl;
        cout << middle_num << endl;
        cout << next_num << endl;
        cout << "============" << endl;
        if (cnt == 10) break;
        */
        cnt++;
    }
    cout << cnt << endl;
    return 0;
}
