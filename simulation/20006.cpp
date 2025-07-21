#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;
// 입장 신청 했을 때 들어갈 수 있는 방 없으면 생성 후 입장
// 해당 방은 첫 플레이어 기준 - 10 ~ 10렙 입장 가능 
//
// 입장할 수 있는 방 있으면 들어간 후, 인우너 다 찰 때 까지 대기 
// 입장 가능한 게 여러개면 앞 방부터 입장
//
// 정원 다 차면 게임 시작

int player_num, level, maximum;
string nickname;
vector<pair<int, string> > v[300];

bool cmp(pair<int,string> p1, pair<int,string> p2) {
    return p1.second < p2.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> player_num >> maximum;
    int max_room_idx = 0;
    for (int i = 0; i < player_num; i++) {
        cin >> level >> nickname;
        bool isInsert = false;
        for (int j = 0; j <= max_room_idx; j++) {
            if (v[j].size() == 0) {
                v[j].push_back({level, nickname});
                isInsert = true;
                break;
            }
            else if (-10 <= v[j][0].first - level && v[j][0].first - level <= 10 && v[j].size() != maximum) {
                v[j].push_back({level, nickname});
                isInsert = true;
                break;
            }
        }
        if (!isInsert) {
            v[++max_room_idx].push_back({level, nickname});
        }
    }
    for (int i = 0; i <= max_room_idx; i++) sort(v[i].begin(), v[i].end(), cmp);

    for(int i = 0; i <= max_room_idx; i++) {
        if (v[i].size() == maximum) cout << "Started!" << '\n';
        else cout << "Waiting!" << '\n';
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j].first << " " << v[i][j].second << '\n';
        }
    }
    
    
    return 0;
}
