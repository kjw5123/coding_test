#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int king, sub;
vector<int> shops;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    int val;
    for (int i = 0; i < n; i++) {
        cin >> val;
        shops.push_back(val);
    }
    cin >> king >> sub;

    long long int result = 0;
    for (int i = 0; i < (int)shops.size(); i++) {
        result++;
        shops[i] -= king;
        if (shops[i] <= 0) continue;
        result += shops[i] / sub;
        if (shops[i] % sub != 0) result += 1;
    }

    cout << result << endl;
    return 0;
}
