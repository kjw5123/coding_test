#include <iostream>

using namespace std;

int main() {
    int a, b, c, m;
    cin >> a >> b >> c >> m;
    int stress = 0;
    int work = 0;
    int time = 0;
    while(time!=24) {
        if (stress + a <= m){
            stress += a;
            work += b;
        } else {
            stress -= c;
            if (stress <= 0) stress = 0;
        }
        time++;
    }

    cout << work << endl;


    return 0;
}
