#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>
#include <climits>

using namespace std;

// 독서실 특) 사람들 멀리 앉으려 함
// 1. 사람들은 가장 가까이에 있는 사람이 멀리 있는 잘 ㅣ선호 
// 2. 내가 1빠따로 독서실 온거면 1번 자리 선호
// 3. 1,2 번 조건 부합 못한다면, 먼 좌석 중 가장 작은 자리 번호 원한다 
//
// 독서실은 09:00 ~ 21:00 운영됨
//
// 입력 
// 좌석 수 N (1 ~ 100)
// 예약자 수 T (1 ~ 500)
// 민규 선호 번호 P (1 ~ N)

// T 입력 양식은 입실시간 + 퇴실 시간 "HHMM HHMM"로 주어진다
//
// 문자열 처리 때문에 정답률이 낮은가?
// 초 단위는 필요 없으니 분단위 convert 하자 
// str[0] * 600 + str[1] * 60 + str[2] * 10 + str[3]; 아이 좋아

// 2차원 배열을 하나 파서 채워가면서 할까? 고민이넹 

// 손님들은 1부터 채우는걸 선호함 (내가 지금 1 base라;)
// 1이 없으면 n로 가야함
// n도 없으면 
// n = 6이랑 7로 좀 비교 해보자 
// 1 0 0 0 0 2 
// 1 0 3 0 0 2
// 1 0 3 4 0 2
// 1 5 3 4 0 2
//
// 1 0 0 0 0 0 2
// 1 0 0 3 0 0 2
// 1 4 0 3 0 0 2
// 1 4 0 3 5 0 2
// 1 4 6 3 5 7 2
//
// 이걸 어떻게 규칙화 하지 
int n, t, p;
string s, e;
int time_table[101][721];// index 0이 의미하는 바는 0900 ~ 0901 점유
vector<pair<int, int>> times;

int time2min (string str) {
    return (str[0]-48)*600 + (str[1]-48)*60 + (str[2]-48)*10 + (str[3]-48);
}

bool cmp(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first == p2.first) return p1.second < p2.second;
    return p1.first < p2.first;
}

void check_remained_time() {
    int cnt = 0;
    for (int i = 0; i < 720; i++) {  // 이거 킥이다 719가 21:00이라 <= 하면 안됨 
        if (time_table[p][i] == 0) cnt++; 
    }
    cout << cnt << endl;
}

int get_min_dist(int y, int x) {
    int minVal = INT_MAX;
    for (int i = 1; i <= n; i++) {
        if (time_table[i][x] != 0) minVal = min(minVal, abs(i - y));
    }
    return minVal;
}

bool isNoOne(int start) {
    for (int i = 1; i <= n; i++) {
        if (time_table[i][start] != 0) return false;
    }
    return true;
}

int select_idx(int start, int end) {
    if (isNoOne(start) && time_table[1][start] == 0) return 1;

    // 가장 가까운 게 젤 먼 경우 ...
    // 걍 완전탐색 하지 뭐
    int min_maxVal = INT_MIN;
    int min_maxIdx = -1;
    for (int i = 1; i <= n; i++) {
        if (time_table[i][start] == 0) {
            int min_dist = get_min_dist(i, start);
            if (min_maxVal < min_dist) {
                min_maxVal = min_dist;
                min_maxIdx = i;
            }
        }
    }
    return min_maxIdx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> t >> p;
    int offset = time2min("0900");

    for (int i = 0; i < t; i++) {
        cin >> s >> e;
        times.push_back({time2min(s)-offset, time2min(e)-offset});
    }
    sort(times.begin(), times.end(), cmp);
/*
    for (int i = 0; i < (int)times.size(); i++) {
        cout << times[i].first << " " << times[i].second << endl;
    }
*/
    //simulation
    int person_num = 1;
    for (int i = 0; i < (int)times.size(); i++) {
        // 결국 start ~ end 까지 점유 시키긴 해야함
        // 그리고 i = start; i < end임
        
        int idx = select_idx(times[i].first, times[i].second);
        for (int j = times[i].first; j < times[i].second; j++) {
            time_table[idx][j] = person_num;
        }
        person_num++;
    }

    check_remained_time();
    return 0;
}
