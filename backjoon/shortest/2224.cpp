#include <iostream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

int n;
int dist[129][129];
vector<int> alphabet[129];

struct cmp {
    bool operator() (int a, int b) {
        return a > b;
    }
};
int cnt = 0;
void dijkstra(int start) {
    dist[start][start] = 0;
    priority_queue<int, vector<int>, cmp> pq;
    pq.push(start);
    
    while(!pq.empty()) {
        // cout << "I'm " << pq.top() << endl;
        int c_idx = pq.top();
        pq.pop();

        for (int i = 0; i < (int)alphabet[c_idx].size(); i++) {
            int n_idx = alphabet[c_idx][i];
            int n_dist = dist[start][n_idx];
            if (n_dist != 0) {
                // cout << " I Insert " << n_idx << endl;
                pq.push(n_idx);
                dist[start][n_idx] = 0;
                cnt++;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    string str;
    char s, e;
    for (int i = 0; i <= (int)'z'; i++) {
        for (int j = 0; j <= (int)'z'; j++) {
            dist[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> s >> str >> e;
        alphabet[(int)s].push_back((int)e);
    }

    for (int i = 65; i <= (int)'z'; i++) {
        dijkstra(i);
    }
    cout << cnt << endl;
    for (int i = 65; i <= (int)'z'; i++) {
        for (int j = 65; j <= (int)'z'; j++) {
            if (i != j && dist[i][j] == 0) cout << char(i) << " => " << char(j) << '\n';
        }
    }




    return 0;
}
