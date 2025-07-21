#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
// 참가 인원수 N 1 ~ 1000
// 참가 팀     M 1 ~ 200
// 주자 수 6명 이하인 팀은 점수 X
// 등수 합 최소 팀 출력
// 단 동일 점수면 5번째 선수 등수 낮은 팀이 우승
int tc, man;
int team[201];   // 팀별 소속 인원 수
int mans[1001];  // 각인원 별 팀 정보
int grades[1001];// 각 인원 별 등수
int result[201]; // 팀 점수 총합
int result_cnt[201];
int five_man[201];

int main() {   
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> tc;

    for (int t = 0; t < tc; t++) {
        cin >> man;
        memset(team, 0x00, sizeof(team));
        memset(mans, 0x00, sizeof(mans));
        memset(grades, 0x00, sizeof(grades));
        memset(result, 0x00, sizeof(result));
        memset(result_cnt, 0x00, sizeof(result_cnt));
        memset(five_man, 0x00, sizeof(five_man));

        int total_team = 0;
        for (int i = 1; i <= man; i++) {
            cin >> mans[i];  // 팀 정보 입력
            team[mans[i]]++;  // 팀 인원 수 카운트
            total_team = max(total_team, mans[i]);
        }
/*
        for (int i = 1; i <= total_team; i++) {
            cout << team[i] << " ";
        }
        cout << endl;
*/
        int grade = 1;
        for (int i = 1; i <= man; i++) {
            if (team[mans[i]] == 6) {  // 온전히 6명으로 이루어진
                grades[i] = grade++;  // 인원 별 등수 매기기
                five_man[mans[i]]++;
                if (five_man[mans[i]] == 5) five_man[mans[i]] = grades[i];
            } 
        }
/*
        for (int i = 1; i <= man; i++) {
            cout << grades[i] << " ";
        }
        cout << endl;
*/
        for (int i = 1; i <= man; i++) {
            if (result_cnt[mans[i]] <= 3) result[mans[i]] += grades[i];
            result_cnt[mans[i]]++;
        }
/* 
        for (int i = 1; i <= total_team; i++) {
            cout << result[i] << " ";
        }
        cout << endl;
*/
        int minResult = 1e9;
        for (int i = 1; i <= total_team; i++) {
            if (result[i] != 0) minResult = min(minResult, result[i]);
        }

        vector<int> winner_teams;
        for (int i = 1; i <= total_team; i++) {
            if (result[i] == minResult) winner_teams.push_back(i);
        }
        if (winner_teams.size() == 1) {
            cout << winner_teams[0] << endl;

        } else {
            int small_five_grade = 1e9;
            for (int i = 0; i < winner_teams.size(); i++) {
                small_five_grade = min(five_man[winner_teams[i]], small_five_grade);
            }

            for (int i = 1; i <= total_team; i++) {
                if (five_man[i] == small_five_grade) cout << i << endl;
            }
        }
    }
        
    return 0;
}
