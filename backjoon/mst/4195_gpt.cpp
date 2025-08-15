#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>

using namespace std;
// 테스트 케이스로 나뉘는 문제는 꼭 전역변수 초기화를 잊지 말자 ! ! ! ! ! ! ! ! ! 

int tc, n;
string str1, str2;
set<string> name_list;
map<string, pair<string, int>> name;
vector<pair<string, string>> inputs;

string find(string s) {
    if (s == name[s].first) { return s; }
    return name[s].first = find(name[s].first);
}

void unite(string s1, string s2) {
    s1 = find(s1);
    s2 = find(s2);
    if (s1 != s2) {
        name[s1].second += name[s2].second;
        name[s2].first = s1;
    }
    cout << name[s1].second << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tc;

    for (int t = 0; t < tc; t++) {
        cin >> n;
        name_list.clear(); inputs.clear(); name.clear();

        for (int i = 0; i < n; i++) {
            cin >> str1 >> str2;
            inputs.push_back({str1,str2});
            name_list.insert(str1); name_list.insert(str2);
        }

        for (set<string>::iterator it = name_list.begin(); it != name_list.end(); it++) {
            name[*it] = {*it, 1};
        }


        for (int i = 0; i < (int)inputs.size(); i++) {
            string s1 = inputs[i].first; string s2 = inputs[i].second;
            unite(s1, s2);

        }
    }
    
    
    
    return 0;
}
