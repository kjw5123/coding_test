#include <iostream>

using namespace std;

int main() {
    for (int i = 0; i < 3; i++) {
        int z = 0; int o = 0;
        for (int i = 0; i < 4; i++) {
            int a;
            cin >> a;
            if (a == 0) z++;
            else o++;
        }
        if (z == 0) cout << "E" << endl;
        else if (z == 1) cout << "A" << endl;
        else if (z == 2) cout << "B" << endl;
        else if (z == 3) cout << "C" << endl;
        else if (z == 4) cout << "D" << endl;
    }


    return 0;
}
