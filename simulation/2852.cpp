#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>


using namespace std;
int n;
vector<pair<int,int> > v;

int convert(string str) {
    return (str[0] - 48) * 600 + (str[1] - 48) * 60 + (str[3]- 48) * 10 + (str[4] - 48);
}

string int2time(int t) {
    string str;
    str += to_string(t / 600); t %= 600;
    str += to_string(t / 60); t %= 60;
    str += ":";
    str += to_string(t / 10); t %= 10;
    str += to_string(t);
    return str;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    // 귀찮은데 초로 변환하자
    string str;
    int team;
    for (int i = 0; i < n; i++) {
        cin >> team >> str;
        v.push_back({team, convert(str)});
    }

    int a_score = 0; int b_score = 0;
    int a_lead = 0; int b_lead = 0;
    int prev_team = -1;
    int prev_time = 0;
    int final_time = 60 * 48;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].first == 1) a_score++;
        else b_score++;

        if ( a_score > b_score ) {
            a_lead += final_time - v[i].second;
            if (prev_team == 1) a_lead -= final_time - v[i].second;
            else if (prev_team == 2) b_lead -= final_time - v[i].second;
            
            prev_team = 1;

        } else if (a_score < b_score){
            b_lead += final_time - v[i].second;
            if (prev_team == 1) a_lead -= final_time - v[i].second;
            else if (prev_team == 2) b_lead -= final_time - v[i].second;
            
            prev_team = 2;

        } else {
            if (prev_team == 1) a_lead -= final_time - v[i].second;
            else if (prev_team == 2) b_lead -= final_time - v[i].second;

            prev_team = -1;
        }

        prev_time = v[i].second;
    }
    // cout << a_lead << " " << b_lead << endl;
    cout << int2time(a_lead) << endl;
    cout << int2time(b_lead) << endl;
    return 0;
}
