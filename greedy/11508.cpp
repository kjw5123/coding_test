#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int v1, int v2) {
    return v1 > v2;
}

vector<int> v;
int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        v.push_back(val);  
    }
    sort(v.begin(), v.end(), cmp);
/*
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
*/      
    long long result = 0;
    int remain = v.size() % 3;
    for (int i = 0; i < v.size() - remain; i++) {
        if (i % 3 != 2) result += v[i];
    }
    for (int i = v.size() - remain; i < v.size(); i++) {
        result += v[i]; 
    }
    cout << result << endl; 
    return 0;
}
