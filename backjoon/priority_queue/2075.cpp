#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct cmp {
    bool operator() (int a, int b) {
        return a > b;
    }
};

int n;
priority_queue<int, vector<int>, cmp> pq;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    int val;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> val;
            pq.push(val);
            if ((int)pq.size() > n) pq.pop();
        }
    }
    /*
    while((int)pq.size() != 1) {
        pq.pop();
    }
    */

    cout << pq.top() << endl;

    return 0;
}
