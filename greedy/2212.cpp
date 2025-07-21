#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int v1, int v2) {
    return v1 < v2;
}

bool cmp2(int v1, int v2) {
    return v1 > v2;
}

vector<int> v;
vector<int> diff;
vector<int> pdf;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;

    
    for (int i = 0; i < n; i++) {
        int val; cin >> val;
        v.push_back(val);
    }
    sort(v.begin(), v.end(), cmp);
    
    for (int i = 0; i < n - 1; i++) {
        diff.push_back(v[i+1] - v[i]);
    }

    sort(diff.begin(), diff.end(), cmp2);
    int result = 0;
    for (int i = k - 1; i < n; i++) {
        result += diff[i];
    }
    cout << result << endl;
     
    return 0; 
}
