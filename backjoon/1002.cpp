/*
 * #include <iostream>
#include <cmath>

using namespace std;

int main() {
    int tc;
    cin >> tc;

    for (int i = 0; i < tc; i++) {
        int x1, y1, r1, x2, y2, r2;

        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

        if (x1 == x2 && y1 == y2 && r1 == r2) cout << -1 << endl;
        else if (x1 == x2 && y1 == y2 && r1 != r2) cout << 0 << endl;
        else if (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) < r1 + r2) cout << 2 << endl;
        else if (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) == r1 + r2) cout << 1 << endl;
        else cout << 0 << endl;
    }
    
    
    return 0;
}
*/

#include <iostream>

using namespace std;

int main() {
    int tc;
    cin >> tc;

    for (int i = 0; i < tc; i++) {
        int x1, y1, r1, x2, y2, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

        int dx = x1 - x2;
        int dy = y1 - y2;
        int dist_sq = dx * dx + dy * dy;

        int sum_r = r1 + r2;
        int diff_r = r1 - r2;
        int sum_r_sq = sum_r * sum_r;
        int diff_r_sq = diff_r * diff_r;

        if (x1 == x2 && y1 == y2 && r1 == r2) {
            cout << -1 << '\n'; 
        }
        else if (dist_sq > sum_r_sq || dist_sq < diff_r_sq) {
            cout << 0 << '\n'; 
        }
        else if (dist_sq == sum_r_sq || dist_sq == diff_r_sq) {
            cout << 1 << '\n';  
        }
        else {
            cout << 2 << '\n'; 
        }
    }

    return 0;
}

