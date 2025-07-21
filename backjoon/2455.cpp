#include <iostream>

using namespace std;

int main() {
    int out, in;
    int remain = 0;
    int maxIn = -1;
    for (int i = 0; i < 4; i++) {
        cin >> out >> in;
        remain += in - out;
        if (remain > maxIn) maxIn = remain;
    }
    cout << maxIn << endl;


    return 0;
}
