#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int a, t, to_find;
    cin >> a >> t >> to_find;
    // 뻔 - 데기 - 뻔 - 데기 - (뻔) x N  - (데기) x N
    int bun = 0;
    int degi = 0;

    string str = "0101";
    
    int idx = 0;
    int turn = 2;
    while (true) {
        for (int i = 0; i < 4; i++) {
            if (str[i] == '0') bun++;
            else if (str[i] == '1') degi++;

            if (to_find == 0 && bun == t) {
                cout << idx << endl;
                return 0;
            } else if (to_find == 1 && degi == t) {
                cout << idx << endl;
                return 0;
            }
            
            idx = (idx+1) % a;
        }

        for (int i = 0; i < turn; i++) {
            bun++;
            if (to_find == 0 && bun == t) {
                cout << idx << endl;
                return 0;
            }
            idx = (idx+1) % a;
        }

        for (int i = 0; i < turn; i++) {
            degi++;
            if (to_find == 1 && degi == t) {
                cout << idx << endl;
                return 0;
            }
            idx = (idx+1) % a;
        }



        turn++;
    }
    
    
    return 0;
}
