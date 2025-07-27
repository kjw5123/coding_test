#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstdlib>
#include <algorithm>

using namespace std;


struct cmp{
    bool operator() (pair<int,int> p1, pair<int,int> p2) {
        if (p1.first == p2.first) return p1.second < p2.second;
        return p1.first > p2.first;
    }
};

priority_queue<pair<int,int>, vector<pair<int,int> >, cmp> pq;

int m;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> m;

    int s, e;

    while(true) {
        cin >> s >> e;
        if (s > e) swap(s, e);
        if (s == 0 && e == 0) break;
        if (e<=0||s>m||s==e) continue;
        pq.push({s, e});
    }
    int cur = 0;
    int cnt = 0;

    while (cur < m) {
        if (pq.empty()) { cout << 0 << endl; exit(0); }

        int best = cur;
        while (!pq.empty() && pq.top().first <= cur) {
            best = max(best, pq.top().second);
            pq.pop();
        }
        if (best == cur) { cout << 0 << endl; exit(0); }

        cur = best;
        ++cnt;
    }

    cout << cnt << '\n';
    /*
    if (pq.size() == 0) {cout << 0 << endl; return 0;}
    int cs = pq.top().first;
    int ce = pq.top().second;
    pq.pop(); int cnt = 1;
    if (cs > 0) {cout << 0 << endl; return 0;}

    int bigger = ce;
    while(ce < m) {
        if (pq.empty()) break;
        int ns = pq.top().first; int ne = pq.top().second; pq.pop();
        if (ne <= ns) continue;
        if (ns <= ce) bigger = max(bigger, ne);

        if (ns > ce) {
            ce = bigger; cnt++;
            if (ns > ce) {cout << 0 << endl; exit(0);}
            if (ns <= ce) bigger = max(bigger, ne);
            else pq.push({ns, ne});
            if (cs <= 0 && ce >= m) {cout << cnt << endl; exit(0);}
        }
    }
    if (ce != bigger) {ce = bigger; cnt++;}
    if (ce >= m) cout << cnt << endl;
    else cout << 0 << endl;
    return 0;   
    */
}
