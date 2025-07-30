#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;
int n;

void bfs() {
    queue<string> q;
    int now_level = 0;
    for (int i = 0; i <= 9; i++) {
        now_level++;
        if (now_level == n) { cout << i << endl; exit(0); }
        q.push(to_string(i));
    }

    while (!q.empty()) {
        string c_str = q.front();
        int now_length = c_str.length();
        // cout << "current string is " << c_str << endl;
        q.pop();

        for (int i = 0; i <= 9; i++) {
            if (c_str[now_length-1] - 48 > i) {
                now_level++;
                string next_str = c_str + char(i+'0');
                // cout << "My value is " << next_str << " and now_level is " << now_level << endl;
                if (now_level == n) { cout << next_str << endl; exit(0); }
                q.push(next_str);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    bfs();
    cout << -1 << endl;
    return 0;
}
