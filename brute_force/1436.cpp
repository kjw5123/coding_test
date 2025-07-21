#include <iostream>
#include <climits>
#include <string>

using namespace std;


int main() {
    int n;
    cin >> n;
    int cnt = 0;
    for (int i = 0; i < INT_MAX; i++) {
        string str = to_string(i);
        int six_cnt = 0;
        for (int j = 0 ; j < str.length(); j++) {
            if (str[j] == '6') six_cnt++;
            else six_cnt = 0;
            if (six_cnt == 3) cnt++;
            if (cnt == n) {
                cout << str << endl;
                return 0;    
            }
        }
    }
    
    
    
    return 0;
}
