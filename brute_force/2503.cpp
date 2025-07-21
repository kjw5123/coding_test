#include <iostream>
#include <set>
#include <string>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;
set<string> s;
int n;
int arr[10];

void arr_init() {
    memset(arr, 0x00, sizeof(arr));
}

int main() {
    cin >> n;
    string val; int strike, ball;
    cin >> val >> strike >> ball;

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (i == j) continue;
            for (int k = 1; k <= 9; k++) {
                if (k == i || k == j) continue;
                    arr_init();
                    arr[i]++; arr[j]++; arr[k]++;
                    int correct = 0; int cnt = 0;
                    if (arr[val[0]-48] == 1) cnt++; if (arr[val[1]-48] == 1) cnt++; if (arr[val[2]-48] == 1) cnt++;
                    if (val[0] - 48 == i) correct++; if (val[1] - 48 == j) correct++; if (val[2] - 48 == k) correct++;
                    if (strike == correct && ball == cnt - correct) s.insert(to_string(100*i + 10*j + k));
            }
        }
    }
    for (int tc = 0; tc < n - 1; tc++) {
        cin >> val >> strike >> ball;
        set<string> s2;
        arr_init();
        arr[val[0]-48]++; arr[val[1]-48]++; arr[val[2]-48]++;
        for (set<string>::iterator it = s.begin(); it != s.end(); it++) {
            string cmp = *it;
            int correct = 0; int cnt = 0;
            if (arr[cmp[2]-48] == 1) cnt++; if (arr[cmp[1]-48] == 1) cnt++; if (arr[cmp[0]-48] == 1) cnt++;
            if (cmp[0] == val[0]) correct++; if (cmp[1] == val[1]) correct++; if (cmp[2] == val[2]) correct++;
            if (strike == correct && ball == cnt - correct) s2.insert(cmp);
        }
        s = s2;
    }

    cout << s.size() << endl;
    return 0;
}
