#include <iostream>
#include <string>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    string s, t;
    cin >> s >> t;

    set<string> visited;
    queue<string> q;

    q.push(t);
    visited.insert(t);

    while (!q.empty()) {
        string cur = q.front();
        q.pop();

        if (cur == s) {
            cout << 1 << endl;
            return 0;
        }

        if (cur.length() < s.length()) continue;

        if (cur.back() == 'A') {
            string next = cur;
            next.pop_back();
            if (!visited.count(next)) {
                visited.insert(next);
                q.push(next);
            }
        }

        if (cur.front() == 'B') {
            string next = cur;
            reverse(next.begin(), next.end());
            next.pop_back();
            if (!visited.count(next)) {
                visited.insert(next);
                q.push(next);
            }
        }
    }

    cout << 0 << endl;
    return 0;
}

