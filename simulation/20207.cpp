#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>

using namespace std;

// 연속된 두 일자가 한 직사각형 블럭이다 1xN이란 소리
//
// 달력은 시작 ~ 종료 날짜로 입력될 것이다
// 시작일이 가장 앞선 일정부터 순서대로 채워 넣을거다 vector<pair<int,int> > v 만들고 sort first
// 시작일이 같은 게 있으면 긴거부터 처리할 것이다 second - first 해서 큰거부터 넣고 visited 처리 하면 되겠네
int n, s, e;
vector<pair<int, int> > v;

bool arr[1001][366];
bool visited[1000];


bool cmp(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first == p2.first) {
        return p1.second > p2.second;
    }
    return p1.first < p2.first;
}

bool isNoVisited() {
    for (int i = 0; i < v.size(); i++) {
        if (!visited[i]) return true;
    }
    return false;
}

void check_arr() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 12; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
void check_visited() {
    for (int i = 0; i < v.size(); i++) {
            cout << visited[i] << " ";
    }
    cout << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s >> e;
        v.push_back({s, e});
    }
    sort(v.begin(), v.end(), cmp);
    /*
    for (int i = 0; i < v.size(); i++) {
        cout << v[i].first << " " << v[i].second << endl;
    }
    */
    int idx = 1;
    while (true) {
        for (int i = 0; i < v.size(); i++) {
            if (!visited[i]) {
                if (arr[idx][v[i].first] == 0) {
                    for (int j = v[i].first; j <= v[i].second; j++) {
                        // cout << "arr[" << idx << "][" << j << "] is true" << endl;
                        arr[idx][j] = true;
                    }
                    // check_arr();
                    visited[i] = true;
                }
            }
        }
        // cout << "My index is " << idx << endl;
        // check_visited();
        // cout << v.size() << endl;
        if (!isNoVisited()) break;
        idx++;
    }


    int result = 0; int height = 0; int width = 0;
    for (int day = 1; day <= 365; day++) {
        int cnt = 0;

        for (int row = 1; row <= 1000; row++) {
            if (arr[row][day]) cnt++;
        }
    
        if (cnt > 0) {
            width++;
            height = max(height, cnt);

        } else {
            result += height * width;
            height = 0;
            width = 0;
        }
    }
    result += height * width;
    cout << result << '\n';
    return 0;
}
