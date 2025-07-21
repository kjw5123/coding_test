#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int,int> > v;

bool cmp(pair<int,int> p1, pair<int,int> p2) {
    if (p1.second == p2.second) {
        return p1.first < p2.first;
    }
    return p1.second < p2.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int start, end;
        cin >> start >> end;
        v.push_back({start, end});
    }
    sort(v.begin(), v.end(), cmp);

    // 이미 매 회의에 대해 최대로 적게 파이 가져가는 애들이 앞에 나오게끔 함
    int cnt = 1;
    int end = v[0].second;
    for (int i = 1; i < n; i++) {
        if (end <= v[i].first) {
            end = v[i].second;
            cnt++;
        }
    }
    cout << cnt << endl;

   /* 
    for (int i = 0; i < n; i++) {
        cout << v[i].first << " " << v[i].second << endl;
    }
    */
    return 0;
}
