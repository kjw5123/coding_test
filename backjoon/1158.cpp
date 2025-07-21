#include <iostream>
#include <deque>

using namespace std;
deque<int> d;
int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        d.push_back(i);
    }

    cout << '<';

    while(!d.empty()) {
        for (int i = 0; i < k-1; i++) {
            d.push_back(d.front());
            d.pop_front();
        }
        cout << d.front();
        d.pop_front();
        
        if (d.size() != 0) cout << ", ";
    }

    cout << '>';


    return 0;
}
