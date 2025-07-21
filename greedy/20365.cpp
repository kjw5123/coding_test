#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    string str;
    cin >> str;

    int cnt = 0;
    int r_cnt = 0; int b_cnt = 0;
    char now_color = str[0];
    if (str[0] == 'R') r_cnt++;
    else b_cnt++;
    
    for (int i = 1; i < str.length(); i++) {
        if (now_color != str[i]) {
            if (now_color == 'R') {b_cnt++;}
            else r_cnt++;
            now_color = str[i];
        }
    }
//    cout << r_cnt << " " << b_cnt << endl;
    cout << min(r_cnt, b_cnt) + 1 << endl;
    return 0;
}
