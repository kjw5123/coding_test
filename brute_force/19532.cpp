#include <iostream>

using namespace std;


int main() {
    long long int a,b,c,d,e,f;
    cin >> a >> b >> c >> d >> e >> f;
/*
    if (c == 0 && f == 0) {
        cout << 0 << " " << 0 << endl;
    }
    else {
        long long int x = (c*e - f*b) / (a*e - d*b);
        long long int y = (c - a * x) / b;
        cout << x << " " << y << endl;
    }
*/
    for (int x = -999; x <= 999; x++) {

        for (int y = -999; y <= 999; y++) {
            if ((a * x + b * y == c) && (d * x + e * y == f)) cout << x << " " << y << endl;   
        }
    }
    
    return 0;
}
