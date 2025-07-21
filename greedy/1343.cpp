#include <iostream>
#include <vector>

using namespace std;

vector<int> v;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // AAAA , BB 모양 짝대기 2개 무한개 가짐
    string str;
    cin >> str;

    // XXXX....XXX.....XX (4 0 0 0 0 3 0 0 0 0 0 2)
    // XX.XXXXXXXXXX..XXXXXXXX...XXXXXX (2 0 10 0 0 8 0 0 0 6)
    int cnt = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == 'X') cnt++;
        else {
            if(cnt != 0) v.push_back(cnt);
            cnt = 0;
            v.push_back(0);
        }
    }

    if (cnt != 0) v.push_back(cnt);

    for (int i = 0; i < v.size(); i++) {
        if (v[i] % 2 != 0) {
            cout << -1 << endl;
            return 0;
        }
    }
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 0) cout << '.';
        else {
            int four = v[i] / 4;
            int two = v[i] / 2 - 2 * four;
            for (int j = 0; j < four; j++) {
                cout << "AAAA";
            }
            for (int j = 0; j < two; j++) {
                cout << "BB";
            }
        }
    }
    return 0;
}
