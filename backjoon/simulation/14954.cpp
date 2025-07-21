#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
// 1 2 3 4 5 6 7 8 9 10
// 1 1 1 4 5 6 7 8 9 10
// (arr[2] != 2)이니 해당 숫자로 쭊 밀면 
// 1 1 1 1 5 6 7 8 9 10
// (arr[5] == 5)이니 5로 밀면
// 1 1 1 1 5 5 5 5 9 10
// 다른 숫자 나올 때마다 cnt++ 하면 
// 4 나오긴 하네 
int n, m;
vector<int> v;
vector<pair<int , int > > boom;

bool cmp(pair<int,int> p1, pair<int,int> p2) {
    if (p1.first == p2.first) return p1.second < p2.second;
    return p1.first < p2.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    v.push_back(0);
    
    for (int i = 1; i <= n; i++) v.push_back(i);
    int s, e;
    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        boom.push_back({s, e});
    }
    sort(boom.begin(), boom.end(), cmp);

    for (int i = 0; i < (int)boom.size(); i++) {
        int start_idx = boom[i].first;
        int end_idx = boom[i].second;

        if (v[start_idx] == start_idx) {
            for (int j = start_idx; j <= end_idx; j++) {
                v[j] = start_idx;
            }

        } else {
            for (int j = start_idx; j <= end_idx; j++) {
                v[j] = v[start_idx];
            }
            
        }
    }

    int cnt = 0;
    for (int i = 0; i < (int)v.size() - 1; i++) {
        if (v[i] != v[i+1]) cnt++;
    }
    cout << cnt << endl;
    return 0;
}
