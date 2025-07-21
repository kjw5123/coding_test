#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> a;
vector<int> b;
int n , m;
int main() {
    cin >> n >> m;
    int val = 0;
    for (int i = 0; i < n; i++) {
        cin >> val;
        a.push_back(val);
    }    
    
    
    for (int i = 0; i < m; i++) {
        cin >> val;
        b.push_back(val);
    }    

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int a_idx = 0;
    int b_idx = 0;

    for (int i = 0; i < a.size() + b.size(); i++) {
        if (a_idx >= a.size()) {
            cout << b[b_idx++] << " ";

        } else if (b_idx >= b.size()) {
            cout << a[a_idx++] << " ";

        } else {
            if (a[a_idx] <= b[b_idx]) {
                cout << a[a_idx++] << " ";

            } else {
                cout << b[b_idx++] << " ";
            }
        }
    }

    return 0;
}
