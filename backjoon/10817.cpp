#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> v;

    int a;
    cin >> a;
    v.push_back(a);
    cin >> a;
    v.push_back(a);
    cin >> a;
    v.push_back(a);

    sort(v.begin(), v.end());
    cout << v[1] << endl;
    return 0;
}
