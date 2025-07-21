#include <iostream>

using namespace std;

int lcm(int n1, int n2) {
    int maxVal = -1;
    for (int i = 1; i <= n1; i++) {
        if (n1 % i == 0 && n2 % i == 0) maxVal = i;
    }
    return maxVal;
}

int main() {
    int n1, n2;
    cin >> n1 >> n2;
    if (n2 > n1) {
        int temp = n2;
        n2 = n1;
        n1 = temp;
    }
    int l = lcm(n1, n2);
    int g = n1 * n2 / l;

    cout << l << '\n' << g << endl;



    return 0;
}
